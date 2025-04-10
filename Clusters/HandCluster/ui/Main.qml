import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 25
    property int letterSizeLoaded: 28
    visible: true
    width: 1280
    height: 400

    // minimumWidth: 1280
    // maximumWidth: 1280
    // minimumHeight: 400
    // maximumHeight: 400
    property int iconWidth: 35
    property int iconHeight: 35

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
        width: parent.width * 2/4   // Ocupa 2/3 da tela
        height: parent.height * 0.7// 80% da altura, sem tocar no topo
        // anchors.right: parent.right // Fixa no lado direito
        anchors.bottom: parent.bottom
        // leftLanePoints: leftLaneMock
        // rightLanePoints: rightLaneMock
    }

    Image { 
        id: carImage
        width: parent.width * 1/4   // Ocupa 1/4 da largura da tela
        height: parent.height * 0.6 // 70% da altura
        source: "../assets/images/car.png"
        anchors.horizontalCenter: parent.horizontalCenter // Centraliza horizontalmente
        anchors.bottom: parent.bottom // Fixa na parte superior
        anchors.bottomMargin: -35

    }
    ObjectDetector {
        id: objectDetector
        width: parent.width // Ajusta a largura para ocupar o espaço do retângulo
        height: parent.height * 0.6 // Ajusta a altura para ocupar o espaço do retângulo
        anchors.right: parent.right // Fixa no lado direito
        anchors.bottom: parent.bottom
        anchors.topMargin: 50
    }
    SpeedDisplay {}
    GearDisplay {}
    BatteryIndicator {}

    TimeInfo {}
    LightInfo {}
}
