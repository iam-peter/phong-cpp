#ifndef SCENE_H
#define SCENE_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DInput/QKeyEvent>

class Phong;

class Scene : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D m_position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool m_active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit Scene(Qt3DCore::QNode* parent, Phong* phong);
    ~Scene();

    virtual void keyPressed(Qt3DInput::QKeyEvent* event);
    virtual void keyReleased(Qt3DInput::QKeyEvent* event);

    void setPosition(const QVector3D& position);
    QVector3D position() const;

    void setName(const QString& name);
    QString name() const;

    void setActive(bool active);
    bool active() const;

signals:
    void positionChanged(const QVector3D&);
    void nameChanged(const QString&);
    void activeChanged(bool);

protected:
    QVector3D m_position;
    QString m_name;
    bool m_active;
    Qt3DCore::QTransform* m_transform;

    Phong* m_phong; // pointer to 'parent' (e.g. camera access)
};

#endif // SCENE_H
