TEMPLATE = app

QT += qml quick widgets core

QT_CONFIG -= no-pkg-config

CONFIG += link_pkgconfig debug moc
PKGCONFIG = \
    gstreamer-1.0 \
    gstreamer-video-1.0

DEFINES += GST_USE_UNSTABLE_API

INCLUDEPATH += ../lib

SOURCES += main.cpp VideoSetPlaying.cc VideoController.cc
HEADERS += VideoSetPlaying.h VideoPlayer.h

RESOURCES += qmlsink.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
