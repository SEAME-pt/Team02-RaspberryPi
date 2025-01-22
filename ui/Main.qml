import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: app
    visible: true
    width: Screen.width
    height: Screen.height
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    visibility: Window.FullScreen  // Add this line

    property int letterSize: 25
    property int letterSizeLoaded: 30
    property int iconWidth: 10
    property int iconHeight: 10
    property bool carClusterVisible: true
    property bool showSplash: true

    font.family: "Roboto"
    font.pixelSize: 30 
    font.bold: false

    // Car CLuster
    Rectangle {
        anchors.fill: parent
        visible: app.carClusterVisible

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#000000" }
            GradientStop { position: 1.0; color: "#808080" }
        }
        
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            width: 100
            height: 100
            color: "transparent"
            Image {
                id: car
                anchors.centerIn: parent
                source: "qrc:/assets/images/car.png"
                visible: true
            }
        }
        Row {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            spacing: 10

            TurnSignalLeft {}
            SpeedDisplay {}
            TurnSignalRight {}
        }

        GearShiftInfo {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 15
        }

        LightInfo {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 15
        }

        FootbarInfo {
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 20
        }

        TimeInfo {
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 20
        }
    }

    // // Logo Screen
    // Rectangle {
    //     id: splashScreen
    //     visible: app.showSplash
    //     anchors.fill: parent
    //     color: "black"

    //     // O retângulo sempre fica visível, mas apenas o logo tem a opacidade animada
    //     Image {
    //         id: logo
    //         source: "qrc:/assets/icons/seame-logo.png" // Substitua pelo logo do carro
    //         anchors.centerIn: parent
    //         width: parent.width * 0.5
    //         height: parent.width * 0.5
    //         fillMode: Image.PreserveAspectFit
    //         opacity: 1.0 // Começa visível

    //         SequentialAnimation {
    //             running: true
    //             loops: 1

    //             // Transição para mostrar o logo
    //             PropertyAnimation {
    //                 target: logo
    //                 property: "opacity"
    //                 from: 0.0
    //                 to: 1.0
    //                 duration: 3000 // 3 segundos
    //             }

    //             PauseAnimation { duration: 1000 } // Aguarda 1 segundo com o logo visível

    //             // Transição para esconder o logo
    //             PropertyAnimation {
    //                 target: logo
    //                 property: "opacity"
    //                 from: 1.0
    //                 to: 0.0
    //                 duration: 2000 // 2 segundos
    //             }

    //             PauseAnimation { duration: 1000 } // Aguarda 2 segundos com a tela preta

    //             ScriptAction {
    //                 script: {
    //                     app.showSplash = false; // Oculta a splash screen
    //                     app.carClusterVisible = true; // Mostra o cluster
    //                 }
    //             }
    //         }
    //     }
    // }


}