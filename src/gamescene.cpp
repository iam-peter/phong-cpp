#include "gamescene.h"
#include "phong.h"

GameScene::GameScene(Qt3DCore::QNode* parent,
                     Phong* phong):
    Scene(parent, phong),
    m_frameAction(nullptr),
    m_topWall(nullptr),
    m_bottomWall(nullptr),
    m_ball(nullptr),
    m_leftRacket(nullptr),
    m_rightRacket(nullptr),

    m_world(nullptr),
    m_bodyBall(nullptr),
    m_bodyLeftRacket(nullptr),
    m_bodyRightRacket(nullptr)
{
    m_frameAction = new Qt3DLogic::QFrameAction(this);

    QObject::connect(this, &Scene::activeChanged,
                     this, & GameScene::handleConnections);

    float width = 26.0f;
    float height = 18.0f;

    m_topWall = new Wall(this,
                         QVector3D(0.0f, 0.5f * height, 0.0f),
                         QVector3D(width, 1.0f, 1.0f));

    m_bottomWall = new Wall(this,
                            QVector3D(0.0f, -0.5f * height, 0.0f),
                            QVector3D(width, 1.0f, 1.0f));

    m_ball = new Ball(this,
                      QVector3D(0.0f, 0.0f, 0.0f),
                      0.8f);

    m_leftRacket = new Racket(this,
                              QVector3D(-4.0f, 0.0f, 0.0f),
                              QVector3D(1.0f, 4.0f, 1.0f));
    m_rightRacket = new Racket(this,
                               QVector3D(4.0f, 0.0f, 0.0f),
                               QVector3D(1.0f, 4.0f, 1.0f));


    // Initialize Box2D stuff
    b2Vec2 gravity(0.0f, 0.0f);
    m_world = new b2World(gravity);

    // Top Wall
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(0.0f, 0.5f * height);
        bodyDef.type = b2_staticBody;

        b2PolygonShape shape;
        shape.SetAsBox(width * 0.5f, 0.5f);

        b2Body* body = m_world->CreateBody(&bodyDef);
        body->CreateFixture(&shape, 0.0f);
    }

    // Bottom Wall
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(0.0f, -0.5f * height);
        bodyDef.type = b2_staticBody;

        b2PolygonShape shape;
        shape.SetAsBox(width * 0.5f, 0.5f);

        b2Body* body = m_world->CreateBody(&bodyDef);
        body->CreateFixture(&shape, 0.0f);
    }

    // Ball
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(0.0f, 0.0f);
        bodyDef.type = b2_dynamicBody;
        bodyDef.bullet = true;
        //bodyDef.linearDamping = 0.0f;
        //bodyDef.angularDamping = 0.01f;
        bodyDef.gravityScale = 0.0f;

        m_bodyBall = m_world->CreateBody(&bodyDef);

        b2CircleShape shape;
        shape.m_radius = 0.8f;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.restitution = 0.8f;

        m_bodyBall->CreateFixture(&fixtureDef);
    }

    // Left Racket
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(-4.0f, 0.0f);
        bodyDef.type = b2_dynamicBody;
        bodyDef.bullet = true;
        bodyDef.linearDamping = 0.3f;
        bodyDef.angularDamping = 0.1f;
        bodyDef.gravityScale = 0.0f;

        m_bodyLeftRacket = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.restitution = 0.8f;

        m_bodyLeftRacket->CreateFixture(&fixtureDef);
    }
}

GameScene::~GameScene()
{}

void GameScene::keyPressed(Qt3DInput::QKeyEvent* event) {
    qDebug() << Q_FUNC_INFO;

    switch (event->key()) {
        case Qt::Key_Escape:
            m_phong->previousScene();
            break;
        case Qt::Key_Up:
            m_bodyBall->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f),
                                           m_bodyBall->GetWorldCenter(),
                                           true);
            break;
        case Qt::Key_Down:
            m_bodyBall->ApplyLinearImpulse(b2Vec2(0.0f, -1.0f),
                                           m_bodyBall->GetWorldCenter(),
                                           true);
            break;
        case  Qt::Key_Left:
            m_bodyBall->ApplyLinearImpulse(b2Vec2(-1.0f, 0.0f),
                                           m_bodyBall->GetWorldCenter(),
                                           true);
            break;
        case Qt::Key_Right:
            m_bodyBall->ApplyLinearImpulse(b2Vec2(1.0f, 0.0f),
                                           m_bodyBall->GetWorldCenter(),
                                           true);
            break;
        default:
            break;
    }

    event->setAccepted(true);
}

void GameScene::keyReleased(Qt3DInput::QKeyEvent* event) {
    qDebug() << Q_FUNC_INFO;
    event->setAccepted(true);
}

void GameScene::handleConnections(bool active) {
    if (active) {
        QObject::connect(m_frameAction, &Qt3DLogic::QFrameAction::triggered,
                         this, &GameScene::gameLoop);
    }
    else
    {
        QObject::disconnect(m_frameAction, &Qt3DLogic::QFrameAction::triggered,
                            this, &GameScene::gameLoop);
    }
}

void GameScene::gameLoop(float dt) {
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    m_world->Step(dt, velocityIterations, positionIterations);

    {
        b2Vec2 position = m_bodyBall->GetPosition();
        float32 angle = m_bodyBall->GetAngle();
        m_ball->setPosition(QVector3D(position.x, position.y, 0.0f));
    }

    {
        b2Vec2 position = m_bodyLeftRacket->GetPosition();
        float32 angle = m_bodyLeftRacket->GetAngle();
        m_leftRacket->setPosition(QVector3D(position.x, position.y, 0.0f));
        m_leftRacket->setRotation(angle);
    }
}
