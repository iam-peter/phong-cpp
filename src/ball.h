#ifndef BALL_H
#define BALL_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Box2D/Collision/Shapes/b2CircleShape.h>

class Ball : public Qt3DCore::QEntity
{
public:
    explicit Ball(Qt3DCore::QNode* parent,
                  QVector3D position,
                  float radius);
    ~Ball();

    void setPosition(QVector3D position);
    QVector3D position() const;

    b2CircleShape* shape();

private:
    Qt3DCore::QTransform* m_transform;

    QVector3D m_position;
    float m_radius;

    b2CircleShape* m_b2Shape;
};

#endif // BALL_H
