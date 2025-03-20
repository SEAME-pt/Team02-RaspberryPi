import QtQuick 2.15

Rectangle {
    anchors.verticalCenter: parent.verticalCenter
    
    width: 100
    height: 100
    color: "transparent"

    Column {
        anchors.centerIn: parent
        spacing: 5  // Espaçamento entre os textos

        Text {
            font.family: "Open Sans"
            text: instrumentCluster.speed
            font.pixelSize: 110
            color: "white"
            opacity: 1.0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            font.family: "Open Sans"
            text: "DM/S"
            font.pixelSize: app.letterSize
            color: "gray"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}

