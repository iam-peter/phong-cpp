#include "extrudedtextmesh.h"

ExtrudedTextMesh::ExtrudedTextMesh(Qt3DCore::QNode* parent):
    Qt3DCore::QEntity(parent),
    m_textMesh(nullptr),
    m_transform(nullptr),
    m_material(nullptr),
    m_horizontalAlignment(HorizontalAlignment::Left),
    m_verticalAlignment(VerticalAlignment::Bottom),
    m_font(QFont()),
    m_text(QString()),
    m_depth(0.5f),
    m_width(0.0f),
    m_height(0.0f),
    m_ambient(QColor()),
    m_specular(QColor()),
    m_diffuse(QColor()),
    m_shininess(0.0f),
    m_position(0.0f, 0.0f, 0.0f)
{
    m_textMesh = new Qt3DExtras::QExtrudedTextMesh();
    m_transform = new Qt3DCore::QTransform();
    m_material = new Qt3DExtras::QPhongMaterial();
    m_material->setAmbient(m_ambient);
    m_material->setSpecular(m_specular);
    m_material->setDiffuse(m_diffuse);
    m_material->setShininess(m_shininess);

    addComponent(m_textMesh);
    addComponent(m_transform);
    addComponent(m_material);

    QObject::connect(m_textMesh->geometry(), &Qt3DRender::QGeometry::minExtentChanged,
                     this, &ExtrudedTextMesh::layout);
    QObject::connect(m_textMesh->geometry(), &Qt3DRender::QGeometry::maxExtentChanged,
                     this, &ExtrudedTextMesh::layout);

    QObject::connect(this, &ExtrudedTextMesh::horizontalAlignmentChanged,
                     this, &ExtrudedTextMesh::layout);
    QObject::connect(this, &ExtrudedTextMesh::verticalAlignmentChanged,
                     this, &ExtrudedTextMesh::layout);

    QObject::connect(this, &ExtrudedTextMesh::fontChanged,
                     m_textMesh, &Qt3DExtras::QExtrudedTextMesh::setFont);
    QObject::connect(this, &ExtrudedTextMesh::textChanged,
                     m_textMesh, &Qt3DExtras::QExtrudedTextMesh::setText);
    QObject::connect(this, &ExtrudedTextMesh::depthChanged,
                     m_textMesh, &Qt3DExtras::QExtrudedTextMesh::setDepth);

    QObject::connect(this, &ExtrudedTextMesh::ambientChanged,
                     m_material, &Qt3DExtras::QPhongMaterial::setAmbient);
    QObject::connect(this, &ExtrudedTextMesh::specularChanged,
                     m_material, &Qt3DExtras::QPhongMaterial::setSpecular);
    QObject::connect(this, &ExtrudedTextMesh::diffuseChanged,
                     m_material, &Qt3DExtras::QPhongMaterial::setDiffuse);
    QObject::connect(this, &ExtrudedTextMesh::shininessChanged,
                     m_material, &Qt3DExtras::QPhongMaterial::setShininess);
}

ExtrudedTextMesh::~ExtrudedTextMesh()
{}

void ExtrudedTextMesh::setHorizontalAlignment(HorizontalAlignment value)
{
    m_horizontalAlignment = value;
    emit horizontalAlignmentChanged(value);
}

ExtrudedTextMesh::HorizontalAlignment ExtrudedTextMesh::horizontalAlignment() const
{
    return m_horizontalAlignment;
}

void ExtrudedTextMesh::setVerticalAlignment(VerticalAlignment value)
{
    m_verticalAlignment = value;
    emit verticalAlignmentChanged(value);
}

ExtrudedTextMesh::VerticalAlignment ExtrudedTextMesh::verticalAlignment() const
{
    return m_verticalAlignment;
}

void ExtrudedTextMesh::setFont(const QFont& font)
{
    m_font = font;
    emit fontChanged(font);
}

QFont ExtrudedTextMesh::font() const
{
    return m_font;
}

void ExtrudedTextMesh::setText(const QString& text)
{
    m_text = text;
    emit textChanged(text);
}

void ExtrudedTextMesh::setText(unsigned text)
{
    setText(QString::number(text));
}

QString ExtrudedTextMesh::text() const
{
    return m_text;
}

void ExtrudedTextMesh::setDepth(float depth)
{
    m_depth = depth;
    emit depthChanged(depth);
}

float ExtrudedTextMesh::depth() const
{
    return m_depth;
}

void ExtrudedTextMesh::setAmbient(const QColor& ambient)
{
    m_ambient = ambient;
    emit ambientChanged(ambient);
}

QColor ExtrudedTextMesh::ambient() const
{
    return m_ambient;
}

void ExtrudedTextMesh::setSpecular(const QColor& specular)
{
    m_specular = specular;
    emit specularChanged(specular);
}

QColor ExtrudedTextMesh::specular() const
{
    return m_specular;
}

void ExtrudedTextMesh::setDiffuse(const QColor& diffuse)
{
    m_diffuse = diffuse;
    emit diffuseChanged(diffuse);
}

QColor ExtrudedTextMesh::diffuse() const
{
    return m_diffuse;
}

void ExtrudedTextMesh::setShininess(float shininess)
{
    m_shininess = shininess;
    emit shininessChanged(shininess);
}

float ExtrudedTextMesh::shininess() const
{
    return m_shininess;
}

void ExtrudedTextMesh::layout()
{
    m_width = m_textMesh->geometry()->maxExtent().x() - m_textMesh->geometry()->minExtent().x();
    m_height = m_textMesh->geometry()->maxExtent().y() - m_textMesh->geometry()->minExtent().y();

    if (m_horizontalAlignment == HorizontalAlignment::Right)
        m_position.setX(-m_width);
    else if (m_horizontalAlignment == HorizontalAlignment::HCenter)
        m_position.setX(m_width * -0.5f);
    else
        m_position.setX(0.0f);

    if (m_verticalAlignment == VerticalAlignment::Top)
        m_position.setY(-m_height);
    else if (m_verticalAlignment == VerticalAlignment::VCenter)
        m_position.setY(m_height * -0.5f);
    else
        m_position.setY(0.0f);

    m_transform->setTranslation(m_position);
}
