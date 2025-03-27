import QtQuick 2.15

Row {
    spacing: 5
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.topMargin: 20
    anchors.leftMargin: 80


    Rectangle {
        width: app.iconWidth
        height: app.iconHeight
        color: "transparent"
        Image {
            id: lowBeamSignal
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            source: "../assets/icons/low_beam_on.png"
            // visible: instrumentCluster.lowBeam
            visible: true
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
            source: "../assets/icons/high_beam_on.png"
            //visible: instrumentCluster.highBeam
            visible: true
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
            source: "../assets/icons/front_fog_on.png"
            // visible: instrumentCluster.frontFogLight
            visible: true
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
            source: "../assets/icons/parking_lights_on.png"
            // visible: instrumentCluster.parkingLight
            visible: true
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
            source: "../assets/icons/high_beam_on.png"
            // visible: instrumentCluster.rearFogLight
            visible: true
        }
    }
}
