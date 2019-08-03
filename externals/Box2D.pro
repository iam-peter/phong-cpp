QT -= core \
      gui \
      webkit

TEMPLATE = lib

CONFIG += debug staticlib warn_on

DESTDIR = lib
MOC_DIR = tmp
OBJECTS_DIR = tmp

INCLUDEPATH += ..

HEADERS += Box2D/Box2D.h \
           Box2D/Collision/*.h \
           Box2D/Collision/Shapes/*.h \
           Box2D/Common/*.h \
           Box2D/Dynamics/*.h \
           Box2D/Dynamics/Contacts/*.h \
           Box2D/Dynamics/Joints/*.h \
           Box2D/Rope/*.h

SOURCES += Box2D/Collision/*.cpp \
           Box2D/Collision/Shapes/*.cpp \
           Box2D/Common/*.cpp \
           Box2D/Dynamics/*.cpp \
           Box2D/Dynamics/Contacts/*.cpp \
           Box2D/Dynamics/Joints/*.cpp \
           Box2D/Rope/*.cpp