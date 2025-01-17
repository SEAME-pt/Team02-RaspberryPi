import QtQuick 2.15

Column {
    spacing: 10

    Text {
        font.family: "Open Sans"
        text: "P"
        font.pixelSize: app.letterSize
        // color: instrumentCluster.gear === GearPosition.PARK ? "blue" : "white"
        color: "white"
    }
    Text {
        font.family: "Open Sans"
        text: "R"
        font.pixelSize: app.letterSize
        // color: instrumentCluster.gear === GearPosition.REVERSE ? "blue" : "white"
        color: "white"
    }
    Text {
        font.family: "Open Sans"
        text: "N"
        font.pixelSize: app.letterSize
        color: instrumentCluster.gear === GearPosition.NEUTRAL ? "blue" : "white"
        color: "white"
    }
    Text {
        font.family: "Open Sans"
        text: "D"
        font.pixelSize: app.letterSize
        color: instrumentCluster.gear === GearPosition.DRIVE ? "blue" : "white"
        color: "white"
    }
}