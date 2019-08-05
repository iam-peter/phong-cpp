#include "wall.h"

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/qtransform.h>

Wall::Wall(Qt3DCore::QNode* parent,
           b2World* world,
           QVector3D position,
           QVector3D scale):
    Qt3DCore::QEntity(parent),
    m_position(position),
    m_scale(scale),
    m_bodyDef(nullptr),
    m_shape(nullptr),
    m_fixtureDef(nullptr),
    m_body(nullptr)
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

    // Create the box2d bodyDef, shape, fixtureDef and body
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(m_position.x(), m_position.y());
    m_bodyDef->type = b2_staticBody;

    m_shape = new b2PolygonShape();
    m_shape->SetAsBox(m_scale.x() * 0.5f, m_scale.y() * 0.5f);

    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->shape = m_shape;
    m_fixtureDef->density = 0.0f;

    m_body = world->CreateBody(m_bodyDef);
    m_body->CreateFixture(m_fixtureDef);
}

Wall::~Wall()
{}
