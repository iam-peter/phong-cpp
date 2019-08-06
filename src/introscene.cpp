#include "introscene.h"
#include "phong.h"
#include "extrudedtextmesh.h"

#include <Qt3DExtras/QPhongMaterial>

IntroScene::IntroScene(Qt3DCore::QNode* parent, Phong* phong):
    Scene(parent, phong),
    m_followingScene(nullptr)
{
    // Font
    QFont font;
    //font.setCapitalization(QFont::AllUppercase);
    font.setFamily("monospace");
    font.setPointSize(20.0f);

    // Title
    Qt3DCore::QEntity* titleEntity = new Qt3DCore::QEntity(this);

    ExtrudedTextMesh* titleMesh = new ExtrudedTextMesh(titleEntity);
    titleMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::hcenter);
    titleMesh->setText("YOOO! Title here");
    titleMesh->setDepth(0.5f);
    titleMesh->setDiffuse(QColor(255.0f, 0.0f, 255.0f));
    titleMesh->setFont(font);

    Qt3DCore::QTransform* titleTransform = new Qt3DCore::QTransform();
    titleTransform->setScale(2.0f);

    titleEntity->addComponent(titleTransform);

    // Note
    Qt3DCore::QEntity* noteEntity = new Qt3DCore::QEntity(this);

    ExtrudedTextMesh* noteMesh = new ExtrudedTextMesh(noteEntity);
    noteMesh->setHorizontalAlignment(ExtrudedTextMesh::HorizontalAlignment::hcenter);
    noteMesh->setText("[Press any key]");
    noteMesh->setDepth(0.5f);
    noteMesh->setDiffuse(QColor(255.0f, 255.0f, 255.0f));

    Qt3DCore::QTransform* noteTransform = new Qt3DCore::QTransform();
    noteTransform->setTranslation(QVector3D(0.0f, -4.0f, 0.0f));

    noteEntity->addComponent(noteTransform);
}

IntroScene::~IntroScene()
{}

void IntroScene::keyPressed(Qt3DInput::QKeyEvent* event)
{
    qDebug() << Q_FUNC_INFO;

    if (event->key() != Qt::Key_Escape) {
        m_phong->nextScene(m_followingScene);
    }
}

void IntroScene::setFollowingScene(Scene* followingScene) {
    m_followingScene = followingScene;
}

Scene* IntroScene::followingScene() const {
    return m_followingScene;
}
