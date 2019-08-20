#include "gamescene.h"
#include "phong.h"
#include "extrudedtextmesh.h"

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
    m_world(nullptr),
    m_stageWidth(34.0f),
    m_stageHeight(20.0f),
    m_goalDepth(4.0f),
    m_left(),
    m_right()
{
    m_frameAction = new Qt3DLogic::QFrameAction(this);

    QObject::connect(this, &Scene::activeChanged,
                     [=](bool active) {active ? startGameLoop() : stopGameLoop(); });

    m_left = new Player();
    m_left->setName("Ping");

    m_right = new Player();
    m_right->setName("Pong");

    // Initialize Box2D stuff
    b2Vec2 gravity(0.0f, 0.0f);
    m_world = new b2World(gravity);

    {
        // Left plane
        Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

        Qt3DExtras::QPlaneMesh* mesh = new Qt3DExtras::QPlaneMesh();
        mesh->setWidth(m_goalDepth);
        mesh->setHeight(m_stageHeight);

        Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
        material->setDiffuse(QColor(100.0f, 100.0f, 100.0f));

        Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
        transform->setTranslation(QVector3D((m_stageWidth * -0.5f) + (m_goalDepth * 0.5f), 0.0f, -0.5f));
        transform->setRotationX(90.0f);

        entity->addComponent(mesh);
        entity->addComponent(material);
        entity->addComponent(transform);
    }

    {
        // Right plane
        Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

        Qt3DExtras::QPlaneMesh* mesh = new Qt3DExtras::QPlaneMesh();
        mesh->setWidth(m_goalDepth);
        mesh->setHeight(m_stageHeight);

        Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
        material->setDiffuse(QColor(100.0f, 100.0f, 100.0f));

        Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
        transform->setTranslation(QVector3D((m_stageWidth * 0.5f) + (m_goalDepth * -0.5f), 0.0f, -0.5f));
        transform->setRotationX(90.0f);

        entity->addComponent(mesh);
        entity->addComponent(material);
        entity->addComponent(transform);
    }

    m_topWall = new Wall(this,
                         m_world,
                         QVector3D(0.0f, 0.5f * m_stageHeight, 0.0f),
                         QVector3D(m_stageWidth, 1.0f, 1.0f));

    m_bottomWall = new Wall(this,
                            m_world,
                            QVector3D(0.0f, -0.5f * m_stageHeight, 0.0f),
                            QVector3D(m_stageWidth, 1.0f, 1.0f));

    m_ball = new Ball(this,
                      m_world,
                      QVector3D(0.0f, 0.0f, 0.0f),
                      0.8f);
    m_ball->body()->SetLinearVelocity(b2Vec2(-10.0f, 10.0f));

    m_leftRacket = new Racket(this,
                              m_world,
                              QVector3D(-(m_stageWidth * 0.5f - m_goalDepth), 0.0f, 0.0f),
                              QVector3D(1.0f, 4.0f, 1.0f));
    m_rightRacket = new Racket(this,
                               m_world,
                               QVector3D((m_stageWidth * 0.5f - m_goalDepth), 0.0f, 0.0f),
                               QVector3D(1.0f, 4.0f, 1.0f));



    // Font
    QFont font;
    font.setCapitalization(QFont::AllUppercase);
    font.setFamily("monospace");

    // Scoreboard
    {
        Qt3DCore::QEntity* scoreBoardEntity = new Qt3DCore::QEntity(this);

        // Left player name
        {
            Qt3DCore::QEntity* playerNameEntity = new Qt3DCore::QEntity(scoreBoardEntity);

            ExtrudedTextMesh* nameMesh = new ExtrudedTextMesh(playerNameEntity);
            nameMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::Left);
            nameMesh->setText(m_left->name()); // TODO connect to nameChanged signal
            nameMesh->setDepth(0.5f);
            nameMesh->setDiffuse(QColor(255.0f, 255.0f, 255.0f));
            nameMesh->setFont(font);

            Qt3DCore::QTransform* playerNameTransform = new Qt3DCore::QTransform();
            playerNameTransform->setTranslation(QVector3D(-m_stageWidth * 0.5f,
                                                          m_stageHeight * 0.5f + 1.4f,
                                                          0.0f));

            playerNameEntity->addComponent(playerNameTransform);
        }

        // Left player score
        {
            Qt3DCore::QEntity* playerScoreEntity = new Qt3DCore::QEntity(scoreBoardEntity);

            ExtrudedTextMesh* scoreMesh = new ExtrudedTextMesh(playerScoreEntity);
            scoreMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::Right);
            scoreMesh->setText(m_left->score());
            QObject::connect(m_left, &Player::scoreChanged,
                             scoreMesh, qOverload<unsigned>(&ExtrudedTextMesh::setText));
            scoreMesh->setDepth(0.5f);
            scoreMesh->setDiffuse(QColor(255.0f, 255.0f, 255.0f));
            scoreMesh->setFont(font);

            Qt3DCore::QTransform* playerScoreTransform = new Qt3DCore::QTransform();
            playerScoreTransform->setTranslation(QVector3D(-2.0f,
                                                          m_stageHeight * 0.5f + 1.4f,
                                                          0.0f));

            playerScoreEntity->addComponent(playerScoreTransform);
        }

        // Collon
        {
            Qt3DCore::QEntity* playerNameEntity = new Qt3DCore::QEntity(scoreBoardEntity);

            ExtrudedTextMesh* nameMesh = new ExtrudedTextMesh(playerNameEntity);
            nameMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::HCenter);
            nameMesh->setText(":");
            nameMesh->setDepth(0.5f);
            nameMesh->setDiffuse(QColor(255.0f, 255.0f, 255.0f));
            nameMesh->setFont(font);

            Qt3DCore::QTransform* playerNameTransform = new Qt3DCore::QTransform();
            playerNameTransform->setTranslation(QVector3D(0.0f, m_stageHeight * 0.5f + 1.4f, 0.0f));

            playerNameEntity->addComponent(playerNameTransform);
        }

        // Right player score
        {
            Qt3DCore::QEntity* playerScoreEntity = new Qt3DCore::QEntity(scoreBoardEntity);

            ExtrudedTextMesh* scoreMesh = new ExtrudedTextMesh(playerScoreEntity);
            scoreMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::Left);
            scoreMesh->setText(m_right->score());
            QObject::connect(m_right, &Player::scoreChanged,
                             scoreMesh, qOverload<unsigned>(&ExtrudedTextMesh::setText));
            scoreMesh->setDepth(0.5f);
            scoreMesh->setDiffuse(QColor(255.0f, 255.0f, 255.0f));
            scoreMesh->setFont(font);

            Qt3DCore::QTransform* playerScoreTransform = new Qt3DCore::QTransform();
            playerScoreTransform->setTranslation(QVector3D(2.0f,
                                                           m_stageHeight * 0.5f + 1.4f,
                                                           0.0f));

            playerScoreEntity->addComponent(playerScoreTransform);
        }

        // Right player name
        {
            Qt3DCore::QEntity* playerNameEntity = new Qt3DCore::QEntity(scoreBoardEntity);

            ExtrudedTextMesh* nameMesh = new ExtrudedTextMesh(playerNameEntity);
            nameMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::Right);
            nameMesh->setText(m_right->name()); // TODO connect to nameChanged signal
            nameMesh->setDepth(0.5f);
            nameMesh->setDiffuse(QColor(255.0f, 255.0f, 255.0f));
            nameMesh->setFont(font);

            Qt3DCore::QTransform* playerNameTransform = new Qt3DCore::QTransform();
            playerNameTransform->setTranslation(QVector3D(m_stageWidth * 0.5f,
                                                          m_stageHeight * 0.5f + 1.4f,
                                                          0.0f));

            playerNameEntity->addComponent(playerNameTransform);
        }
    }
}

