import QtQuick 2.15

Row {
    spacing: 5
    Image {
        id: clockIcon
        source: "qrc:/assets/icons/watch.png"
        width: app.iconWidth - 5 
        height: app.iconHeight - 5
        visible: true
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        width: 7 // Adjust the width to set the desired space
        height: 1
        color: "transparent"
    }

    Text {
        font.family: "Open Sans"
        id: timeDisplay
        text: "11:11"
        font.pixelSize:  app.letterSize
        color: "white"
        opacity: 0.0
    }

    Text {
        font.family: "Open Sans"
        id: amPmDisplay
        text: "AM"
        font.pixelSize: app.letterSize
        color: "gray"
        opacity: 0.0
    }

    Timer {
        id: clockTimer
        interval: 1000 // Atualiza a cada 1 segundo
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