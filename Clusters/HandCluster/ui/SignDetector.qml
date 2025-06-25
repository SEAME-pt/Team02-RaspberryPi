import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    id: root
    width: parent.width
    height: parent.height
    z: 100

    property ListModel signModel: ListModel {}

    Timer {
        id: hideTimer
        interval: 3000
        running: false
        repeat: false
        onTriggered: {
            console.log("Timer triggered: clearing signs")
            signModel.clear()
        }
    }

    Connections {
        target: instrumentCluster

        function onSignDetectedChanged() {
            const value = instrumentCluster.signDetected
            console.log("QML received signal from C++:", value)

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

                    default: return "";
                }
            }

            const path = getImagePath(value);

            if (value === 0 || path === "") {
                signModel.clear();
            } else {
                let exists = false;
                for (let i = 0; i < signModel.count; i++) {
                    if (signModel.get(i).source === path) {
                        exists = true;
                        break;
                    }
                }

                if (!exists) {
                    for (let i = signModel.count - 1; i >= 0; i--) {
                        const item = signModel.get(i);
                        if (item.source.includes("traffic-light")) {
                            signModel.remove(i);
                        }
                    }

                    if (signModel.count >= 3) {
                        signModel.remove(0);
                    }
                    signModel.append({ source: path });
                    hideTimer.restart();
                }
            }

            console.log("signModel updated, count:", signModel.count);
        }
    }

    // Gray rectangle
    Rectangle {
        width: 200
        height: 200
        color: "transparent"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.rightMargin: 150
        z: 101

        Rectangle {
            width: parent.width - 10
            height: parent.height - 10
            color: "transparent"
            anchors.centerIn: parent

            Item {
                id: triangleContainer
                width: parent.width
                height: parent.height

                Repeater {
                    model: signModel
                    delegate: Image {
                        width: 65
                        height: 65
                        fillMode: Image.PreserveAspectFit
                        source: model.source + "?" + Date.now()

                        x: {
                            if (index === 0) return triangleContainer.width / 2 - width / 2
                            if (index === 1) return triangleContainer.width / 4 - width / 2
                            if (index === 2) return 3 * triangleContainer.width / 4 - width / 2
                            return 0
                        }

                        y: {
                            if (index === 0) return 0
                            if (index === 1 || index === 2) return 85 // vertical spacing
                            return 0
                        }

                        onStatusChanged: {
                            if (status === Image.Error) {
                                console.log("❌ Error loading image:", source)
                            } else if (status === Image.Ready) {
                                console.log("✅ Image loaded:", source)
                            }
                        }
                    }
                }
            }
        }
    }
}
