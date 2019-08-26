#pragma once

#include <QQuickItem>
#include <gst/gst.h>

class VideoController : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QObject *videoItem WRITE setVideoItem READ videoItem NOTIFY videoItemChanged)
public:
    VideoController(QQuickItem *parent = nullptr);
    virtual ~VideoController();

    /* This is the Qml GstGLVideoItem  */
    QObject *videoItem() const;
    Q_SLOT void setVideoItem(QObject *videoItem);
    Q_SIGNAL void videoItemChanged(QObject *videoItem);

    /* This method prepares the pipeline, creates the sink, links things together. */
    void preparePipeline();

    /* This method sets the pipeline state to playing as soon as Qt allows it */
    Q_INVOKABLE void startVideo();
    
    /* This *actually* enables the video set by startVideo() */
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

private:
    QObject *m_videoItem;
    GstElement *m_pipeline;
    GstElement *m_videoSink;
    bool m_shouldStartVideo;
};
