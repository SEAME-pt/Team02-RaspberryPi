import QtQuick 2.15

Row {
    anchors.rightMargin: 30
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 5
    anchors.top: parent.top
    anchors.topMargin: 25
    property string fontFamily: "default"

    Rectangle {
        width: 7
        height: 1
        color: "transparent"
    }

    Text {
        font.family: fontFamily
        id: timeDisplay
        text: "11:11"
        font.pixelSize:  app.letterSize
        color: "white"
        opacity: 0.0
    }

    Text {
        font.family: fontFamily
        id: amPmDisplay
        text: "AM"
        font.pixelSize: app.letterSize
        color: "gray"
        opacity: 0.0
    }

    Timer {
        id: clockTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            timeDisplay.text = timeHelper.getCurrentTime();
            timeDisplay.opacity = 1.0

            amPmDisplay.text = timeHelper.getCurrentAmPm();
            amPmDisplay.opacity = 1.0
        }
    }

    QtObject {
        id: timeHelper

        function getCurrentTime() {
            const currentDate = new Date();
            let hours = currentDate.getHours();
            let minutes = currentDate.getMinutes();

            hours = hours % 12 || 12;
            minutes = minutes < 10 ? "0" + minutes : minutes

            return hours + ":" + minutes;
        }

        function getCurrentAmPm() {
            const currentDate = new Date();
            return currentDate.getHours() >= 12 ? "PM" : "AM";
        }
    }
}