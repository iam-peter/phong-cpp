#ifndef EXTRUDEDTEXTMESH_H
#define EXTRUDEDTEXTMESH_H

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QExtrudedTextMesh>
#include <Qt3DExtras/QPhongMaterial>

class ExtrudedTextMesh : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(HorizontalAlignment m_horizontalAlignment
               READ horizontalAlignment
               WRITE setHorizontalAlignment
               NOTIFY horizontalAlignmentChanged)
    Q_PROPERTY(VerticalAlignment m_verticalAlignment
               READ verticalAlignment
               WRITE setVerticalAlignment
               NOTIFY verticalAlignmentChanged)

    Q_PROPERTY(QFont m_font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QString m_text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(float m_depth READ depth WRITE setDepth NOTIFY depthChanged)

    Q_PROPERTY(QColor m_ambient READ ambient WRITE setAmbient NOTIFY ambientChanged)
    Q_PROPERTY(QColor m_specular READ specular WRITE setSpecular NOTIFY specularChanged)
    Q_PROPERTY(QColor m_diffuse READ diffuse WRITE setDiffuse NOTIFY diffuseChanged)
    Q_PROPERTY(float m_shininess READ shininess WRITE setShininess NOTIFY shininessChanged)

public:
    enum HorizontalAlignment{ left, hcenter, right };
    enum VerticalAlignment{ top, vcenter, bottom };

    ExtrudedTextMesh(Qt3DCore::QNode* parent = nullptr);
    ~ExtrudedTextMesh();

    void setHorizontalAlignment(HorizontalAlignment value);
    HorizontalAlignment horizontalAlignment() const;

    void setVerticalAlignment(VerticalAlignment value);
    VerticalAlignment verticalAlignment() const;

    void setFont(const QFont& font);
    QFont font() const;

    void setText(const QString& text);
    QString text() const;

    void setDepth(float depth);
    float depth() const;

    void setAmbient(const QColor& ambient);
    QColor ambient() const;

    void setSpecular(const QColor& specular);
    QColor specular() const;

    void setDiffuse(const QColor& diffuse);
    QColor diffuse() const;

    void setShininess(float shininess);
    float shininess() const;

signals:
    void horizontalAlignmentChanged(HorizontalAlignment);
    void verticalAlignmentChanged(VerticalAlignment);
    void fontChanged(const QFont&);
    void textChanged(const QString&);
    void depthChanged(float);
    void ambientChanged(const QColor&);
    void specularChanged(const QColor&);
    void diffuseChanged(const QColor&);
    void shininessChanged(float);

private:
    void layout();

    Qt3DExtras::QExtrudedTextMesh* m_textMesh;
    Qt3DCore::QTransform* m_transform;
    Qt3DExtras::QPhongMaterial* m_material;

    HorizontalAlignment m_horizontalAlignment;
    VerticalAlignment m_verticalAlignment;

    QFont m_font;
    QString m_text;
    float m_depth;

    float m_width;
    float m_height;

    QColor m_ambient;
    QColor m_specular;
    QColor m_diffuse;
    float m_shininess;

    QVector3D m_position;
};

#endif // EXTRUDEDTEXTMESH_H
