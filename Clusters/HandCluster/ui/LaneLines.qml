
import QtQuick 2.15

Canvas {
    id: laneCanvas
    width: parent.width
    height: parent.height
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 100
    anchors.topMargin: 100

    property var leftLanePoints: instrumentCluster.leftLanePoints
    property var rightLanePoints: instrumentCluster.rightLanePoints

    // onLeftLanePointsChanged: {
    //     // console.log("Left lane updated:");
    //     // for (var i = 0; i < leftLanePoints.length; i++) {
    //     //     console.log("Point " + i + ": (" + leftLanePoints[i].x + ", " + leftLanePoints[i].y + ")");
    //     // }
    //     requestPaint();
    // }

    onRightLanePointsChanged: {
        // console.log("Right lane updated:");
        // for (var i = 0; i < rightLanePoints.length; i++) {
        //     console.log("Point " + i + ": (" + rightLanePoints[i].x + ", " + rightLanePoints[i].y + ")");
        // }
        requestPaint();
    }

    // Component.onCompleted: {
    //     console.log("LaneLines in Canvas initialized!");
    // }

    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height);

        ctx.lineWidth = 6;
        ctx.shadowBlur = 20;
        ctx.shadowColor = "rgba(200, 200, 200, 0.5)";

        var gradient = ctx.createLinearGradient(0, height / 2, 0, height);
        gradient.addColorStop(0, "rgba(255, 255, 255, 0.9)");
        gradient.addColorStop(1, "rgba(150, 150, 150, 0.2)");

        ctx.strokeStyle = gradient;
        ctx.globalAlpha = 0.8;

        function drawLane(points) {
            if (!points || points.length < 2) return;
            ctx.beginPath();
            ctx.moveTo(points[0].x, points[0].y);

            for (var i = 1; i < points.length - 1; i++) {
                var xc = (points[i].x + points[i + 1].x) / 2;
                var yc = (points[i].y + points[i + 1].y) / 2;
                ctx.quadraticCurveTo(points[i].x, points[i].y, xc, yc);
            }

            ctx.lineTo(points[points.length - 1].x, points[points.length - 1].y);
            ctx.stroke();
        }

        drawLane(leftLanePoints);
        drawLane(rightLanePoints);

        ctx.fillStyle = "blue";
        ctx.font = app.font;
        ctx.fillText("Canvas Rendered", 10, 30);
    }
}
