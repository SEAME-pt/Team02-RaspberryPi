import QtQuick 2.15

Rectangle {
    anchors.verticalCenter: parent.verticalCenter
    width: 100
    height: 100
    color: "transparent"
    anchors.left: parent.left
    anchors.leftMargin: 150
    property string fontFamily: "default"
    property bool leftBlinkerVisible: false
    property bool rightBlinkerVisible: false

    Connections {
        target: instrumentCluster

        onLeftBlinkerChanged: {
            if (instrumentCluster.leftBlinker) {
                instrumentCluster.rightBlinker = false;
            } else {
                leftBlinkerVisible = false;
            }
        }

        onRightBlinkerChanged: {
            if (instrumentCluster.rightBlinker) {
                instrumentCluster.leftBlinker = false;
            } else {
                rightBlinkerVisible = false;
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
                opacity: leftBlinkerVisible ? 1.0 : 0.0
                width: 50
                height: 50
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
                opacity: rightBlinkerVisible ? 1.0 : 0.0
                width: 50
                height: 50
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Timer {
            id: blinkTimer
            interval: 500
            running: instrumentCluster.leftBlinker || instrumentCluster.rightBlinker
            repeat: true
            onTriggered: {
                if (instrumentCluster.leftBlinker && !instrumentCluster.rightBlinker) {
                    leftBlinkerVisible = !leftBlinkerVisible;
                    rightBlinkerVisible = false;
                } else if (instrumentCluster.rightBlinker && !instrumentCluster.leftBlinker) {
                    rightBlinkerVisible = !rightBlinkerVisible;
                    leftBlinkerVisible = false;
                } else {
                    leftBlinkerVisible = false;
                    rightBlinkerVisible = false;
                }
            }
        }

        Text {
            font.family: fontFamily
            text: "KM/H"
            font.pixelSize: app.letterSize
            color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
