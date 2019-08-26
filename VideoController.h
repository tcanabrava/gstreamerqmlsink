#pragma once

#include <QQuickItem>
#include <gst/gst.h>

class VideoPlayer : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QObject *videoItem WRITE setVideoItem READ videoItem NOTIFY videoItemChanged)
public:
    VideoPlayer(QQuickItem *parent = nullptr);
    virtual ~VideoPlayer();

    QObject *videoItem() const;
    Q_SLOT void setVideoItem(QObject *videoItem);
    Q_SIGNAL void videoItemChanged(QObject *videoItem);

    void preparePipeline();
    GstElement *pipeline() const;
    GstElement *sink() const;
    Q_INVOKABLE void startVideo();
    
private:
    QObject *m_videoItem;
    GstElement *m_pipeline;
    GstElement *m_videoSink;
};
