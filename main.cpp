#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QRunnable>
#include <gst/gst.h>

#include "VideoSetPlaying.h"
#include "VideoPlayer.h"

int main(int argc, char *argv[])
{
  int ret;

  gst_init (&argc, &argv);

  QGuiApplication app(argc, argv);

  qmlRegisterType<VideoPlayer>("org.bluerobotics.com", 1, 0, "VideoPlayer");

  GstElement *sink = gst_element_factory_make ("qmlglsink", nullptr);
  gst_object_unref(sink);


  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


  /* find and set the videoItem on the sink */
  auto rootObject = static_cast<QQuickWindow *> (engine.rootObjects().first());
  auto videoPlayer = rootObject->findChild<QQuickItem *> ("videoPlayer");
  

  ret = app.exec();


  gst_deinit ();

  return ret;
}
