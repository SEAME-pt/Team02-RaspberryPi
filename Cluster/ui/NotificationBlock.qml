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
    property bool emergencyBrakeAlreadyShown: false
    property bool laneDepartureAlreadyShown: false

    function updateNotification() {

        showEmergencyBrakeIcon = false
        iconSource = ""
        messageText = ""

        console.log("Updating notification with warning code:", warningCode)
        switch (warningCode) {
            case 1:
                iconSource = "../assets/icons/warning.png"
                messageText = "Emergency braking activated!"
                showEmergencyBrakeIcon = true
                break;
            case 2:
                iconSource = "../assets/icons/warning.png"
                messageText = "Lane departure detected!"
                break;
        }

        if (iconSource !== "") {
            showNotification()
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
            if (instrumentCluster.warningCode === 1) {
                // Emergency braking
                if (!emergencyBrakeAlreadyShown) {
                    emergencyBrakeAlreadyShown = true

                    showEmergencyBrakeIcon = true
                    notificationBlock.warningCode = 1
                    notificationBlock.updateNotification()
                    notificationBlock.visible = true

                    emergencyBrakeNotificationTimer.restart()
                    emergencyBrakeIconHideDelay.stop()
                    objectPresenceMonitor.restart()
                } else {
                    showEmergencyBrakeIcon = true
                    emergencyBrakeIconHideDelay.stop()
                    objectPresenceMonitor.restart()
                }
            } else if (instrumentCluster.warningCode === 2) {
                // Lane departure
                if (!laneDepartureAlreadyShown) {
                    laneDepartureAlreadyShown = true

                    notificationBlock.warningCode = 2
                    notificationBlock.updateNotification()
                    notificationBlock.visible = true
                }
            } else {
                // Reset flags when warning code is cleared (optional)
                emergencyBrakeAlreadyShown = false
                laneDepartureAlreadyShown = false
            }
        }
    }   

    Connections {
        target: instrumentCluster

        onLaneDepartureChanged: {
            if (instrumentCluster.laneDeparture === 0) {
                laneDepartureAlreadyShown = false
            }
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
        }
    }

    Timer {
        id: hideTimer
        interval: 3000
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
