import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 40
    property int letterSizeLoaded: 45
    width: 1280
    height: 400
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    // flags: Qt.Window | Qt.WindowStaysOnTopHint

    visibility: Window.FullScreen
    property int iconWidth: 65
    property int iconHeight: 65

    property string fontPath1: Qt.resolvedUrl("file:/opt/vehicle/etc/fonts/electrolize.ttf")
    // property string fontPath1: Qt.resolvedUrl("file:electrolize.ttf")

    property bool fontExists: false
    property bool objectStillPresent: false
    property bool showEmergencyBrakeIcon: instrumentCluster.warningCode === 1

    FontLoader {
        id: customFont
        source: fontPath1
    }

    Component.onCompleted: {
        console.log("Font Status:", customFont.status)
        if (customFont.status === FontLoader.Ready) {
            console.log("Fonte carregada com sucesso:", customFont.name)
            app.font = customFont.name
            forceLayoutUpdate();
        } else {
            console.log("Erro ao carregar a fonte:", customFont.status)
        }
    }

    function forceLayoutUpdate() {
        app.width = app.width + 1;
        app.width = app.width - 1;
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#2c2c2c"  // cinza médio
    }

    LaneLines {
        id: laneLines 
        width: parent.width * 2/4
        height: parent.height * 0.7
        // anchors.right: parent.right
        anchors.bottom: parent.bottom
        // leftLanePoints: leftLaneMock
        // rightLanePoints: rightLaneMock
    }

    ObjectDetector {
        id: objectDetector
        width: parent.width * 2/4
        height: parent.height * 0.9
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 50
    }

    Image {
        id: carImage
        width: parent.width * 1/4
        height: parent.height * 0.7
        source: "../assets/images/car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        // anchors.bottom: parent.bottom 
        fillMode: Image.PreserveAspectFit
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 110  // Aumente para mais abaixo
    }

    SpeedDisplay {
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    GearDisplay {
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    BatteryIndicator {
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    TimeInfo {
        id: timeInfo
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }
    
    NotificationBlock {
        id: notificationBlock
        warningCode: instrumentCluster.warningCode
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    LightInfo {}

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.leftMargin: 65
        spacing: 13

        Rectangle {
        width: app.iconWidth - 7
        height: app.iconHeight - 7
        color: "transparent"
        

            Image {
                id: assistSteerSignal
                anchors.centerIn: parent
                width: parent.width
                height: parent.height
                fillMode: Image.PreserveAspectFit

                source: {
                    if (instrumentCluster.autonomyLevel === 2)
                        return "../assets/icons/assist-steer-on.png"
                    else if (instrumentCluster.autonomyLevel === 5)
                        return "../assets/icons/assist-navigate-driving-on.png"
                    else
                        return ""
                }
                visible: source !== ""
            }
        }

        Rectangle {
            width: app.iconWidth - 15  
            height: app.iconHeight - 15
            color: "transparent"
            y: 5

            Image {
                id: emergencyBrakingSignal
                anchors.centerIn: parent
                width: parent.width
                height: parent.height
                source: "../assets/icons/brake.png"
                visible: showEmergencyBrakeIcon
            }
        }

        Rectangle {
            width: app.iconWidth - 15  
            height: app.iconHeight - 15
            color: "transparent"
            y: 5

            Image {
                id: laneDepartureSignal
                anchors.centerIn: parent
                width: parent.width
                height: parent.height
                source: "../assets/icons/lane-departure.png"
                visible: instrumentCluster.laneDeparture === 10 || instrumentCluster.laneDeparture === 20
            }

        }

        Timer {
            id: emergencyBrakeNotificationTimer
            interval: 3000
            running: false
            repeat: false
            onTriggered: {
                notificationBlock.visible = false
            }
        }

        Timer {
            id: objectPresenceMonitor
            interval: 1000
            repeat: false
            running: false
            onTriggered: {
                emergencyBrakeIconHideDelay.start()
            }
        }


        Timer {
            id: emergencyBrakeIconHideDelay
            interval: 2000
            running: false
            repeat: false
            onTriggered: {
                showEmergencyBrakeIcon = false
                instrumentCluster.warningCode = 0
            }
        }

        Rectangle {
            width: app.iconWidth - 17  
            height: app.iconHeight - 17
            color: "transparent"
            y: 5

            Image {
                id: cruiseControlSignal
                anchors.centerIn: parent
                width: parent.width
                height: parent.height
                source: "../assets/icons/cruise-control.png"
                visible: instrumentCluster.cruiseControl === true
            }
        }
    }
   

    SignDetector {
        id: signDetector
        width: parent.width
        height: parent.height
        iconWidth: app.iconWidth
        iconHeight: app.iconHeight
    }

    Rectangle {
        id: leftLaneDiagonal
        width: 7
        height: parent.height * 0.70
        anchors.verticalCenter: carImage.verticalCenter
        anchors.horizontalCenter: carImage.horizontalCenter
        anchors.horizontalCenterOffset: -40
        rotation: 35
        transformOrigin: Item.Top

        border.width: 0

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: instrumentCluster.laneDeparture === 10 ? "#252525" : "#252525"
            }
            GradientStop {
                position: 1.0
                color: instrumentCluster.laneDeparture === 10 ? "#972727" : "#a5a4a4"
                
            }
        }

        Connections {
            target: instrumentCluster
            onLaneDepartureChanged: leftLaneDiagonal.update()
        }
    }

    Rectangle {
        id: rightLaneDiagonal
        width: 7
        height: parent.height * 0.70
        anchors.verticalCenter: carImage.verticalCenter
        anchors.horizontalCenter: carImage.horizontalCenter
        anchors.horizontalCenterOffset: 40
        rotation: -35
        transformOrigin: Item.Top
        border.width: 0

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: instrumentCluster.laneDeparture === 20 ? "#252525" : "#252525"
            }
            GradientStop {
                position: 1.0
                color: instrumentCluster.laneDeparture === 20 ?  "#972727" : "#a5a4a4"
            }
        }

        Connections {
            target: instrumentCluster
            onLaneDepartureChanged: rightLaneDiagonal.update()
        }
    }


    Rectangle {
        id: roadBackground
        width: parent.width
        height: parent.height
        color: "#808080"
        z: -1
    }

}