import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example.canbus 1.0

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

            property real angle: 0.75 * Math.PI

            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);

                // Background gradient for the circular gauge
                var bgGradient = ctx.createRadialGradient(width / 2, height / 2, 50, width / 2, height / 2, 120);
                bgGradient.addColorStop(0, "#001848");
                bgGradient.addColorStop(1, "#002060");
                ctx.fillStyle = bgGradient;
                ctx.beginPath();
                ctx.arc(width / 2, height / 2, 120, 0, 2 * Math.PI);
                ctx.fill();

                // Draw Speed Arc based on speed value
                var arcStartAngle = 0.75 * Math.PI; // Start at 270 degrees (left)
                var arcEndAngle = arcStartAngle + (Math.PI * canBusHandler.speed / 180); // Map speedValue to an arc from 0 to 180 degrees
                var arcGradient = ctx.createLinearGradient(0, 0, width, height);
                arcGradient.addColorStop(0, "#00ff00");
                arcGradient.addColorStop(1, "#004000");
                ctx.lineWidth = 15;
                ctx.strokeStyle = arcGradient;
                ctx.beginPath();
                ctx.arc(width / 2, height / 2, 100, arcStartAngle, arcEndAngle);
                ctx.stroke();

                // Speed Value
                ctx.font = "36px Arial";
                ctx.fillStyle = "white";
                ctx.textAlign = "center";
                ctx.fillText(canBusHandler.speed + " km/h", width / 2, height / 2);

                // Label
                ctx.font = "18px Arial";
                ctx.fillStyle = "lightgray";
                ctx.fillText("km/h", width / 2, height / 2 + 40);
            }

            // Speed angle animation with smoother transition
            NumberAnimation {
                id: speedAnimation
                target: speedGauge
                property: "angle"
                from: speedGauge.angle
                to: 0.75 * Math.PI + (Math.PI * canBusHandler.speed / 180)
                duration: 1000 // 1 second transition for smoother effect
                easing.type: Easing.InOutQuad // Smoother easing
                running: true
                onRunningChanged: {
                    speedGauge.requestPaint(); // Trigger repaint when animation is running
                }
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

            property real angle: 0.75 * Math.PI // Initial angle for the arc

            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);

                // Background gradient for the circular gauge
                var bgGradient = ctx.createRadialGradient(width / 2, height / 2, 50, width / 2, height / 2, 120);
                bgGradient.addColorStop(0, "#001848");
                bgGradient.addColorStop(1, "#002060");
                ctx.fillStyle = bgGradient;
                ctx.beginPath();
                ctx.arc(width / 2, height / 2, 120, 0, 2 * Math.PI);
                ctx.fill();

                // Draw Battery Arc based on battery value
                var arcStartAngle = 0.75 * Math.PI; // Start at 270 degrees (left)
                var arcEndAngle = arcStartAngle + (Math.PI * canBusHandler.battery / 500); // Map batteryValue to an arc from 0 to 180 degrees
                var arcGradient = ctx.createLinearGradient(0, 0, width, height);
                arcGradient.addColorStop(0, "#ffcc00"); // Yellow arc for battery status
                arcGradient.addColorStop(1, "#e0b100");
                ctx.lineWidth = 15;
                ctx.strokeStyle = arcGradient;
                ctx.beginPath();
                ctx.arc(width / 2, height / 2, 100, arcStartAngle, arcEndAngle);
                ctx.stroke();

                // Battery Value
                ctx.font = "36px Arial";
                ctx.fillStyle = "white";
                ctx.textAlign = "center";
                ctx.fillText(canBusHandler.battery + " km", width / 2, height / 2);

                // Label
                ctx.font = "18px Arial";
                ctx.fillStyle = "lightgray";
                ctx.fillText("Battery", width / 2, height / 2 + 40);
            }

            // Battery angle animation with smoother transition
            NumberAnimation {
                id: batteryAnimation
                target: batteryGauge
                property: "angle"
                from: batteryGauge.angle
                to: 0.75 * Math.PI + (Math.PI * canBusHandler.battery / 500)
                duration: 1000 // 1 second transition for smoother effect
                easing.type: Easing.InOutQuad // Smoother easing
                running: true
                onRunningChanged: {
                    batteryGauge.requestPaint(); // Trigger repaint when animation is running
                }
            }
        }
    }
}
