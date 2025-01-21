import QtQuick 2.15

Column {
    spacing: 10

    Rectangle {
        width: app.iconWidth
        height: app.iconHeight
        color: "transparent" // Keeps the placeholder invisible
        Image {
            id: lowBeamSignal
            anchors.centerIn: parent
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
            source: "qrc:/assets/icons/back_fog_on.png"
            visible: instrumentCluster.lights.rearFogLight
        }
    }
}
