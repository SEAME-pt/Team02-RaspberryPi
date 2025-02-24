import QtQuick
import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    visible: true
    width: 1024
    height: 600
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    visibility: Window.FullScreen  // Add this line

    property int letterSize: 27
    property int letterSizeGear: 25
    property int letterSizeLoaded: 30
    property int gearOffset: -2
    property int iconWidth: 45
    property int iconHeight: 45
    property bool carClusterVisible: true
    property bool showSplash: true

    font.family: "Roboto"
    font.pixelSize: 30
    font.bold: false


    Rectangle {
        anchors.fill: parent  // Faz o retângulo preencher todo o ApplicationWindow
        color: "lightgray"  // Cor de fundo

        Image {
            source: "qrc:/assets/images/car-detection.png"  // Caminho do arquivo .jpeg
            anchors.centerIn: parent  // Centraliza a imagem dentro do retângulo
            //fillMode: Image.PreserveAspectFit  // Garante que a imagem seja redimensionada proporcionalmente
            anchors.fill: parent  // Faz a imagem ocupar todo o espaço disponível no retângulo
        }
    }

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 50
        spacing: 10

        //TurnSignalLeft {}
        Column {
            spacing: 0

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
                font.pixelSize: app.letterSize - 4
                color: "gray"
                anchors.bottomMargin: 5
            }

        }
        //TurnSignalRight {}
    }


    Row {
        anchors.top: parent.top
        width: parent.width
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
        height: 50
        spacing: 30
        padding: 10

        Column {

            Row {
                spacing: 5

                Text {
                    font.family: "Open Sans"
                    text: "22°"
                    font.pixelSize: app.letterSize
                    color: "white"
                }
                Text {
                    font.family: "Open Sans"
                    text: "C"
                    font.pixelSize: app.letterSize
                    color: "gray"
                }
            }
        }

        Column {
            Row {
                spacing: 5
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
        }

    }

    Column {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 15
        spacing: 7

        Rectangle {
                width: app.iconWidth
                height: app.iconHeight
                color: "transparent" // Keeps the placeholder invisible
                Image {
                    id: lowBeamSignal
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height
                    source: "qrc:/assets/icons/low_beam_on.png"
                    visible: instrumentCluster.lights.lowBeam
                }
            }

            Rectangle {
                width: app.iconWidth
                height: app.iconHeight
                color: "transparent"
                Image {
                    id: highBeamSignal
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height
                    source: "qrc:/assets/icons/high_beam_on.png"
                    visible: instrumentCluster.lights.highBeam
                }
            }

            Rectangle {
                width: app.iconWidth
                height: app.iconHeight
                color: "transparent"
                Image {
                    id: frontFogSignal
                    anchors.centerIn: parent
                     width: parent.width
                    height: parent.height
                    source: "qrc:/assets/icons/front_fog_on.png"
                    visible: instrumentCluster.lights.frontFogLight
                }
            }

            Rectangle {
                width: app.iconWidth
                height: app.iconHeight
                color: "transparent"
                Image {
                    id: parkingLightsSignal
                    anchors.centerIn: parent
                     width: parent.width
                    height: parent.height
                    source: "qrc:/assets/icons/parking_lights_on.png"
                    visible: instrumentCluster.lights.parkingLight
                }
            }

            Rectangle {
                width: app.iconWidth
                height: app.iconHeight
                color: "transparent"
                Image {
                    id: backFogSignal
                    anchors.centerIn: parent
                     width: parent.width
                    height: parent.height
                    source: "qrc:/assets/icons/back_fog_on.png"
                    visible: instrumentCluster.lights.rearFogLight
                }
            }
    }

    Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            spacing: 16
            Text {
                font.family: "Open Sans"
                text: "P"
                font.pixelSize: instrumentCluster.gear.park ? app.letterSizeLoaded : app.letterSizeGear
                color: instrumentCluster.gear.park ? "blue" : "white"
                y: instrumentCluster.gear.park ? gearOffset : 0
            }
            Text {
                font.family: "Open Sans"
                text: "R"
                font.pixelSize: instrumentCluster.gear.reverse ? app.letterSizeLoaded : app.letterSizeGear
                color: instrumentCluster.gear.reverse ? "blue" : "white"
                y: instrumentCluster.gear.reverse ? gearOffset : 0
            }
            Text {
                font.family: "Open Sans"
                text: "N"
                font.pixelSize: instrumentCluster.gear.neutral ? app.letterSizeLoaded : app.letterSizeGear
                color: instrumentCluster.gear.neutral ? "blue" : "white"
                y: instrumentCluster.gear.neutral ? gearOffset : 0
            }
            Text {
                font.family: "Open Sans"
                text: "D"
                font.pixelSize: instrumentCluster.gear.drive ? app.letterSizeLoaded : app.letterSizeGear
                color: instrumentCluster.gear.drive ? "blue" : "white"
                y: instrumentCluster.gear.drive ? gearOffset : 0
            }
        }

    Row {
            
        anchors.right: parent.right
        anchors.rightMargin: 140
        anchors.verticalCenterOffset: -110
        anchors.verticalCenter: parent.verticalCenter
        spacing: 15
        CircularProgressBar {
            id: batteryPercentage
            lineWidth: 10
            value: instrumentCluster.battery.percentage / 100
            size: 115
            secondaryColor: "#ffffff"
            primaryColor: instrumentCluster.battery.percentage < 20 ? "#ff0000" : "#2fc71b"

            Text {
                text: parseInt(batteryPercentage.value * 100) + "%"
                anchors.centerIn: parent
                font.pixelSize: 22
                color: "#ffffff"
            }
        }
    }
}

