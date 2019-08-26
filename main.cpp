#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QRunnable>
#include <gst/gst.h>

#include "VideoSetPlaying.h"
#include "VideoController.h"

int main(int argc, char *argv[])
{
  int ret;

  gst_init (&argc, &argv);

  QGuiApplication app(argc, argv);

  qmlRegisterType<VideoController>("org.bluerobotics.com", 1, 0, "VideoController");

  // This is just so I have the Qml item registered.
  GstElement *sink = gst_element_factory_make ("qmlglsink", nullptr);
  gst_object_unref(sink);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  ret = app.exec();
  gst_deinit ();

  return ret;
}
