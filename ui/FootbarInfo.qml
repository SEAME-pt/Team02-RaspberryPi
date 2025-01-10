import QtQuick 2.15

Row {
    width: parent.width
    height: 50
    spacing: 30
    padding: 10

    Column {

        Row {
            spacing: 5
            Text {
                font.family: "Open Sans"
                text: canBusHandler.battery
                font.pixelSize: app.letterSize
                color: "white"
            }
            Text {
                font.family: "Open Sans"
                text: "%"
                font.pixelSize: app.letterSize
                color: "gray"
            }
        }
    }

    Column {

        Row {
            spacing: 5
            Text {
                font.family: "Open Sans"
                text: "256"
                font.pixelSize: app.letterSize
                color: "white"
            }
            Text {
                font.family: "Open Sans"
                text: "mi"
                font.pixelSize: app.letterSize
                color: "gray"
            }
        }
    }
    Column {

        Row {
            spacing: 5
            Text {
                font.family: "Open Sans"
                text: "22°"
                font.pixelSize: app.letterSize
                color: "white"
            }
            Text {
                font.family: "Open Sans"
                text: "G"
                font.pixelSize: app.letterSize
                color: "gray"
            }
        }
    }

}
