import QtQuick 2.15

Column {
    spacing: 5

    Text {
        font.family: "Open Sans"
        text: canBusHandler.speed
        font.pixelSize: 150
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
