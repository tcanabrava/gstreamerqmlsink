#include "VideoSetPlaying.h"

#include <QDebug>

VideoSetPlaying::VideoSetPlaying (GstElement * element) : 
    m_pipeline(element ? static_cast<GstElement *> (gst_object_ref (element)) : nullptr)
{
}

VideoSetPlaying::~VideoSetPlaying ()
{
  if (m_pipeline)
    gst_object_unref (m_pipeline);
}

void VideoSetPlaying::run ()
{
  if (m_pipeline) {
    qDebug() << "Starting to render";
    gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
    qDebug() << "Call to render finished";
  }
}