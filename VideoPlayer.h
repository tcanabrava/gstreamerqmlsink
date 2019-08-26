#pragma once

#include <QQuickItem>

class VideoPlayer : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QObject *videoItem WRITE setVideoItem READ videoItem NOTIFY videoItemChanged)
public:
    VideoPlayer(QQuickItem *parent = nullptr);

    QObject *videoItem() const;
    Q_SLOT void setVideoItem(QObject *videoItem);
    Q_SIGNAL void videoItemChanged(QObject *videoItem);
private:
    QObject *m_videoItem;
};
