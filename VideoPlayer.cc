#include "VideoPlayer.h"

VideoPlayer::VideoPlayer(QQuickItem *parent) 
: QQuickItem(parent)
, m_videoItem(nullptr)
, m_pipeline(nullptr)
, m_videoSink(nullptr)
{
    preparePipeline();
}

VideoPlayer::~VideoPlayer() {
    gst_element_set_state (m_pipeline, GST_STATE_NULL);
    gst_object_unref (m_pipeline);
}

void VideoPlayer::preparePipeline() {
  m_pipeline = gst_pipeline_new (nullptr);

  GstElement *src = gst_element_factory_make ("videotestsrc", nullptr);
  GstElement *glupload = gst_element_factory_make ("glupload", nullptr);

  m_videoSink = gst_element_factory_make ("qmlglsink", nullptr);

  g_assert (src && glupload && m_videoSink);

  gst_bin_add_many (GST_BIN (m_pipeline), src, glupload, m_videoSink, nullptr);
  gst_element_link_many (src, glupload, m_videoSink, nullptr);
}

void VideoPlayer::setVideoItem(QObject *videoItem) {
    if (m_videoItem != videoItem) {
        m_videoItem = videoItem;
        g_object_set(m_videoSink, "widget", videoItem, nullptr);
        Q_EMIT videoItemChanged(m_videoItem);
    }
}

GstElement* VideoPlayer::pipeline() const {
    return m_pipeline;
}

GstElement* VideoPlayer::sink() const {
    return m_videoSink;
}

QObject *VideoPlayer::videoItem() const {
    return m_videoItem;
}
