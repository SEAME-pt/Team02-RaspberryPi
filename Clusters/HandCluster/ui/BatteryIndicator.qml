import QtQuick 2.15
Row {
    anchors.top: parent.top
    anchors.topMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 80
    spacing: 10

    
    Rectangle {
        width: 20
        height: 30
        color: "transparent"

        Image {
            source: "../assets/icons/raio.png"
            width: 20
            height: 20
            anchors.centerIn: parent
        }
    }

    Text {
        text: instrumentCluster.percentage + "%"
        font.pixelSize: 20
        // font.family: Qt.binding(function() { return app.font; })
        font.family: app.font
        color: "white"
    }

    Item {
        width: 10
        height: 1
    }

    Text {
        text: instrumentCluster.autonomy + "m"
        font.pixelSize: 20
        // font.family: Qt.binding(function() { return app.font; })
        font.family: app.font
        color: "white"
    }
}