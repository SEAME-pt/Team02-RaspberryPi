import QtQuick 2.15
// import com.example.gearPosition 1.0

Row {
    spacing: 15

    Text {
        font.family: "Open Sans"
        text: "P"
        font.pixelSize: instrumentCluster.gear.park ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.park ? "blue" : "white"
    }
    Text {
        font.family: "Open Sans"
        text: "R"
        font.pixelSize: instrumentCluster.gear.reverse ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.reverse ? "blue" : "white"
    }
    Text {
        font.family: "Open Sans"
        text: "N"
                font.pixelSize: instrumentCluster.gear.neutral ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.neutral ? "blue" : "white"
    }
    Text {
        font.family: "Open Sans"
        text: "D"
        font.pixelSize: instrumentCluster.gear.drive ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear.drive ? "blue" : "white"
    }
}