#ifndef WALL_H
#define WALL_H

#include <QVector3D>
#include <Qt3DCore/qentity.h>

class Wall : public Qt3DCore::QEntity
{
public:
    explicit Wall(Qt3DCore::QNode* parent,
                  QVector3D position,
                  QVector3D scale);
    ~Wall();

private:
    QVector3D m_position;
    QVector3D m_scale;
};

#endif // WALL_H
