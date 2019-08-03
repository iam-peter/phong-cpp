#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "wall.h"
#include "ball.h"

#include <QFrameAction>

class GameScene : public Scene
{
    Q_OBJECT

public:
    explicit GameScene(Qt3DCore::QNode* parent,
                       Phong* phong);
    ~GameScene();

    void keyPressed(Qt3DInput::QKeyEvent* event);
    void keyReleased(Qt3DInput::QKeyEvent* event);

    void handleConnections(bool active);
    void gameLoop(float dt);

private:
    Qt3DLogic::QFrameAction* m_frameAction;

    Wall* m_topWall;
    Wall* m_bottomWall;
    Ball* m_ball;
};

#endif // GAMESCENE_H