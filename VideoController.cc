#include "VideoController.h"
#include "VideoSetPlaying.h"

#include <QQuickWindow>

VideoController::VideoController(QQuickItem *parent)
: QQuickItem(parent)
, m_videoItem(nullptr)
, m_pipeline(nullptr)
, m_videoSink(nullptr)
{
    preparePipeline();
}

VideoController::~VideoController() {
    gst_element_set_state (m_pipeline, GST_STATE_NULL);
    gst_object_unref (m_pipeline);
}

void VideoController::preparePipeline() {
  m_pipeline = gst_pipeline_new (nullptr);

  GstElement *src = gst_element_factory_make ("videotestsrc", nullptr);
  GstElement *glupload = gst_element_factory_make ("glupload", nullptr);

  m_videoSink = gst_element_factory_make ("qmlglsink", nullptr);

  gst_bin_add_many (GST_BIN (m_pipeline), src, glupload, m_videoSink, nullptr);
  gst_element_link_many (src, glupload, m_videoSink, nullptr);
}

void VideoController::setVideoItem(QObject *videoItem) {
    if (m_videoItem != videoItem) {
        m_videoItem = videoItem;
        g_object_set(m_videoSink, "widget", videoItem, nullptr);
        Q_EMIT videoItemChanged(m_videoItem);
    }
}

void VideoController::startVideo() {
    window()->scheduleRenderJob (new VideoSetPlaying(m_pipeline), QQuickWindow::BeforeSynchronizingStage);
}

QObject *VideoController::videoItem() const {
    return m_videoItem;
}
