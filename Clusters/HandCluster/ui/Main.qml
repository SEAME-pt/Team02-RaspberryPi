import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 28
    property int letterSizeLoaded: 30
    visible: true
    width: 1280
    height: 400

    // minimumWidth: 1280
    // maximumWidth: 1280
    // minimumHeight: 400
    // maximumHeight: 400
    property int iconWidth: 40
    property int iconHeight: 40

    // Defina a primeira fonte
    property string fontPath1: "file:///usr/share/fonts/electrolize.ttf"
    property string fontPath2: "../assets/fonts/electrolize.ttf"
    property bool fontExists: false

    // FontLoader que será alterado conforme a existência do arquivo
    FontLoader {
        id: customFont
        source: fontExists ? fontPath2 : fontPath1
    }

    // Combina a lógica de verificação da fonte e a atualização de layout em uma única função
    Component.onCompleted: {
        var file = Qt.openUrlExternally(fontPath1);
        if (file !== "") {
            fontExists = true;
        } else {
            fontExists = false;
        }

        // Verifica o status da fonte
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

    SpeedDisplay {}
    GearDisplay {}
    BatteryIndicator {}

    TimeInfo {
        id: timeInfo
    }
    
    NotificationBlock {
        warningCode: instrumentCluster.warningCode
    }

    LightInfo {}
}
