#ifndef RACKET_H
#define RACKET_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Box2D/Box2D.h>

class Racket : public Qt3DCore::QEntity
{
public:
    explicit Racket(Qt3DCore::QNode* parent,
                    b2World* world,
                    const QVector3D& position,
                    const QVector3D& scale);
    ~Racket();

    void setPosition(const QVector3D& position);
    QVector3D position() const;

    void setScale(const QVector3D& scale);
    QVector3D scale() const;

    void setRotation(float rotation);
    float rotation() const;

    void update();

    b2Body* body() { return m_body; }

private:
    Qt3DCore::QTransform* m_transform;

    QVector3D m_position;
    QVector3D m_scale;
    float m_rotation; // Around z-axis

    b2BodyDef* m_bodyDef;
    b2PolygonShape* m_shape;
    b2FixtureDef* m_fixtureDef;
    b2Body* m_body;
};

#endif // RACKET_H
