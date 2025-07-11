import QtQuick 2.15
import QtQuick.Controls 2.4
Rectangle {
    id: notificationBlock
    width: 350
    height: 40
    radius: 10
    anchors.top: parent.top
    anchors.topMargin: 20
    anchors.horizontalCenter: parent.horizontalCenter
    color: "gray"
    opacity: 0
    visible: false
    property string fontFamily: "default"

    property int warningCode: 0

    property string iconSource: ""
    property string messageText: ""

    function updateNotification() {
        switch (warningCode) {
            case 1:
                iconSource = "../assets/icons/warning.png"
                messageText = "Emergency braking activated!";
                break;
            case 10:
                iconSource = "../assets/icons/warning.png"
                messageText = "Lane departure detected!";
                break;
            case 11:
                iconSource = "../assets/icons/warning.png"
                messageText = "Lane departure detected!";
                break;
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
        target: instrumentCluster

        onWarningCodeChanged: {
            notificationBlock.warningCode = instrumentCluster.warningCode;
            notificationBlock.updateNotification();
        }
    }

    // Animations
    SequentialAnimation {
        id: appearAnimation
        PropertyAnimation { target: notificationBlock; property: "y"; to: 60; duration: 300; easing.type: Easing.OutQuad } // Adjusted to move up slightly
        PropertyAnimation { target: notificationBlock; property: "opacity"; to: 0.9; duration: 200 }
    }

    SequentialAnimation {
        id: disappearAnimation
        PropertyAnimation { target: notificationBlock; property: "opacity"; to: 0; duration: 200 }
        PropertyAnimation { target: notificationBlock; property: "y"; to: -height + 10; duration: 300; easing.type: Easing.InQuad } // Adjusted to move up slightly
        onStopped: {
            visible = false;
            // instrumentCluster.warningCode = 0;
        }
    }

    Timer {
        id: hideTimer
        interval: 4000
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
            font.family: fontFamily
            verticalAlignment: Text.AlignVCenter
        }
    }
}
