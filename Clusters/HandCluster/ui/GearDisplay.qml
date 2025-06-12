import QtQuick 2.15

Row {
    anchors.right: parent.right
    anchors.verticalCenter: parent.verticalCenter
    anchors.rightMargin: 40
    spacing: 16
    property string fontFamily: "default"

    function gearColor(gearValue) {
        return instrumentCluster.gear === gearValue ? "blue" : "white";
    }

    function gearSize(gearValue) {
        return instrumentCluster.gear === gearValue ? app.letterSizeLoaded : app.letterSize;
    }
    
    Column {
        spacing: 8

        Text { text: "P"; font.family: fontFamily; font.pixelSize: gearSize(127); color: gearColor(127) }
        Text { text: "R"; font.family: fontFamily; font.pixelSize: gearSize(-1); color: gearColor(-1) }
        Text { text: "N"; font.family: fontFamily; font.pixelSize: gearSize(0); color: gearColor(0) }
        Text { text: "D"; font.family: fontFamily; font.pixelSize: gearSize(1); color: gearColor(1) }
    }
}
