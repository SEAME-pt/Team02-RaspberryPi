import QtQuick 2.15
import QtQuick.Controls 2.4

Rectangle {
    id: notificationBlock
    width: 400
    height: 40
    radius: 10
    color: "gray"
    opacity: 0
    anchors.horizontalCenter: parent.horizontalCenter
    y: -height
    visible: false

    property int warningCode: instrumentCluster.warningCode
    property string iconSource: ""
    property string messageText: ""

    function updateNotification() {
        switch (warningCode) {
        case 1:
            iconSource = "../assets/icons/warning.png"
            messageText = "Emergency braking activated!";
            break;
        case 2:
            iconSource = "../assets/icons/warning.png"
            messageText = "Autopilot unavailable for current drive";
            break;
        case 3:
            iconSource = "../assets/icons/warning.png"
            messageText = "Lane departure detected!";
            break;
        default:
            iconSource = "";
            messageText = "";
        }

        if (iconSource !== "") {
            showNotification();
        }
    }

    function showNotification() {
        visible = true;
        appearAnimation.start();
        hideTimer.restart();
    }

    function hideNotification() {
        disappearAnimation.start();
    }

    Component.onCompleted: updateNotification()

    Connections {
        target: notificationBlock
        onWarningCodeChanged: updateNotification()
    }

    // Animations
    SequentialAnimation {
        id: appearAnimation
        PropertyAnimation { target: notificationBlock; property: "y"; to: 70; duration: 300; easing.type: Easing.OutQuad }
        PropertyAnimation { target: notificationBlock; property: "opacity"; to: 0.9; duration: 200 }
    }

    SequentialAnimation {
        id: disappearAnimation
        PropertyAnimation { target: notificationBlock; property: "opacity"; to: 0; duration: 200 }
        PropertyAnimation { target: notificationBlock; property: "y"; to: -height; duration: 300; easing.type: Easing.InQuad }
        onStopped: {
            visible = false;
        }
    }

    Timer {
        id: hideTimer
        interval: 4000 // milliseconds to stay on screen
        running: false
        repeat: false
        onTriggered: hideNotification()
    }

    Row {
        anchors.centerIn: parent
        spacing: 10
        visible: iconSource !== ""

        Image {
            source: iconSource
            width: 24
            height: 24
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: messageText
            color: "white"
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
        }
    }
}
