import QtQuick 2.15
// import com.example.gearPosition 1.0

Column {
    spacing: 10

    Text {
        font.family: "Open Sans"
        text: "P"
        font.pixelSize: app.letterSize
        color: instrumentCluster.gear.park ? "blue" : "white"
    }
    Text {
        font.family: "Open Sans"
        text: "R"
        font.pixelSize: app.letterSize
        color: instrumentCluster.gear.reverse ? "blue" : "white"
    }
    Text {
        font.family: "Open Sans"
        text: "N"
        font.pixelSize: app.letterSize
        color: instrumentCluster.gear.neutral ? "blue" : "white"
    }
    Text {
        font.family: "Open Sans"
        text: "D"
        font.pixelSize: app.letterSize
        color: instrumentCluster.gear.drive ? "blue" : "white"
    }
}