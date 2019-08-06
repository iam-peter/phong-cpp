#include "scene.h"
#include "phong.h"

Scene::Scene(Qt3DCore::QNode* parent, Phong* phong):
    Qt3DCore::QEntity(parent),
    m_position(QVector3D()),
    m_name(QString("none")),
    m_active(false),
    m_phong(phong)
{
    m_transform = new Qt3DCore::QTransform();
    QObject::connect(this, &Scene::positionChanged,
                     m_transform, &Qt3DCore::QTransform::setTranslation);

    addComponent(m_transform);
}

Scene::~Scene()
{}

void Scene::keyPressed(Qt3DInput::QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        m_phong->previousScene();
    }

    event->setAccepted(true);
}

void Scene::keyReleased(Qt3DInput::QKeyEvent* event)
{
    event->setAccepted(true);
}

void Scene::setPosition(const QVector3D& position)
{
    m_position = position;
    emit positionChanged(position);
}

QVector3D Scene::position() const
{
    return m_position;
}

void Scene::setName(const QString& name)
{
    m_name = name;
    emit nameChanged(name);
}

QString Scene::name() const
{
    return m_name;
}

void Scene::setActive(bool active)
{
    m_active = active;
    emit activeChanged(active);
}

bool Scene::active() const
{
    return m_active;
}
