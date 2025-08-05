import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: parent.width
    height: parent.height
    z: 100

    property int iconWidth: 65
    property int iconHeight: 65

    property ListModel speedSigns: ListModel {}
    property ListModel trafficLights: ListModel {}

    property string stopSignSource: ""
    property string yieldSignSource: ""
    property string pedestrianSignSource: ""
    property string dangerSignSource: ""

    property color gradientColor: "transparent"

    Timer {
        id: hideTimer
        interval: 2000
        running: false
        repeat: false
        onTriggered: {
            stopSignSource = ""
            yieldSignSource = ""
            pedestrianSignSource = ""
            dangerSignSource = ""
            trafficLights.clear()
            trafficLightGradient.opacity = 0.0
        }
    }

    Connections {
        target: instrumentCluster

        function onSignDetectedChanged() {
            const value = instrumentCluster.signDetected
            console.log("Signal received:", value)

            function getImagePath(val) {
                switch(val) {
                    case 3: return "../assets/icons/50.png";
                    case 4: return "../assets/icons/60.png";
                    case 5: return "../assets/icons/70.png";
                    case 6: return "../assets/icons/80.png";
                    case 7: return "../assets/icons/90.png";
                    case 8: return "../assets/icons/100.png";
                    case 9: return "../assets/icons/120.png";
                    case 11: return "../assets/icons/stop.png";
                    case 12: return "../assets/icons/yield.png"; 
                    case 13: return "../assets/icons/pedestrian.png";
                    case 14: return "../assets/icons/traffic-light-yellow.png";
                    case 15: return "../assets/icons/traffic-light-green.png";
                    case 16: return "../assets/icons/traffic-light-red.png";
                    case 17: return "../assets/icons/danger.png";
                    default: return "";
                }
            }

            const path = getImagePath(value)
            const cacheBuster = "?" + Date.now()

            function alreadyExists(model, p) {
                for (let i = 0; i < model.count; i++) {
                    if (model.get(i).source === p) return true;
                }
                return false;
            }

            if (value === 0 || path === "") {
                speedSigns.clear()
                trafficLights.clear()
                stopSignSource = ""
                yieldSignSource = ""
                pedestrianSignSource = ""
                dangerSignSource = ""
                trafficLightGradient.opacity = 0.0
                return
            }

            if (path.includes("traffic-light")) {
                if (!alreadyExists(trafficLights, path)) {
                    trafficLights.clear()
                    trafficLights.append({ source: path + cacheBuster })
                }
                hideTimer.restart()
            } else if ([3,4,5,6,7,8,9].includes(value)) {
                if (!alreadyExists(speedSigns, path)) {
                    speedSigns.clear()
                    speedSigns.append({ source: path + cacheBuster })
                }
            } else if ([11,12,13,17].includes(value)) {
                if (value === 11) {
                    stopSignSource = ""
                    stopSignSource = path + cacheBuster
                } else if (value === 12) {
                    yieldSignSource = ""
                    yieldSignSource = path + cacheBuster
                } else if (value === 13) {
                    pedestrianSignSource = ""
                    pedestrianSignSource = path + cacheBuster
                } else if (value === 17) {
                    dangerSignSource = ""
                    dangerSignSource = path + cacheBuster
                }
                hideTimer.restart()
            }
        }
    }

    Item {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -100
        z: 102

        Row {
            id: speedSignRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Repeater {
                model: speedSigns
                delegate: Image {
                    width: iconWidth
                    height: iconHeight
                    source: model.source
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    // TRAFFIC LIGHT SIGNS
    Item {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 600
        anchors.verticalCenterOffset: -115
        z: 102

        Repeater {
            model: trafficLights
            delegate: Image {
                width: iconWidth * 3.5
                height: iconHeight * 3.5
                source: model.source
                fillMode: Image.PreserveAspectFit
                opacity: 1.0

                Behavior on opacity {
                    NumberAnimation {
                        duration: 500
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }

    // GRADIENT EFFECT FOR TRAFFIC LIGHTS
    Rectangle {
        id: trafficLightGradient
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height 
        opacity: 0.0

        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0.0; color: gradientColor }
            GradientStop { position: 1.0; color: "#00000000" }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }
    }

    Connections {
        target: trafficLights
        function onCountChanged() {
            if (trafficLights.count > 0) {
                const src = trafficLights.get(0).source
                if (src.includes("yellow")) {
                    gradientColor = "#9cd3b300"
                    trafficLightGradient.opacity = 0.8
                } else if (src.includes("green")) {
                    gradientColor = "#79018801"
                    trafficLightGradient.opacity = 0.8
                } else if (src.includes("red")) {
                    gradientColor = "#59ca0606"
                    trafficLightGradient.opacity = 0.8
                } else {
                    trafficLightGradient.opacity = 0.0
                }
            } else {
                trafficLightGradient.opacity = 0.0
            }
        }
    }

    // FIXED SIGNS (STOP, YIELD, PEDESTRIAN, DANGER)
    Item {
        width: 160
        height: 160
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 150 
        anchors.rightMargin: 170
        z: 102

        Image {
            visible: stopSignSource !== ""
            width: iconWidth
            height: iconHeight
            source: stopSignSource
            fillMode: Image.PreserveAspectFit
            x: 5
            y: 5
        }

        Image {
            visible: dangerSignSource !== ""
            width: iconWidth
            height: iconHeight
            source: dangerSignSource
            fillMode: Image.PreserveAspectFit
            x: parent.width - width - 5
            y: 5
        }

        Image {
            visible: yieldSignSource !== ""
            width: iconWidth
            height: iconHeight
            source: yieldSignSource
            fillMode: Image.PreserveAspectFit
            x: 5
            y: parent.height - height - 5
        }

        Image {
            visible: pedestrianSignSource !== ""
            width: iconWidth
            height: iconHeight
            source: pedestrianSignSource
            fillMode: Image.PreserveAspectFit
            x: parent.width - width - 5
            y: parent.height - height - 5
        }
    }
}
