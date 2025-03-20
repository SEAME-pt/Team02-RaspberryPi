import QtQuick 2.15

Row {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 25
    spacing: 16

    function gearColor(gearValue) {
        return instrumentCluster.gear === gearValue ? "blue" : "white";
    }

    function gearSize(gearValue) {
        return instrumentCluster.gear === gearValue ? app.letterSizeLoaded : app.letterSize;
    }

    Text { text: "P"; font.pixelSize: gearSize(127); color: gearColor(127) }
    Text { text: "R"; font.pixelSize: gearSize(-1); color: gearColor(-1) }
    Text { text: "N"; font.pixelSize: gearSize(0); color: gearColor(0) }
    Text { text: "D"; font.pixelSize: gearSize(1); color: gearColor(1) }
}
