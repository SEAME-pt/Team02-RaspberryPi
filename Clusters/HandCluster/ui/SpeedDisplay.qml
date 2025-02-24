import QtQuick 2.15


Column {
    spacing: 3

     Rectangle {
        width: 100
        height: 100 
        color: "transparent" 

        Text {
            anchors.centerIn: parent
            font.family: "Open Sans"
            text: instrumentCluster.speed
            font.pixelSize: 110
            color: "white"
            opacity: 1.0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Open Sans"
        text: "DM/S"
        font.pixelSize: app.letterSize
        color: "gray"
    }
}
