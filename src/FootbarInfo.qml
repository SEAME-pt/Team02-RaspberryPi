import QtQuick 2.15

Row {
    width: parent.width
    height: 50
    spacing: 10
    padding: 10

    Column {
        anchors.right: parent.right
        anchors.rightMargin: 200
        spacing: 25

        Row {
            spacing: 3
            Text {
                font.family: "Open Sans"
                text: "P"
                font.pixelSize: app.letterSize
                color: "gray"
            }
            // ...remaining gear indicators...
        }
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: 200
        spacing: 25

        Row {
            spacing: 3
            Text {
                font.family: "Open Sans"
                text: "P"
                font.pixelSize: app.letterSize
                color: "gray"
            }
            // ...remaining gear indicators...
        }
    }

}
