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
    m_world(nullptr)
{
    m_frameAction = new Qt3DLogic::QFrameAction(this);

    QObject::connect(this, &Scene::activeChanged,
                     this, & GameScene::handleConnections);

    // Initialize Box2D stuff
    b2Vec2 gravity(0.0f, 0.0f);
    m_world = new b2World(gravity);

    float width = 30.0f;
    float height = 20.0f;

    m_topWall = new Wall(this,
                         m_world,
                         QVector3D(0.0f, 0.5f * height, 0.0f),
                         QVector3D(width, 1.0f, 1.0f));

    m_bottomWall = new Wall(this,
                            m_world,
                            QVector3D(0.0f, -0.5f * height, 0.0f),
                            QVector3D(width, 1.0f, 1.0f));

    m_ball = new Ball(this,
                      m_world,
                      QVector3D(0.0f, 0.0f, 0.0f),
                      0.8f);

    m_leftRacket = new Racket(this,
                              m_world,
                              QVector3D(-4.0f, 0.0f, 0.0f),
                              QVector3D(1.0f, 4.0f, 1.0f));
    m_rightRacket = new Racket(this,
                               m_world,
                               QVector3D(4.0f, 0.0f, 0.0f),
                               QVector3D(1.0f, 4.0f, 1.0f));
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
            m_ball->body()->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f),
                                               m_ball->body()->GetWorldCenter(),
                                               true);
            break;
        case Qt::Key_Down:
            m_ball->body()->ApplyLinearImpulse(b2Vec2(0.0f, -1.0f),
                                               m_ball->body()->GetWorldCenter(),
                                               true);
            break;
        case  Qt::Key_Left:
            m_ball->body()->ApplyLinearImpulse(b2Vec2(-1.0f, 0.0f),
                                               m_ball->body()->GetWorldCenter(),
                                               true);
            break;
        case Qt::Key_Right:
            m_ball->body()->ApplyLinearImpulse(b2Vec2(1.0f, 0.0f),
                                               m_ball->body()->GetWorldCenter(),
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

    m_leftRacket->update();
    m_rightRacket->update();

    m_ball->update();
}
