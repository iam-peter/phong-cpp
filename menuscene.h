#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "scene.h"

class MenuScene : public Scene
{
    Q_OBJECT
    Q_PROPERTY(int m_currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)

public:
    explicit MenuScene(Qt3DCore::QNode* parent,
                       Phong* phong,
                       const std::vector<Scene*>& menuScenes);
    ~MenuScene();

    void keyPressed(Qt3DInput::QKeyEvent* event);

    void setCurrentItem(int currentItem);
    int currentItem() const;

signals:
    void currentItemChanged(int);

private:
    std::vector<Scene*> m_menuScenes;

    Qt3DCore::QTransform* m_indicatorTransform;

    int m_currentItem;
};

#endif // MENUSCENE_H
