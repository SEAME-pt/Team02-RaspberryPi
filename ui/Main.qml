import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: app
    visible: true
    width: Screen.width
    height: Screen.height
    // flags: Qt.FramelessWindowHint

    property int letterSize: 25
    property int iconWidth: 40
    property int iconHeight: 40
    property bool carClusterVisible: true

    property bool showSplash: true

    font.family: "Roboto"
    font.pixelSize: 30 
    font.bold: false

    // Car CLuster
    Rectangle {
        anchors.fill: parent
        visible: app.carClusterVisible

        // Background Gradient
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.fillStyle = "#000000";
                ctx.fillRect(0, 0, width, height);
            }
        }

        Row {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 100
            spacing: 10

            TurnSignals { 
                isLeft: true
                isBlinking: true 
            }
            SpeedDisplay {}
            TurnSignals { 
                isLeft: false
                isBlinking: false 
            }
        }

        GearShiftInfo {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
        }

        LightInfo {
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 70
        }

        FootbarInfo {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 60
            anchors.left: parent.left
            anchors.leftMargin: 70
        }
    }
}