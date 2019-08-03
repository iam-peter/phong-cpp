#include "wall.h"

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/qtransform.h>

Wall::Wall(Qt3DCore::QNode* parent,
           QVector3D position,
           QVector3D scale):
    Qt3DCore::QEntity(parent),
    m_position(position),
    m_scale(scale)
{
    // Create the entity, mesh, material and transform
    Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

    Qt3DExtras::QCuboidMesh* mesh = new Qt3DExtras::QCuboidMesh();

    Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(255, 255, 255));

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
    transform->setTranslation(m_position);
    transform->setScale3D(m_scale);

    entity->addComponent(mesh);
    entity->addComponent(transform);
    entity->addComponent(material);
}

Wall::~Wall()
{}
