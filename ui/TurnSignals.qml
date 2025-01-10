import QtQuick 2.15

Row {
    id: root
    spacing: 10

    property bool isLeft: true
    property bool isBlinking: false

    Image {
        anchors.verticalCenter: parent.verticalCenter
        id: turnSignal
        source: isLeft ? "qrc:/assets/icons/turn_left_on.png" : "qrc:/assets/icons/turn_right_on.png"
        width: 70
        height: 70
        opacity: 0.0

        Timer {
            id: blinkTimer
            interval: 500
            running: root.isBlinking
            repeat: true
            onTriggered: {
                if (turnSignal.isBlinking) {
                    turnSignal.opacity = turnSignal.opacity === 1.0 ? 0.0 : 1.0;
                } else {
                    turnSignal.opacity = 0.0;
                }
            }
        }
    }
}
