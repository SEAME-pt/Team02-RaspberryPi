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

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10

            Image {
                anchors.verticalCenter: parent.verticalCenter
                id: turnLeftSignal
                source: "qrc:/assets/icons/turn_left_on.png"
                width: 70
                height: 70
                opacity: 0.0

                property bool isBlinkingLeft: false // space to add the variable

                Timer {
                    id: blinkTimerLeft
                    interval: 500 // (500ms = 0,5s)
                    running: true
                    repeat: true
                    onTriggered: {
                        if (turnLeftSignal.isBlinkingLeft) {
                            turnLeftSignal.opacity = turnLeftSignal.opacity === 1.0 ? 0.0 : 1.0;
                        } else {
                            turnLeftSignal.opacity = 0.0;
                        }
                    }
                }
            }

            // Speed
            Column {

                anchors.verticalCenter: parent.verticalCenter
                spacing: 5


                Text {
                    font.family: "Open Sans"
                    text: canBusHandler.speed
                    font.pixelSize: 150
                    color: "white"
                    opacity: 1.0

                    // anchors.verticalCenter: parent.verticalCenter
                    // anchors.right: parent.right
                    // anchors.rightMargin: 300
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    //text: canBusHandler.speedType
                    font.family: "Open Sans"
                    text: "DM/S"
                    font.pixelSize:  app.letterSize
                    color: "gray"
                }
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                id: turnRightSignal
                source: "qrc:/assets/icons/turn_right_on.png"
                width: 70
                height: 70
                opacity: 0.0

                property bool isBlinkingRight: true // space to add the variable

                Timer {
                    id: blinkTimerRight
                    interval: 500 // (500ms = 0,5s)
                    running: true
                    repeat: true
                    onTriggered: {
                        if (turnRightSignal.isBlinkingRight) {
                            turnRightSignal.opacity = turnRightSignal.opacity === 1.0 ? 0.0 : 1.0;
                        } else {
                            turnRightSignal.opacity = 0.0;
                        }
                    }
                }
            }

        }


        // Footbar infos
        Row {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            width: parent.width
            height: 50
            spacing: 10
            padding: 10

            Row {
                anchors.right: parent.right
                anchors.rightMargin: 200
                spacing: 25

                Row {
                    spacing: 3

                    // Hora
                    Text {
                        font.family: "Open Sans"
                        text: "P"
                        font.pixelSize:  app.letterSize
                        color: "gray"
                    }
                    Text {
                        font.family: "Open Sans"
                        text: "R"
                        font.pixelSize:  app.letterSize
                        color: "gray"
                    }
                    Text {
                        font.family: "Open Sans"
                        text: "N"
                        font.pixelSize:  app.letterSize
                        color: "gray"
                    }
                    Text {
                        font.family: "Open Sans"
                        text: "D"
                        font.pixelSize:  app.letterSize
                        color: "blue"
                    }
                }
            }

            Row {
                spacing: 5

                // Hora
                Text {
                    font.family: "Open Sans"
                    id: timeDisplay
                    text: "11:11"
                    font.pixelSize:  app.letterSize
                    color: "white"
                    opacity: 0.0
                }

                // AM/PM
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

                // Funções encapsuladas em um QtObject
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

            Row {
                anchors.left: parent.left
                anchors.leftMargin: 200
                spacing: 25

                Row {
                    spacing: 3

                    // Hora
                    Text {
                        font.family: "Open Sans"
                        text: "256"
                        font.pixelSize:  app.letterSize
                        color: "white"
                    }
                    Text {
                        font.family: "Open Sans"
                        text: "mi"
                        font.pixelSize: app.letterSize
                        color: "gray"
                    }

                }

                Row {
                    spacing: 5

                    // Hora
                    Text {
                        font.family: "Open Sans"
                        text: "22°"
                        font.pixelSize:  app.letterSize
                        color: "white"
                    }

                    // AM/PM
                    Text {
                        font.family: "Open Sans"
                        text: "G"
                        font.pixelSize:  app.letterSize
                        color: "gray"
                    }
                }
            }
        }

        Row {
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter // Centraliza horizontalmente
            height: 50
            spacing: 10 // Espaçamento entre os elementos
            padding: 10


            Image {
                id: lowBeamSignal
                source: "qrc:/assets/icons/low_beam_on.png" // Use 'qrc:/' as a prefix
                width: app.iconWidth
                height: app.iconHeight
                visible: true
            }

            Image {
                    id: highBeamSignal
                    source: "qrc:/assets/icons/high_beam_on.png"
                    width: app.iconWidth
                    height: app.iconHeight
                    visible: true


            }

            Image {
                id: frontFogSignal
                source: "qrc:/assets/icons/front_fog_on.png" // Use 'qrc:/' as a prefix
                width: app.iconWidth
                height: app.iconHeight
                visible: true
            }

            Image {
                id: parkingLightsSignal
                source: "qrc:/assets/icons/parking_lights_on.png" // Use 'qrc:/' as a prefix
                width: app.iconWidth
                height: app.iconHeight
                visible: true
            }

            Image {
                id: backFogSignal
                source: "qrc:/assets/icons/back_fog_on.png" // Use 'qrc:/' as a prefix
                width: app.iconWidth
                height: app.iconHeight
                visible: true
            }
        }
    }
}