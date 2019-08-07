#include "gamescene.h"
#include "phong.h"

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>

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

    float goalWidth = 4.0f;

    {
        // Left plane
        Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

        Qt3DExtras::QPlaneMesh* mesh = new Qt3DExtras::QPlaneMesh();
        mesh->setWidth(goalWidth);
        mesh->setHeight(height);

        Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
        material->setDiffuse(QColor(100.0f, 100.0f, 100.0f));

        Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
        transform->setTranslation(QVector3D((width * -0.5f) + (goalWidth * 0.5f), 0.0f, -0.5f));
        transform->setRotationX(90.0f);

        entity->addComponent(mesh);
        entity->addComponent(material);
        entity->addComponent(transform);
    }

    {
        // Right plane
        Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

        Qt3DExtras::QPlaneMesh* mesh = new Qt3DExtras::QPlaneMesh();
        mesh->setWidth(goalWidth);
        mesh->setHeight(height);

        Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
        material->setDiffuse(QColor(100.0f, 100.0f, 100.0f));

        Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
        transform->setTranslation(QVector3D((width * 0.5f) + (goalWidth * -0.5f), 0.0f, -0.5f));
        transform->setRotationX(90.0f);

        entity->addComponent(mesh);
        entity->addComponent(material);
        entity->addComponent(transform);
    }

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
    int32 positionIterations = 6;
    m_world->Step(dt, velocityIterations, positionIterations);

    m_leftRacket->update();
    m_rightRacket->update();

    m_ball->update();
}
