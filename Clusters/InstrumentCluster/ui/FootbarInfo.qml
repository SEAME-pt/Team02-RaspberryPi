import QtQuick 2.15

Row {
    width: parent.width
    height: 50
    spacing: 30
    padding: 10

    Column {
        Row {
            spacing: 5

            Image {
                id: cloudIcon
                source: "qrc:/assets/icons/cloud.png"
                width: app.iconWidth - 5
                height: app.iconHeight - 5
                visible: true
                fillMode: Image.PreserveAspectFit
            }
            
            Rectangle {
                width: 7 // Adjust the width to set the desired space
                height: 1
                color: "transparent"
            }

            Text {
                font.family: "Open Sans"
                text: "22°"
                font.pixelSize: app.letterSize
                color: "white"
            }
            Text {
                font.family: "Open Sans"
                text: "C"
                font.pixelSize: app.letterSize
                color: "gray"
            }
        }
    }

}
