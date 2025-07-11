import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 40
    property int letterSizeLoaded: 45
    width: 1280
    height: 400
    // flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    flags: Qt.Window | Qt.WindowStaysOnTopHint

    // visibility: Window.FullScreen

    visibility: Window.Windowed
    property int iconWidth: 65
    property int iconHeight: 65

    property string fontPath1: Qt.resolvedUrl("file:/opt/vehicle/etc/fonts/electrolize.ttf")
    property bool fontExists: false

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
        color: "#252525"
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
        height: parent.height * 0.6
        source: "../assets/images/car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom 
        anchors.bottomMargin: -25
        // anchors.verticalCenter: parent.verticalCenter
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
                visible: instrumentCluster.laneDeparture == 10 || instrumentCluster.laneDeparture == 20
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
                visible: instrumentCluster.warningCode == 1
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
        width: 13
        height: parent.height * 0.70
        anchors.verticalCenter: carImage.verticalCenter
        rotation: 35
        transformOrigin: Item.TopLeft
        x: carImage.x + 130
        border.color: "black"

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: instrumentCluster.laneDeparture === 10 ? "#252525" : "#252525"
            }
            GradientStop {
                position: 1.0
                color: instrumentCluster.laneDeparture === 10 ? "#972727" : "#5c5c5c"
            }
        }

        Connections {
            target: instrumentCluster
            onLaneDepartureChanged: leftLaneDiagonal.update()
        }
    }

    Rectangle {
        id: rightLaneDiagonal
        width: 13
        height: parent.height * 0.70
        anchors.verticalCenter: carImage.verticalCenter
        rotation: -35
        transformOrigin: Item.TopRight
        x: carImage.x + carImage.width - 100
        border.color: "black"
        border.width: 1

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: instrumentCluster.laneDeparture === 20 ? "#252525" : "#252525"
            }
            GradientStop {
                position: 1.0
                color: instrumentCluster.laneDeparture === 20 ?  "#972727" : "#5c5c5c"
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