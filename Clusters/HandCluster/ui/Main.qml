import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 40
    property int letterSizeLoaded: 45
    visible: true
    width: Screen.width
    height:  Screen.height
    // flags: Qt.FramelessWindowHint

    property int iconWidth: 65
    property int iconHeight: 65

    property string fontPath1: Qt.resolvedUrl("file:/opt/vehicle/etc/fonts/electrolize.ttf")
    property bool fontExists: false

    FontLoader {
        id: customFont
        source: fontPath1
    }

    Component.onCompleted: {
        console.log("Font Status:", customFont.status)
        if (customFont.status === FontLoader.Ready) {
            console.log("Fonte carregada com sucesso:", customFont.name)
            app.font = customFont.name
            forceLayoutUpdate();
        } else {
            console.log("Erro ao carregar a fonte:", customFont.status)
        }
    }

    function forceLayoutUpdate() {
        app.width = app.width + 1;
        app.width = app.width - 1;
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#252525"
    }

    LaneLines {
        id: laneLines 
        width: parent.width * 2/4
        height: parent.height * 0.7
        // anchors.right: parent.right
        anchors.bottom: parent.bottom
        // leftLanePoints: leftLaneMock
        // rightLanePoints: rightLaneMock
    }

    ObjectDetector {
        id: objectDetector
        width: parent.width * 2/4
        height: parent.height * 0.9
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 50
    }

    Image { 
        id: carImage
        width: parent.width * 1/4
        height: parent.height * 0.6
        source: "../assets/images/car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom 
        anchors.bottomMargin: -35
    }

    SpeedDisplay {
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    GearDisplay {
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    BatteryIndicator {
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    TimeInfo {
        id: timeInfo
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }
    
    NotificationBlock {
        warningCode: instrumentCluster.warningCode
        fontFamily: customFont.status === FontLoader.Ready ? customFont.name : "default"
    }

    LightInfo {}
}