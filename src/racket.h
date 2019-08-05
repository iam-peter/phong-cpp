#ifndef RACKET_H
#define RACKET_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

class Racket : public Qt3DCore::QEntity
{
public:
    explicit Racket(Qt3DCore::QNode* parent,
                    QVector3D position,
                    QVector3D scale);
    ~Racket();

    void setPosition(QVector3D position);
    QVector3D position() const;

    void setScale(QVector3D scale);
    QVector3D scale() const;

    void setRotation(float rotation);
    float rotation() const;

private:
    Qt3DCore::QTransform* m_transform;

    QVector3D m_position;
    QVector3D m_scale;
    float m_rotation; // Around z-axis
};

#endif // RACKET_H
