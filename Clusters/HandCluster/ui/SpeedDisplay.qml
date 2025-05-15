import QtQuick 2.15
Rectangle {
    anchors.verticalCenter: parent.verticalCenter
    width: 100
    height: 100
    color: "transparent"
    anchors.left: parent.left
    anchors.leftMargin: 100

    Column {
        anchors.centerIn: parent
        spacing: 0

        Text {
            // /text: instrumentCluster.speed
            text: "20"
            font.pixelSize: 90
            font.family: Qt.binding(function() { return app.font; })
            // font.family: app.font
            color: "white"
            opacity: 1.0
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            font.family: Qt.binding(function() { return app.font; })
            // font.family: app.font
            text: "DM/S"
            font.pixelSize: app.letterSize
            color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

