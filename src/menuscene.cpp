#include "menuscene.h"
#include "phong.h"
#include "extrudedtextmesh.h"

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <algorithm>

MenuScene::MenuScene(Qt3DCore::QNode* parent,
                     Phong* phong,
                     const std::vector<Scene*>& menuScenes):
    Scene(parent, phong),
    m_menuScenes(menuScenes),
    m_currentItem(0)
{
    // Font
    QFont font;
    font.setCapitalization(QFont::AllUppercase);
    font.setFamily("monospace");

    // Title
    Qt3DCore::QEntity* titleEntity = new Qt3DCore::QEntity(this);

    ExtrudedTextMesh* titleMesh = new ExtrudedTextMesh(titleEntity);
    titleMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::hcenter);
    titleMesh->setText("P(h)ong");
    titleMesh->setDepth(0.5f);
    titleMesh->setDiffuse(QColor(255, 0, 255));
    titleMesh->setFont(font);

    Qt3DCore::QTransform* titleTransform = new Qt3DCore::QTransform();
    titleTransform->setScale(2.0f);
    titleTransform->setTranslation(QVector3D(0.0f, 2.0f, 0.0f));

    titleEntity->addComponent(titleTransform);

    // Create menu items
    for (unsigned i = 0u; i != m_menuScenes.size(); ++i) {
        Scene* scene = m_menuScenes[i];

        Qt3DCore::QEntity* itemEntity = new Qt3DCore::QEntity(this);

        ExtrudedTextMesh* itemMesh = new ExtrudedTextMesh(itemEntity);
        itemMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::hcenter);
        itemMesh->setText(scene->name());
        itemMesh->setDepth(0.5f);
        itemMesh->setDiffuse(QColor(255, 255, 255));
        itemMesh->setFont(font);

        Qt3DCore::QTransform* itemTransform = new Qt3DCore::QTransform();
        itemTransform->setTranslation(QVector3D(0.0f, i * -2.0f, 0.0f));

        itemEntity->addComponent(itemTransform);
    }

    // Create item indicator
    Qt3DCore::QEntity* itemIndicator = new Qt3DCore::QEntity(this);

    Qt3DExtras::QCylinderMesh* indicatorMesh = new Qt3DExtras::QCylinderMesh();
    indicatorMesh->setRadius(0.4f);
    indicatorMesh->setLength(0.5f);

    Qt3DExtras::QPhongMaterial* indicatorMaterial = new Qt3DExtras::QPhongMaterial();
    indicatorMaterial->setDiffuse(QColor(255, 0, 0));

    m_indicatorTransform = new Qt3DCore::QTransform();
    m_indicatorTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    m_indicatorTransform->setRotationX(90.0f);

    itemIndicator->addComponent(indicatorMesh);
    itemIndicator->addComponent(m_indicatorTransform);
    itemIndicator->addComponent(indicatorMaterial);

    QObject::connect(this, &MenuScene::currentItemChanged,
                     [=](int idx) { m_indicatorTransform->setTranslation(QVector3D(0.0f, idx * -2.0f, 0.0f)); });
}

MenuScene::~MenuScene()
{}

void MenuScene::keyPressed(Qt3DInput::QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
            m_phong->previousScene();
            break;
        case Qt::Key_Up:
            setCurrentItem(std::clamp(m_currentItem - 1, 0, int(m_menuScenes.size()) - 1));
            break;
        case Qt::Key_Down:
            setCurrentItem(std::clamp(m_currentItem + 1, 0, int(m_menuScenes.size()) - 1));
            break;

        case Qt::Key_Enter:
        case Qt::Key_Return:
            m_phong->nextScene(m_menuScenes[m_currentItem]); // TODO implicit conversion
            break;

        default:
            qDebug() << Q_FUNC_INFO << " Unhandled key pressed.";
    }
}

void MenuScene::setCurrentItem(int currentItem)
{
    m_currentItem = currentItem;
    emit currentItemChanged(currentItem);
}

int MenuScene::currentItem() const
{
    return m_currentItem;
}
