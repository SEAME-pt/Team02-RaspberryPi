import QtQuick 2.15

Column {
    spacing: 3

    Text {
        font.family: "Open Sans"
        // text: instrumentCluster.speed
        text: "12"
        font.pixelSize: 110
        color: "white"
        opacity: 1.0
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Open Sans"
        text: "DM/S"
        font.pixelSize: app.letterSize
        color: "gray"
    }
}
