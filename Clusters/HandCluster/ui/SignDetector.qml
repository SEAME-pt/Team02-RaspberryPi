import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    id: root
    property int signDetected: instrumentCluster.signDetected
    property string signImage: ""

    Timer {
        id: hideTimer
        interval: 3000  // 3 seconds
        running: false
        repeat: false
        onTriggered: {
            signDetected = 0
            signImage = ""
        }
    }

    onSignDetectedChanged: {
        console.log("signDetected:", signDetected)

        switch(signDetected) {
            case 0: signImage = ""; break;
            // case 1: signImage = "../assets/icons/30.png"; break;
            // case 2: signImage = "../assets/icons/40.png"; break;
            case 3: signImage = "../assets/icons/50.png"; break;
            case 4: signImage = "../assets/icons/60.png"; break;
            case 5: signImage = "../assets/icons/70.png"; break;
            case 6: signImage = "../assets/icons/80.png"; break;
            case 7: signImage = "../assets/icons/90.png"; break;
            case 8: signImage = "../assets/icons/100.png"; break;
            case 9: signImage = "../assets/icons/120.png"; break;
            case 11: signImage = "../assets/icons/stop.png"; break;
            case 12: signImage = "../assets/icons/yield.png"; break;
            case 13: signImage = "../assets/icons/pedestrian.png"; break;
            default: signImage = ""; break;
        }
        console.log("signImage:", signImage);

        if (signDetected !== 0)
            hideTimer.restart();
    }

    Image {
        id: signDisplay
        // anchors.centerIn: parent
        visible: source !== ""
        width: 100
        height: 100
        fillMode: Image.PreserveAspectFit
        source: signImage + "?" + Date.now()
    }
}
