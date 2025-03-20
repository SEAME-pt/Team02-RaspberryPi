import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 18
    property int letterSizeLoaded: 20
    visible: true
    width: 1024
    height: 600

    Rectangle {
        width: parent.width
        height: parent.height
        color: "black"

    }
    
    LaneLines {
        id: laneLines 
        leftLanePoints: instrumentCluster.leftLanePoints
        rightLanePoints: instrumentCluster.rightLanePoints

        Component.onCompleted: {
            console.log("LaneLines initialized heyyy");
            // console.log("leftLanePoints: ", leftLanePoints[0].x, leftLanePoints[0].y);  // Access x and y
            // console.log("rightLanePoints: ", rightLanePoints[0].x, rightLanePoints[0].y);  // Access x and y
        }   
    }


    SpeedDisplay {}
    GearDisplay {}
    BatteryIndicator {}
}
