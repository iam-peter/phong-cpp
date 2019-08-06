#include "racket.h"

#include <QtMath>
#include <QGeometry>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

Racket::Racket(Qt3DCore::QNode* parent,
               b2World* world,
               const QVector3D& position,
               const QVector3D& scale):
    Qt3DCore::QEntity(parent),
    m_transform(nullptr),
    m_position(position),
    m_scale(scale),
    m_rotation(0.0f),
    m_bodyDef(nullptr),
    m_shape(nullptr),
    m_fixtureDef(nullptr),
    m_body(nullptr)
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

    // Create the box2d bodyDef, shape, fixtureDef and body
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(m_position.x(), m_position.y());
    m_bodyDef->type = b2_dynamicBody;
    //m_bodyDef->bullet = true;
    m_bodyDef->linearDamping = 0.3f;
    m_bodyDef->angularDamping = 0.1f;
    m_bodyDef->gravityScale = 0.0f;

    m_shape = new b2PolygonShape();
    m_shape->SetAsBox(m_scale.x() * 0.5f, m_scale.y() * 0.5f);

    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->shape = m_shape;
    m_fixtureDef->density = 1.0f;
    m_fixtureDef->friction = 0.4f;
    m_fixtureDef->restitution = 0.8f;

    m_body = world->CreateBody(m_bodyDef);
    m_body->CreateFixture(m_fixtureDef);
}

Racket::~Racket()
{}

void Racket::setPosition(const QVector3D& position) {
    m_position = position;
    m_transform->setTranslation(m_position);
}

QVector3D Racket::position() const {
    return m_position;
}

void Racket::setScale(const QVector3D& scale) {
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

void Racket::update() {
    b2Vec2 position = m_body->GetPosition();
    float32 angle = m_body->GetAngle();
    setPosition(QVector3D(position.x, position.y, 0.0f));
    setRotation(qRadiansToDegrees(angle));
}
