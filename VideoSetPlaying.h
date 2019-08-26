#pragma once

#include <QRunnable>
#include <gst/gst.h>

class VideoSetPlaying : public QRunnable
{
public:
  VideoSetPlaying(GstElement *);
  ~VideoSetPlaying();

  void run ();

private:
  GstElement * m_pipeline;
};