GameScene::~GameScene()
{}

void GameScene::keyPressed(Qt3DInput::QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            m_phong->previousScene();
            break;

        case Qt::Key_Up:
            m_leftRacket->body()->SetLinearVelocity(b2Vec2(0.0f, 20.0f));
            m_rightRacket->body()->SetLinearVelocity(b2Vec2(0.0f, 20.0f));
            break;
        case Qt::Key_Down:
            m_leftRacket->body()->SetLinearVelocity(b2Vec2(0.0f, -20.0f));
            m_rightRacket->body()->SetLinearVelocity(b2Vec2(0.0f, -20.0f));
            break;
        case Qt::Key_Left:
            m_ball->body()->ApplyLinearImpulse(b2Vec2(-1.0f, 0.0f),
                                               m_ball->body()->GetWorldCenter(),
                                               true);
            break;
        case Qt::Key_Right:
            m_ball->body()->ApplyLinearImpulse(b2Vec2(1.0f, 0.0f),
                                               m_ball->body()->GetWorldCenter(),
                                               true);
            break;

        case Qt::Key_R: // Reset ball
            m_ball->setPosition(QVector3D(0.0f, 0.0f, 0.0f));
            m_ball->body()->SetLinearVelocity(b2Vec2(-10.0f, 10.0f));
            break;
        default:
            break;
    }

    event->setAccepted(true);
}

void GameScene::keyReleased(Qt3DInput::QKeyEvent* event) {

    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
        m_leftRacket->body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        m_rightRacket->body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        break;
    default:
        break;
    }

    event->setAccepted(true);
}

void GameScene::startGameLoop() {
    QObject::connect(m_frameAction, &Qt3DLogic::QFrameAction::triggered,
                     this, &GameScene::gameLoop);
}

void GameScene::stopGameLoop() {
    QObject::disconnect(m_frameAction, &Qt3DLogic::QFrameAction::triggered,
                        this, &GameScene::gameLoop);
}

void GameScene::gameLoop(float dt) {
    int32 velocityIterations = 6;
    int32 positionIterations = 6;
    m_world->Step(dt, velocityIterations, positionIterations);

    m_leftRacket->update();
    m_rightRacket->update();

    m_ball->update();

    // Check for goal
    if (m_ball->position().x() > 0) { // on the right side
        if (m_ball->position().x() > (m_stageWidth * 0.5f) - m_goalDepth) {
            scored(m_left);
        }
    }
    else { // on the left side
        if (m_ball->position().x() < (m_stageWidth * -0.5f) + m_goalDepth) {
            scored(m_right);
        }
    }
}

void GameScene::scored(Player* player)
{
    stopGameLoop();

    player->setScore(player->score() + 1);

    // Reset ball
    m_ball->setPosition(QVector3D(0.0f, 0.0f, 0.0f));
    m_ball->body()->SetLinearVelocity(b2Vec2(-10.0f, 10.0f));

    startGameLoop();
}
