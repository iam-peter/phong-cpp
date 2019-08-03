#ifndef INTROSCENE_H
#define INTROSCENE_H

#include "scene.h"

class IntroScene : public Scene
{
public:
    explicit IntroScene(Qt3DCore::QNode* parent, Phong* phong);
    ~IntroScene();

    void keyPressed(Qt3DInput::QKeyEvent* event);

    void setFollowingScene(Scene* followingScene);
    Scene* followingScene() const;

private:
    Scene* m_followingScene;
};

#endif // INTROSCENE_H
