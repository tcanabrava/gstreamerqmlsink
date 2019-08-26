#include "VideoPlayer.h"

VideoPlayer::VideoPlayer(QQuickItem *parent) 
: QQuickItem(parent)
, m_videoItem(nullptr)
{
}

void VideoPlayer::setVideoItem(QObject *videoItem) {
    if (m_videoItem != videoItem) {
        m_videoItem = videoItem;
        Q_EMIT videoItemChanged(m_videoItem);
        qDebug() << "Video Set!";
    }
}

QObject *VideoPlayer::videoItem() const {
    return m_videoItem;
}
