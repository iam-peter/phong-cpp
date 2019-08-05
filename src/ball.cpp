#include "ball.h"

#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>

Ball::Ball(Qt3DCore::QNode* parent,
           QVector3D position,
           float radius):
    Qt3DCore::QEntity(parent),
    m_transform(nullptr),
    m_position(position),
    m_radius(radius),
    m_b2Shape(nullptr)
{
    // Create the entity, mesh, material and transform
    Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

    Qt3DExtras::QCylinderMesh* mesh = new Qt3DExtras::QCylinderMesh();
    mesh->setRadius(m_radius);
    mesh->setLength(0.5f);

    Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(255, 255, 0));

    m_transform = new Qt3DCore::QTransform();
    m_transform->setTranslation(m_position);
    m_transform->setRotationX(90.0f);

    entity->addComponent(mesh);
    entity->addComponent(m_transform);
    entity->addComponent(material);

    m_b2Shape = new b2CircleShape();
    m_b2Shape->m_p.Set(m_position.x(), m_position.y());
    m_b2Shape->m_radius = m_radius;
}

Ball::~Ball()
{}

void Ball::setPosition(QVector3D position) {
    m_position = position;
    m_transform->setTranslation(m_position);
}

QVector3D Ball::position() const {
    return m_position;
}

b2CircleShape* Ball::shape() {
    return m_b2Shape;
}
