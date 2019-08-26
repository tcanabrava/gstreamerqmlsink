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
  auto videoItem = rootObject->findChild<QQuickItem *>("videoItem");

  g_object_set(qobject_cast<VideoPlayer*>(videoPlayer)->sink(), "widget", videoItem, nullptr);

  // gst_element_set_state (pipeline, GST_STATE_PLAYING);

   rootObject->scheduleRenderJob (new VideoSetPlaying (qobject_cast<VideoPlayer*>(videoPlayer)->pipeline()),
        QQuickWindow::BeforeSynchronizingStage);

  ret = app.exec();


  gst_deinit ();

  return ret;
}
