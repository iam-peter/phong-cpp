#include "ball.h"

#include <QtMath>
#include <Qt3DExtras/QPhongMaterial>

Ball::Ball(Qt3DCore::QNode* parent,
           b2World* world,
           const QVector3D& position,
           float radius):
    Qt3DCore::QEntity(parent),
    m_transform(nullptr),
    m_mesh(nullptr),
    m_position(position),
    m_radius(radius),
    m_rotation(0.0f),
    m_bodyDef(nullptr),
    m_shape(nullptr),
    m_fixtureDef(nullptr),
    m_body(nullptr)
{
    // Create the entity, mesh, material and transform
    Qt3DCore::QEntity* entity = new Qt3DCore::QEntity(this);

    m_transform = new Qt3DCore::QTransform();
    m_transform->setTranslation(m_position);

    entity->addComponent(m_transform);

    {
        // Encapsulate another entity to make rotation around z-axis working
        Qt3DCore::QEntity* tmpEntity = new Qt3DCore::QEntity(entity);

        m_mesh = new Qt3DExtras::QCylinderMesh();
        m_mesh->setRadius(m_radius);
        m_mesh->setLength(0.5f);

        Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
        material->setDiffuse(QColor(255.0f, 255.0f, 0.0f));

        Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
        transform->setRotationX(90.0f);

        tmpEntity->addComponent(m_mesh);
        tmpEntity->addComponent(material);
        tmpEntity->addComponent(transform);
    }

    // Create the box2d bodyDef, shape, fixtureDef and body
    m_bodyDef = new b2BodyDef();
    m_bodyDef->type = b2_dynamicBody;
    //m_bodyDef->bullet = true;
    m_bodyDef->linearDamping = 0.0f;
    m_bodyDef->angularDamping = 0.05f;
    m_bodyDef->gravityScale = 0.0f;

    m_shape = new b2CircleShape();
    m_shape->m_radius = m_radius;

    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->shape = m_shape;
    m_fixtureDef->density = 0.0f;
    m_fixtureDef->friction = 0.0f;
    m_fixtureDef->restitution = 1.0f;

    m_body = world->CreateBody(m_bodyDef);
    m_body->CreateFixture(m_fixtureDef);
    m_body->SetTransform(b2Vec2(m_position.x(), m_position.y()),
                         qDegreesToRadians(m_rotation));
}

Ball::~Ball()
{}

void Ball::setPosition(const QVector3D& position) {
    m_position = position;
    m_transform->setTranslation(m_position);
    m_body->SetTransform(b2Vec2(m_position.x(), m_position.y()),
                         qDegreesToRadians(m_rotation));
}

QVector3D Ball::position() const {
    return m_position;
}

void Ball::setRadius(float radius) {
    m_radius = radius;
    m_mesh->setRadius(m_radius);
    m_shape->m_radius = m_radius;
}

float Ball::radius() const {
    return m_radius;
}

void Ball::setRotation(float rotation) {
    m_rotation = rotation;
    m_transform->setRotationZ(m_rotation);
    m_body->SetTransform(b2Vec2(m_position.x(), m_position.y()),
                         qDegreesToRadians(m_rotation));
}

float Ball::rotation() const {
    return m_rotation;
}

void Ball::update() {
    b2Vec2 position = m_body->GetPosition();
    float32 angle = m_body->GetAngle();

    // Set position
    m_position = QVector3D(position.x, position.y, 0.0f);
    m_transform->setTranslation(m_position);

    // Set rotation
    m_rotation = qRadiansToDegrees(angle);
    m_transform->setRotationZ(m_rotation);
}
