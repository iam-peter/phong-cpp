TEMPLATE = app

QT += 3dextras 3dcore 3drender 3dinput 3dextras
QT += widgets

CONFIG += c++17

SOURCES += \
        ball.cpp \
        extrudedtextmesh.cpp \
        gamescene.cpp \
        introscene.cpp \
        main.cpp \
        menuscene.cpp \
        phong.cpp \
        player.cpp \
        racket.cpp \
        scene.cpp \
        wall.cpp

HEADERS += \
    ball.h \
    extrudedtextmesh.h \
    gamescene.h \
    introscene.h \
    menuscene.h \
    phong.h \
    player.h \
    racket.h \
    scene.h \
    wall.h

INCLUDEPATH += ../externals/Box2D/

LIBS += -L../lib -lexternals

TARGET = ../phong-cpp
