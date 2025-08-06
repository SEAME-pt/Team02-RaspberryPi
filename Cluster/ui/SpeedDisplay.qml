import QtQuick 2.15

Rectangle {
    anchors.verticalCenter: parent.verticalCenter
    width: 100
    height: 100
    color: "transparent"
    anchors.left: parent.left
    anchors.leftMargin: 150

    property string fontFamily: "default"
    property bool blinkerPhase: false

    Connections {
        target: instrumentCluster

        onLeftBlinkerChanged: {
            if (instrumentCluster.leftBlinker) {
                instrumentCluster.rightBlinker = false;
            }
        }

        onRightBlinkerChanged: {
            if (instrumentCluster.rightBlinker) {
                instrumentCluster.leftBlinker = false;
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Row {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: leftArrow
                source: "../assets/icons/turn_left_on.png"
                opacity: instrumentCluster.leftBlinker && blinkerPhase ? 1.0 : 0.0
                width: 60
                height: 60
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                text: instrumentCluster.speed
                font.pixelSize: 90
                font.family: fontFamily
                color: "white"
                opacity: 1.0
                verticalAlignment: Text.AlignVCenter
            }

            Image {
                id: rightArrow
                source: "../assets/icons/turn_right_on.png"
                opacity: instrumentCluster.rightBlinker && blinkerPhase ? 1.0 : 0.0
                width: 60
                height: 60
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Timer {
            id: blinkTimer
            interval: 500
            running: instrumentCluster.leftBlinker || instrumentCluster.rightBlinker
            repeat: true
            onTriggered: {
                blinkerPhase = !blinkerPhase;
            }
        }

        Text {
            font.family: fontFamily
            text: "M/MIN"
            font.pixelSize: app.letterSize
            color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
