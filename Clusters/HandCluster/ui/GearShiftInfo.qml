import QtQuick 2.15
// import com.example.gearPosition 1.0

Column {
    spacing: 10

    Text {
        font.family: "Open Sans"
        text: "P"
        font.pixelSize: instrumentCluster.gear.park ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.park ? "blue" : "white"
        y: instrumentCluster.gear.park ? gearOffset : 0
    }
    Text {
        font.family: "Open Sans"
        text: "R"
        font.pixelSize: instrumentCluster.gear.reverse ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.reverse ? "blue" : "white"
        y: instrumentCluster.gear.reverse ? gearOffset : 0
    }
    Text {
        font.family: "Open Sans"
        text: "N"
        font.pixelSize: instrumentCluster.gear.neutral ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.neutral ? "blue" : "white"
        y: instrumentCluster.gear.neutral ? gearOffset : 0
    }
    Text {
        font.family: "Open Sans"
        text: "D"
        font.pixelSize: instrumentCluster.gear.drive ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.drive ? "blue" : "white"
        y: instrumentCluster.gear.drive ? gearOffset : 0
    }
}