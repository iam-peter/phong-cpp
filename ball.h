#ifndef BALL_H
#define BALL_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>

class Ball : public Qt3DCore::QEntity
{
public:
    explicit Ball(Qt3DCore::QNode* parent,
                  QVector3D position,
                  float radius);
    ~Ball();

private:
    QVector3D m_position;
    float m_radius;
};

#endif // BALL_H
