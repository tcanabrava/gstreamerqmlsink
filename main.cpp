#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QRunnable>
#include <gst/gst.h>

class SetPlaying : public QRunnable
{
public:
  SetPlaying(GstElement *);
  ~SetPlaying();

  void run ();

private:
  GstElement * pipeline_;
};

SetPlaying::SetPlaying (GstElement * pipeline)
{
  this->pipeline_ = pipeline ? static_cast<GstElement *> (gst_object_ref (pipeline)) : NULL;
}

SetPlaying::~SetPlaying ()
{
  if (this->pipeline_)
    gst_object_unref (this->pipeline_);
}

void
SetPlaying::run ()
{
  if (this->pipeline_) {
    qDebug() << "Starting to render";
    gst_element_set_state (this->pipeline_, GST_STATE_PLAYING);
    qDebug() << "Call to render finished";
  }
}

int main(int argc, char *argv[])
{
  int ret;

  gst_init (&argc, &argv);

  {
    QGuiApplication app(argc, argv);

    GstElement *sink = gst_element_factory_make ("qmlglsink", nullptr);
    gst_object_unref(sink);

    GstElement *pipeline = gst_pipeline_new (nullptr);
    GstElement *src = gst_element_factory_make ("videotestsrc", nullptr);
    GstElement *glupload = gst_element_factory_make ("glupload", nullptr);
    /* the plugin must be loaded before loading the qml file to register the
     * GstGLVideoItem qml item */
    sink = gst_element_factory_make ("qmlglsink", nullptr);

    g_assert (src && glupload && sink);

    gst_bin_add_many (GST_BIN (pipeline), src, glupload, sink, nullptr);
    gst_element_link_many (src, glupload, sink, nullptr);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickItem *videoItem;
    QQuickWindow *rootObject;

    /* find and set the videoItem on the sink */
    rootObject = static_cast<QQuickWindow *> (engine.rootObjects().first());
    videoItem = rootObject->findChild<QQuickItem *> ("videoItem");
    g_assert (videoItem);
    g_object_set(sink, "widget", videoItem, nullptr);

    rootObject->scheduleRenderJob (new SetPlaying (pipeline),
        QQuickWindow::BeforeSynchronizingStage);

    ret = app.exec();

    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
  }

  gst_deinit ();

  return ret;
}
