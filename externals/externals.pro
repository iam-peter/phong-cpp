TEMPLATE = lib

QT -= core \
      gui \
      webkit

CONFIG += debug staticlib warn_on

DESTDIR = ../lib

INCLUDEPATH += Box2D/

HEADERS += Box2D/Box2D/Box2D.h \
           Box2D/Box2D/Collision/*.h \
           Box2D/Box2D/Collision/Shapes/*.h \
           Box2D/Box2D/Common/*.h \
           Box2D/Box2D/Dynamics/*.h \
           Box2D/Box2D/Dynamics/Contacts/*.h \
           Box2D/Box2D/Dynamics/Joints/*.h \
           Box2D/Box2D/Rope/*.h

SOURCES += Box2D/Box2D/Collision/*.cpp \
           Box2D/Box2D/Collision/Shapes/*.cpp \
           Box2D/Box2D/Common/*.cpp \
           Box2D/Box2D/Dynamics/*.cpp \
           Box2D/Box2D/Dynamics/Contacts/*.cpp \
           Box2D/Box2D/Dynamics/Joints/*.cpp \
           Box2D/Box2D/Rope/*.cpp
