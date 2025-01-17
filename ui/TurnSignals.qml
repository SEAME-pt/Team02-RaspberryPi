import QtQuick 2.15

Row {
    id: root
    spacing: 10
    
    Image {
        anchors.verticalCenter: parent.verticalCenter
        id: turnSignal
        source: instrumentCluster.rightBlinker ? "qrc:/assets/icons/turn_right_on.png" : "qrc:/assets/icons/turn_left_on.png"
        width: 70
        height: 70
        opacity: 0.0
        visible: instrumentCluster.rightBlinker || instrumentCluster.leftBlinker
        
        Timer {
            id: blinkTimer
            interval: 500
            running: instrumentCluster.rightBlinker || instrumentCluster.leftBlinker // Start the timer if any blinker is on
            repeat: true
            onTriggered: {
                // Toggle opacity when blinking
                turnSignal.opacity = turnSignal.opacity === 1.0 ? 0.0 : 1.0;
            }
        }
    }
}
