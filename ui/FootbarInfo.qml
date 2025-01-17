import QtQuick 2.15

Row {
    width: parent.width
    height: 50
    spacing: 30
    padding: 10
    Column {

        Row {

            anchors.verticalCenterOffset: -10
            Image {
                id: batteryLevel
                // source: {
                //     if (canBusHandler.battery >= 80) {
                //         "qrc:/assets/icons/battery-5.png"
                //     } else if (canBusHandler.battery >= 60) {
                //         "qrc:/assets/icons/battery-4.png"
                //     } else if (canBusHandler.battery >= 40) {
                //         "qrc:/assets/icons/battery-3.png"
                //     } else if (canBusHandler.battery >= 20) {
                //         "qrc:/assets/icons/battery-2.png"
                //     } else {
                //         "qrc:/assets/icons/battery-1.png"
                //     }
                // }
                width: 80
                visible: true
                fillMode: Image.PreserveAspectFit
                source: "qrc:/assets/icons/battery-4.png" 
                // Adjust this value to move the image up or down
            }
        }
        // Row {
        //     spacing: 5

        //     Text {
        //         font.family: "Open Sans"
        //         //text: canBusHandler.battery
        //         text: "100"
        //         font.pixelSize: app.letterSize
        //         color: "white"
        //     }
        //     Text {
        //         font.family: "Open Sans"
        //         text: "%"
        //         font.pixelSize: app.letterSize
        //         color: "gray"
        //     }
        // }
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
                text: "C"
                font.pixelSize: app.letterSize
                color: "gray"
            }
        }
    }

}
