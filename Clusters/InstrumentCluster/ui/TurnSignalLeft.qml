import QtQuick 2.15


Row {
    id: root
    spacing: 10
    
 Rectangle {
        width: 70
        height: 70
        color: "transparent"
        Image {
            anchors.verticalCenter: parent.verticalCenter
            id: turnSignal
            source: "qrc:/assets/icons/turn_left_on.png"
            width: 70
            height: 70
            opacity: 0.0
            visible: instrumentCluster.leftBlinker
            
            Timer {
                id: blinkTimer
                interval: 500
                running: instrumentCluster.leftBlinker
                repeat: true
                onTriggered: {
                    // Toggle opacity when blinking
                    turnSignal.opacity = turnSignal.opacity === 1.0 ? 0.0 : 1.0;
                }
            }
        }
    }
}

