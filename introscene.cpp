#include "introscene.h"
#include "phong.h"

#include <Qt3DExtras/QExtrudedTextMesh>
#include <Qt3DExtras/QPhongMaterial>

IntroScene::IntroScene(Qt3DCore::QNode* parent, Phong* phong):
    Scene(parent, phong),
    m_followingScene(nullptr)
{
    // Title
    Qt3DCore::QEntity* titleEntity = new Qt3DCore::QEntity(this);

    Qt3DExtras::QExtrudedTextMesh* titleMesh = new Qt3DExtras::QExtrudedTextMesh();
    titleMesh->setText("YOOO! Title here");
    titleMesh->setDepth(0.5f);

    Qt3DCore::QTransform* titleTransform = new Qt3DCore::QTransform();
    titleTransform->setScale(2.0f);

    Qt3DExtras::QPhongMaterial* titleMaterial = new Qt3DExtras::QPhongMaterial();
    titleMaterial->setDiffuse(QColor(255, 0, 255));

    titleEntity->addComponent(titleMesh);
    titleEntity->addComponent(titleTransform);
    titleEntity->addComponent(titleMaterial);

    // Note
    Qt3DCore::QEntity* noteEntity = new Qt3DCore::QEntity(this);

    Qt3DExtras::QExtrudedTextMesh* noteMesh = new Qt3DExtras::QExtrudedTextMesh();
    noteMesh->setText("[Press any key]");
    noteMesh->setDepth(0.5f);

    Qt3DCore::QTransform* noteTransform = new Qt3DCore::QTransform();
    noteTransform->setTranslation(QVector3D(0.0f, -4.0f, 0.0f));

    Qt3DExtras::QPhongMaterial* noteMaterial = new Qt3DExtras::QPhongMaterial();
    noteMaterial->setDiffuse(QColor(200, 200, 200));

    noteEntity->addComponent(noteMesh);
    noteEntity->addComponent(noteTransform);
    noteEntity->addComponent(noteMaterial);
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
