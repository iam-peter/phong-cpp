#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "wall.h"
#include "ball.h"
#include "racket.h"
#include "player.h"

#include <QFrameAction>

#include <Box2D/Box2D.h>

class GameScene : public Scene
{
    Q_OBJECT

public:
    explicit GameScene(Qt3DCore::QNode* parent,
                       Phong* phong);
    ~GameScene();

    void keyPressed(Qt3DInput::QKeyEvent* event);
    void keyReleased(Qt3DInput::QKeyEvent* event);

    void startGameLoop();
    void stopGameLoop();

    void gameLoop(float dt);

    void scored(Player* player);

private:
    Qt3DLogic::QFrameAction* m_frameAction;

    Wall* m_topWall;
    Wall* m_bottomWall;
    Ball* m_ball;

    Racket* m_leftRacket;
    Racket* m_rightRacket;

    b2World* m_world;

    float m_stageWidth;
    float m_stageHeight;
    float m_goalDepth;

    Player* m_left;
    Player* m_right;
};

#endif // GAMESCENE_H
