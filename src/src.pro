TEMPLATE = app

QT += 3dextras 3dcore 3drender 3dinput 3dextras
QT += widgets

CONFIG += c++17

SOURCES += \
        ball.cpp \
        gamescene.cpp \
        introscene.cpp \
        main.cpp \
        menuscene.cpp \
        phong.cpp \
        racket.cpp \
        scene.cpp \
        wall.cpp

HEADERS += \
    ball.h \
    gamescene.h \
    introscene.h \
    menuscene.h \
    phong.h \
    racket.h \
    scene.h \
    wall.h

INCLUDEPATH += ../externals/Box2D/

LIBS += -L../lib -lexternals

TARGET = ../phong-cpp
