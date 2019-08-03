#include "gamescene.h"
#include "phong.h"

GameScene::GameScene(Qt3DCore::QNode* parent,
                     Phong* phong):
    Scene(parent, phong),
    m_frameAction(nullptr),
    m_topWall(nullptr),
    m_bottomWall(nullptr),
    m_ball(nullptr)
{
    m_frameAction = new Qt3DLogic::QFrameAction(this);

    QObject::connect(this, &Scene::activeChanged,
                     this, & GameScene::handleConnections);

    float width = 20.0f;
    float height = 15.0f;

    m_topWall = new Wall(this,
                         QVector3D(0.0f, 0.5f * height, 0.0f),
                         QVector3D(width, 1.0f, 1.0f));

    m_bottomWall = new Wall(this,
                            QVector3D(0.0f, -0.5f * height, 0.0f),
                            QVector3D(width, 1.0f, 1.0f));

    m_ball = new Ball(this,
                      QVector3D(0.0f, 0.0f, 0.0f),
                      0.5);
}

GameScene::~GameScene()
{}

void GameScene::keyPressed(Qt3DInput::QKeyEvent* event) {
    qDebug() << Q_FUNC_INFO;

    if (event->key() == Qt::Key_Escape) {
        m_phong->previousScene();
    }

    event->setAccepted(true);
}

void GameScene::keyReleased(Qt3DInput::QKeyEvent* event) {

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
    qDebug() << "gameLoop " << dt;
}
