import QtQuick 2.15
import QtQuick.Controls 2.15
import canbus 1.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    title: "Instrument Cluster with Smooth Transitions"

    CANBusHandler {
        id: canBusHandler
        onSpeedChanged: speedGauge.requestPaint()
        onBatteryChanged: batteryGauge.requestPaint()
    }

    Rectangle {
        anchors.fill: parent

        // Background Gradient
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                var gradient = ctx.createLinearGradient(0, 0, 0, height);
                gradient.addColorStop(0, "#001848"); // Top dark blue
                gradient.addColorStop(1, "#000022"); // Bottom darker blue
                ctx.fillStyle = gradient;
                ctx.fillRect(0, 0, width, height);
            }
        }

        // Top Highlight Bar
        Canvas {
            height: 50
            width: parent.width
            anchors.top: parent.top
            onPaint: {
                var ctx = getContext("2d");
                var gradient = ctx.createLinearGradient(0, 0, 0, height);
                gradient.addColorStop(0, "rgba(255, 255, 255, 0.1)");
                gradient.addColorStop(1, "transparent");
                ctx.fillStyle = gradient;
                ctx.fillRect(0, 0, width, height);
            }
        }

        // Bottom Shadow Bar
        Canvas {
            height: 50
            width: parent.width
            anchors.bottom: parent.bottom
            onPaint: {
                var ctx = getContext("2d");
                var gradient = ctx.createLinearGradient(0, 0, 0, height);
                gradient.addColorStop(0, "transparent");
                gradient.addColorStop(1, "rgba(0, 0, 0, 0.5)");
                ctx.fillStyle = gradient;
                ctx.fillRect(0, 0, width, height);
            }
        }

        // Left Speedometer Gauge
        Canvas {
            id: speedGauge
            width: 300
            height: 300
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20

            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);

                // Speed Value
                ctx.font = "36px sans-serif";
                ctx.fillStyle = "white";
                ctx.textAlign = "center";
                ctx.fillText(canBusHandler.speed, width / 2, height / 2);

                // Label
                ctx.font = "18px sans-serif";
                ctx.fillStyle = "lightgray";
                ctx.fillText("Speed", width / 2, height / 2 + 40);
            }
        }

        // Right Battery Status Gauge
        Canvas {
            id: batteryGauge
            width: 300
            height: 300
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20

            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);

                // Battery Value
                ctx.font = "36px sans-serif";
                ctx.fillStyle = "white";
                ctx.textAlign = "center";
                ctx.fillText(canBusHandler.battery + " %", width / 2, height / 2);

                // Label
                ctx.font = "18px sans-serif";
                ctx.fillStyle = "lightgray";
                ctx.fillText("Battery", width / 2, height / 2 + 40);
            }
        }
    }
}
