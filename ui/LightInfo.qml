import QtQuick 2.15

Column {
    spacing: 10

    Image {
        id: lowBeamSignal
        source: "qrc:/assets/icons/low_beam_on.png"
        width: app.iconWidth
        height: app.iconHeight
        visible: instrumentCluster.lights.lowBeam
    }

    Image {
        id: highBeamSignal
        source: "qrc:/assets/icons/high_beam_on.png"
        width: app.iconWidth
        height: app.iconHeight
        visible: instrumentCluster.lights.highBeam
    }

    Image {
        id: frontFogSignal
        source: "qrc:/assets/icons/front_fog_on.png"
        width: app.iconWidth
        height: app.iconHeight
        visible: instrumentCluster.lights.frontFogLight
    }

    Image {
        id: parkingLightsSignal
        source: "qrc:/assets/icons/parking_lights_on.png"
        width: app.iconWidth
        height: app.iconHeight
        visible: instrumentCluster.lights.parkingLight
    }

    Image {
        id: backFogSignal
        source: "qrc:/assets/icons/back_fog_on.png"
        width: app.iconWidth
        height: app.iconHeight
        visible: instrumentCluster.lights.rearFogLight
    }
}
