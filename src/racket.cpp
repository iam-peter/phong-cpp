#include "racket.h"

#include <QGeometry>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

Racket::Racket(Qt3DCore::QNode* parent,
               QVector3D position,
               QVector3D scale):
    Qt3DCore::QEntity(parent),
    m_transform(nullptr),
    m_position(position),
    m_scale(scale),
    m_rotation(0.0f)
{
    // Create the entity, mesh, material and transform
    Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

    Qt3DExtras::QCuboidMesh* mesh = new Qt3DExtras::QCuboidMesh();

    Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(0, 255, 0));

    m_transform = new Qt3DCore::QTransform();
    m_transform->setTranslation(m_position);
    m_transform->setScale3D(m_scale);

    entity->addComponent(mesh);
    entity->addComponent(m_transform);
    entity->addComponent(material);
/*
    QObject::connect(mesh->geometry(), &Qt3DRender::QGeometry::minExtentChanged,
                     [](const QVector3D &minExtent) { qDebug() << "minExtent " << minExtent; });

    QObject::connect(mesh->geometry(), &Qt3DRender::QGeometry::maxExtentChanged,
                     [](const QVector3D &maxExtent) { qDebug() << "maxExtent " << maxExtent; });
*/
}

Racket::~Racket()
{}

void Racket::setPosition(QVector3D position) {
    m_position = position;
    m_transform->setTranslation(m_position);
}

QVector3D Racket::position() const {
    return m_position;
}

void Racket::setScale(QVector3D scale) {
    m_scale = scale;
    m_transform->setScale3D(m_scale);
}

QVector3D Racket::scale() const {
    return m_scale;
}

void Racket::setRotation(float rotation) {
    m_rotation = rotation;
    m_transform->setRotationZ(m_rotation);
}

float Racket::rotation() const {
    return m_rotation;
}
