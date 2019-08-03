#include "ball.h"

#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/qtransform.h>

Ball::Ball(Qt3DCore::QNode* parent,
           QVector3D position,
           float radius):
    Qt3DCore::QEntity(parent),
    m_position(position),
    m_radius(radius)
{
    // Create the entity, mesh, material and transform
    Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

    Qt3DExtras::QCylinderMesh* mesh = new Qt3DExtras::QCylinderMesh();
    mesh->setRadius(m_radius);
    mesh->setLength(0.5f);

    Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(255, 255, 0));

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
    transform->setTranslation(m_position);
    transform->setRotationX(90.0f);

    entity->addComponent(mesh);
    entity->addComponent(transform);
    entity->addComponent(material);
}

Ball::~Ball()
{}
