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
            visible: instrumentCluster.lowBeam
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
            visible: instrumentCluster.highBeam
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
            visible: instrumentCluster.frontFogLight
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
            visible: instrumentCluster.parkingLight
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
            source: "../assets/icons/back_fog_on.png"
            visible: instrumentCluster.rearFogLight
        }
    }

    Rectangle {
        color: "transparent" 
        width: app.iconWidth * 13
        height: app.iconHeight
    }

    Rectangle {
        width: app.iconWidth + 3
        height: app.iconHeight + 3
        color: "transparent"
        Image {
            id: autonomySignal
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            source: instrumentCluster.autonomyLevel == 1 ? "../assets/icons/assist-steer-on.png" :
                    (instrumentCluster.autonomyLevel == 5 ? "../assets/icons/assist-navigate-driving-on.png" : "")
            visible: instrumentCluster.autonomyLevel == 1 || instrumentCluster.autonomyLevel == 5
        }
    }
    Rectangle {
        width: app.iconWidth + 3
        height: app.iconHeight + 3
        color: "transparent"
        Image {
            id: laneDepartureSignal
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            source: "../assets/icons/lane-departure.png"
            visible: instrumentCluster.laneDeparture
        }
    }
}
