#include <QGuiApplication>

#include <QtGui/QScreen>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include "phong.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(0, 0, 0));

    QWidget* container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);
    container->setWindowTitle(QStringLiteral("Phong C++"));

    Phong phong(view);

    // Show window
    container->show();
    container->resize(800, 600);

    return app.exec();
}
