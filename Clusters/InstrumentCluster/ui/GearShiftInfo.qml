import QtQuick 2.15
// import com.example.gearPosition 1.0

Row {
    spacing: 20

    Text {
        font.family: "Open Sans"
        text: "P"
        font.pixelSize: instrumentCluster.gear == 127 ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear == 127 ? "blue" : "white"
        y: instrumentCluster.gear == 127 ? gearOffset : 0
    }
    Text {
        font.family: "Open Sans"
        text: "R"
        font.pixelSize: instrumentCluster.gear == -1 ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear == -1 ? "blue" : "white"
        y: instrumentCluster.gear == -1 ? gearOffset : 0
    }
    Text {
        font.family: "Open Sans"
        text: "N"
        font.pixelSize: instrumentCluster.gear == 0 ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear == 0 ? "blue" : "white"
        y: instrumentCluster.gear == 0 ? gearOffset : 0
    }
    Text {
        font.family: "Open Sans"
        text: "D"
        font.pixelSize: instrumentCluster.gear == 1 ? app.letterSizeLoaded : app.letterSize
        color: instrumentCluster.gear == 1 ? "blue" : "white"
        y: instrumentCluster.gear == 1 ? gearOffset : 0
    }
}