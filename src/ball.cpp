#include "ball.h"

#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>

Ball::Ball(Qt3DCore::QNode* parent,
           b2World* world,
           QVector3D position,
           float radius):
    Qt3DCore::QEntity(parent),
    m_transform(nullptr),
    m_position(position),
    m_radius(radius),
    m_bodyDef(nullptr),
    m_shape(nullptr),
    m_fixtureDef(nullptr),
    m_body(nullptr)
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

    // Create the box2d bodyDef, shape, fixtureDef and body
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(m_position.x(), m_position.y());
    m_bodyDef->type = b2_dynamicBody;
    m_bodyDef->bullet = true;
    m_bodyDef->linearDamping = 0.3f;
    m_bodyDef->angularDamping = 0.1f;
    m_bodyDef->gravityScale = 0.0f;

    m_shape = new b2CircleShape();
    m_shape->m_radius = m_radius;

    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->shape = m_shape;
    m_fixtureDef->density = 1.0f;
    m_fixtureDef->friction = 0.4f;
    m_fixtureDef->restitution = 0.8f;

    m_body = world->CreateBody(m_bodyDef);
    m_body->CreateFixture(m_fixtureDef);
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

void Ball::update() {
    b2Vec2 position = m_body->GetPosition();
    float32 angle = m_body->GetAngle();
    setPosition(QVector3D(position.x, position.y, 0.0f));
}
