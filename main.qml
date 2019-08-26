import QtQuick 2.4
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.1

import org.freedesktop.gstreamer.GLVideoItem 1.0
import org.bluerobotics.com 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    x: 30
    y: 30
    color: "black"

    VideoController {
        id: videoController
        videoItem: video
        Component.onCompleted : {
            videoController.startVideo();
        }
    }

    GstGLVideoItem {
        id: video
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        anchors.fill: parent
    }
}
