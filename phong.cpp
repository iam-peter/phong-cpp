#include "phong.h"
#include "introscene.h"
#include "menuscene.h"
#include "gamescene.h"

#include <QKeyboardDevice>
#include <QKeyboardHandler>

#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPhongMaterial>

Phong::Phong(Qt3DExtras::Qt3DWindow* view):
    m_input(nullptr),
    m_rootEntity(nullptr),
    m_camera(nullptr),
    m_lightEntity(nullptr),
    m_introScene(nullptr),
    m_menuScene(nullptr)
{
    m_input = new Qt3DInput::QInputAspect();
    view->registerAspect(m_input);

    // Root entity
    m_rootEntity = new Qt3DCore::QEntity();

    // Camera
    m_camera = view->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0.0f, 0.0f, 34.0f));
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(m_rootEntity);

    Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);

    Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(m_camera->position());

    lightEntity->addComponent(light);
    lightEntity->addComponent(lightTransform);

    Qt3DInput::QKeyboardDevice* keyboardDevice = new Qt3DInput::QKeyboardDevice(m_rootEntity);
    Qt3DInput::QKeyboardHandler* keyboardHandler = new Qt3DInput::QKeyboardHandler(m_rootEntity);
    keyboardHandler->setSourceDevice(keyboardDevice);
    keyboardHandler->setFocus(true);

    QObject::connect(keyboardHandler, &Qt3DInput::QKeyboardHandler::pressed,
                     this, &Phong::keyPressed);
    QObject::connect(keyboardHandler, &Qt3DInput::QKeyboardHandler::released,
                     this, &Phong::keyReleased);

    // Initialize scenes
    m_settingsScene = new Scene(m_rootEntity, this);
    m_settingsScene->setName("Settings");
    m_settingsScene->setPosition(QVector3D(00.0f, 30.0f, 0.0f));

    m_gameScene = new GameScene(m_rootEntity, this);
    m_gameScene->setName("Play");
    m_gameScene->setPosition(QVector3D(30.0f, 0.0f, 0.0f));

    m_menuScene = new MenuScene(m_rootEntity, this, {m_gameScene, m_settingsScene});
    m_menuScene->setPosition(QVector3D(0.0f, 0.0f, 0.0f));

    m_introScene = new IntroScene(m_rootEntity, this);
    m_introScene->setPosition(QVector3D(-30.0f, 0.0f, 0.0f));
    m_introScene->setFollowingScene(m_menuScene);

    // Set root object of the view/window
    view->setRootEntity(m_rootEntity);

    // Push first scene to stack
    nextScene(m_introScene);
}

Phong::~Phong()
{
    qDebug() << "Phong destruction";
}

void Phong::nextScene(Scene* scene)
{
    qDebug() << Q_FUNC_INFO;

    Scene* nextScene = scene;

    if (m_sceneStack.size()) {
        Scene* currScene = m_sceneStack.back();
        currScene->setActive(false);
    }

    // Transform camera
    transformCamera(nextScene->position());

    // Push next scene to stack
    m_sceneStack.push_back(nextScene);
    nextScene->setActive(true);
}

void Phong::previousScene()
{
    // Pop current scene of stack
    Scene* currScene = m_sceneStack.back();
    m_sceneStack.pop_back();
    currScene->setActive(false);

    // Set remaining scene as current
    if (m_sceneStack.size()) {
        Scene* prevScene = m_sceneStack.back();
        prevScene->setActive(true);

        // Transform camera
        transformCamera(prevScene->position());
    }
}

void Phong::transformCamera(QVector3D position) {
    m_camera->setViewCenter(position);
    m_camera->setPosition(position + QVector3D(0.0f, 0.0f, 34.0f));
}

void Phong::keyPressed(Qt3DInput::QKeyEvent* event)
{
    qDebug() << Q_FUNC_INFO << " " << event->key();

    if (m_sceneStack.empty())
        return;

    m_sceneStack.back()->keyPressed(event);
}

void Phong::keyReleased(Qt3DInput::QKeyEvent* event)
{
    qDebug() << Q_FUNC_INFO << " " << event->key();

    if (m_sceneStack.empty())
        return;

    m_sceneStack.back()->keyReleased(event);
}
