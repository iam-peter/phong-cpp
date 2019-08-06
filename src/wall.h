#ifndef WALL_H
#define WALL_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>

#include <Box2D/Box2D.h>

class Wall : public Qt3DCore::QEntity
{
public:
    explicit Wall(Qt3DCore::QNode* parent,
                  b2World* world,
                  const QVector3D& position,
                  const QVector3D& scale);
    ~Wall();

    void update();

    b2Body* body() { return m_body; }

private:
    QVector3D m_position;
    QVector3D m_scale;

    b2BodyDef* m_bodyDef;
    b2PolygonShape* m_shape;
    b2FixtureDef* m_fixtureDef;
    b2Body* m_body;
};

#endif // WALL_H
