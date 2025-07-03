import QtQuick 2.15
Row {
    anchors.top: parent.top
    anchors.topMargin: 25
    anchors.right: parent.right
    anchors.rightMargin: 50
    spacing: 10
    property string fontFamily: "default"
    
    Rectangle {
        width: 45
        height: 45
        color: "transparent"

        Image {
            source: "../assets/icons/raio.png"
            width: 35
            height: 35
            anchors.centerIn: parent
        }
    }

    Text {
        text: instrumentCluster.percentage + "%"
        font.pixelSize: 30
        // font.family: Qt.binding(function() { return app.font; })
        font.family: fontFamily
        color: "white"
    }

}