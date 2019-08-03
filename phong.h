#ifndef PHONG_H
#define PHONG_H

#include <Qt3DCore/qentity.h>
#include <Qt3DInput/QInputAspect>
#include <Qt3DInput/QKeyEvent>

#include <Qt3DRender/qcamera.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/QTorusMesh>

// forward declarations
class Scene;
class IntroScene;
class MenuScene;
class GameScene;

class Phong : public QObject
{
    Q_OBJECT

public:
    explicit Phong(Qt3DExtras::Qt3DWindow* view);
    ~Phong();

    void nextScene(Scene* scene);
    void previousScene();

    void transformCamera(QVector3D position);

public slots:
    void keyPressed(Qt3DInput::QKeyEvent* event);
    void keyReleased(Qt3DInput::QKeyEvent* event);

private:
    Qt3DInput::QInputAspect* m_input;
    Qt3DCore::QEntity* m_rootEntity;
    Qt3DRender::QCamera* m_camera;
    Qt3DCore::QEntity* m_lightEntity;

    std::vector<Scene*> m_sceneStack;

    IntroScene* m_introScene;
    MenuScene* m_menuScene;
    GameScene* m_gameScene;

    Scene* m_settingsScene;

};

#endif // PHONG_H
