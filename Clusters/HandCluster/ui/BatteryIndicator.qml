import QtQuick 2.15

Column {
    anchors.right: parent.right
    anchors.rightMargin: 140
    anchors.verticalCenterOffset: -110
    anchors.verticalCenter: parent.verticalCenter
    spacing: 15

    CircularProgressBar {
        id: batteryPercentage
        lineWidth: 10
        value: instrumentCluster.percentage / 100
        size: 115
        secondaryColor: "#ffffff"
        primaryColor: instrumentCluster.percentage < 20 ? "#ff0000" : "#2fc71b"

        Text {
            text: parseInt(batteryPercentage.value * 100) + "%"
            anchors.centerIn: parent
            font.pixelSize: 22
            color: "#ffffff"
        }
    }
}
