#pragma once

#include <QRunnable>
#include <gst/gst.h>

/* This is used to set the pipeline state to playing, perhaps I can use a lambda */
class VideoSetPlaying : public QRunnable
{
public:
  VideoSetPlaying(GstElement *);
  ~VideoSetPlaying();

  void run ();

private:
  GstElement * m_pipeline;
};
