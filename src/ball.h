#ifndef BALL_H
#define BALL_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Box2D/Box2D.h>

class Ball : public Qt3DCore::QEntity
{
public:
    explicit Ball(Qt3DCore::QNode* parent,
                  b2World* world,
                  QVector3D position,
                  float radius);
    ~Ball();

    void setPosition(QVector3D position);
    QVector3D position() const;

    void update();

    b2Body* body() { return m_body; }

private:
    Qt3DCore::QTransform* m_transform;

    QVector3D m_position;
    float m_radius;

    b2BodyDef* m_bodyDef;
    b2CircleShape* m_shape;
    b2FixtureDef* m_fixtureDef;
    b2Body* m_body;
};

#endif // BALL_H
