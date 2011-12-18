QT += core \
    gui \
    opengl
TARGET = rollercoaster
TEMPLATE = app
INCLUDEPATH += lab \
    lib \
    math \
    support \
    game \
    sweepprune
DEPENDPATH += lab \
    lib \
    math \
    support \
    game \
    sweepprune
HEADERS += lab/glwidget.h \
    lib/targa.h \
    lib/glm.h \
    support/resourceloader.h \
    support/mainwindow.h \
    support/camera.h \
    lib/targa.h \
    sweepprune/SweepPruner.h \
    sweepprune/CollisionPair.h \
    sweepprune/BoundingBox.h \
    game/gameengine.h \
    game/gameobject.h \
    game/beziercurve.h \
    sweepprune/dimensionpoint.h \
    game/particleemitter.h \
    game/projectile.h \
    game/explosion.h \
    game/projectiletrail.h \
    math/vector.h \
    math/matrix3x3.h \
    sweepprune/paircomparator.h
SOURCES += lab/glwidget.cpp \
    lib/targa.cpp \
    lib/glm.cpp \
    support/resourceloader.cpp \
    support/mainwindow.cpp \
    support/main.cpp \
    support/camera.cpp \
    sweepprune/SweepPruner.cpp \
    sweepprune/CollisionPair.cpp \
    sweepprune/BoundingBox.cpp \
    game/gameengine.cpp \
    game/gameobject.cpp \
    game/beziercurve.cpp \
    game/particleemitter.cpp \
    game/projectile.cpp \
    game/explosion.cpp \
    game/projectiletrail.cpp \
    math/matrix3x3.inl
FORMS += mainwindow.ui \
    support/mainwindow.ui
OTHER_FILES += shaders/refract.vert \
    shaders/refract.frag \
    shaders/reflect.vert \
    shaders/reflect.frag \
    shaders/brightpass.frag \
    shaders/blur.frag
RESOURCES += 
