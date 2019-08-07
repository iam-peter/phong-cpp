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
    m_lightTransform(nullptr),
    m_introScene(nullptr),
    m_menuScene(nullptr),
    m_gameScene(nullptr),
    m_settingsScene(nullptr),
    m_animationGroup(nullptr),
    m_cameraPositionAnimation(nullptr),
    m_cameraViewCenterAnimation(nullptr),
    m_lightTransformAnimation(nullptr)
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

    m_lightTransform = new Qt3DCore::QTransform(lightEntity);
    m_lightTransform->setTranslation(m_camera->position());

    lightEntity->addComponent(light);
    lightEntity->addComponent(m_lightTransform);

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
    m_settingsScene->setPosition(QVector3D(00.0f, 40.0f, 0.0f));

    m_gameScene = new GameScene(m_rootEntity, this);
    m_gameScene->setName("Play");
    m_gameScene->setPosition(QVector3D(40.0f, 0.0f, 0.0f));

    m_menuScene = new MenuScene(m_rootEntity, this, {m_gameScene, m_settingsScene});
    m_menuScene->setPosition(QVector3D(0.0f, 0.0f, 0.0f));

    m_introScene = new IntroScene(m_rootEntity, this);
    m_introScene->setPosition(QVector3D(-40.0f, 0.0f, 0.0f));
    m_introScene->setFollowingScene(m_menuScene);

    // Set root object of the view/window
    view->setRootEntity(m_rootEntity);

    // Setup animations
    m_animationGroup = new QParallelAnimationGroup();
    m_cameraPositionAnimation = new QPropertyAnimation(m_camera, "position");
    m_cameraViewCenterAnimation = new QPropertyAnimation(m_camera, "viewCenter");
    m_lightTransformAnimation = new QPropertyAnimation(m_lightTransform, "translation");

    m_animationGroup->addAnimation(m_cameraPositionAnimation);
    m_animationGroup->addAnimation(m_cameraViewCenterAnimation);
    m_animationGroup->addAnimation(m_lightTransformAnimation);

    // Push first scene to stack
    nextScene(m_introScene);
}

Phong::~Phong()
{
    qDebug() << "Phong destruction";
}

void Phong::nextScene(Scene* scene)
{
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

        // Transform camera
        transformCamera(prevScene->position());

        prevScene->setActive(true);
    }
}

void Phong::transformCamera(const QVector3D& position) {
    // Stop potentially running animation
    if (m_animationGroup->state() == QAbstractAnimation::State::Running)
        m_animationGroup->stop();

    m_cameraViewCenterAnimation->setStartValue(m_camera->viewCenter());
    m_cameraViewCenterAnimation->setEndValue(position);

    m_cameraPositionAnimation->setStartValue(m_camera->position());
    m_cameraPositionAnimation->setEndValue(position + QVector3D(0.0f, 0.0f, 34.0f));

    m_lightTransformAnimation->setStartValue(m_camera->position());
    m_lightTransformAnimation->setEndValue(position + QVector3D(0.0f, 0.0f, 34.0f));

    m_animationGroup->start();
}

void Phong::keyPressed(Qt3DInput::QKeyEvent* event)
{
    if (m_sceneStack.empty())
        return;

    m_sceneStack.back()->keyPressed(event);
}

void Phong::keyReleased(Qt3DInput::QKeyEvent* event)
{
    if (m_sceneStack.empty())
        return;

    m_sceneStack.back()->keyReleased(event);
}
