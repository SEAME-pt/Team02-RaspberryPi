import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app
    property int letterSize: 25
    property int letterSizeLoaded: 28
    visible: true
    width: 1024
    height: 600

    property int iconWidth: 35
    property int iconHeight: 35

    FontLoader {
        id: customFont
        source: "file:///usr/share/fonts/electrolize.ttf"
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
        color: "black"
    }
    
    LaneLines {
        id: laneLines 
        leftLanePoints: instrumentCluster.leftLanePoints
        rightLanePoints: instrumentCluster.rightLanePoints
    }
    SpeedDisplay {}
    GearDisplay {}
    BatteryIndicator {}

    TimeInfo {}
    LightInfo {}
}
