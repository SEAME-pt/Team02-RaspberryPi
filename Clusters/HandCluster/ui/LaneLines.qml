import QtQuick 2.15

Canvas {
    id: laneCanvas
    width: 1280
    height: 400
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 100
    anchors.topMargin: 100

    // These now bind directly to the QVariantMaps exposed from C++
    property var leftLaneCoefs: instrumentCluster.leftLaneCoefs
    property var rightLaneCoefs: instrumentCluster.rightLaneCoefs

    property var lastPaintTime: Date

    // Repaint logic
    function shouldRequestPaint() {
        var now = new Date();
        if (!lastPaintTime || (now - lastPaintTime) >= 100) {
            lastPaintTime = now;
            return true;
        }
        return false;
    }

    // Generates lane points from coefficients
    function generateLaneFromCoefficients(a, b, c, height) {
        var lanePoints = [];
        for (var y = height; y >= height / 3; y -= 5) {
            var x = a * y * y + b * y + c;
            lanePoints.push({ "x": x, "y": y });
        }
        return lanePoints;
    }

    // Draws a lane given coefficients
    function drawLane(a, b, c) {
        var points = generateLaneFromCoefficients(a, b, c, height);
        if (points.length < 2) return;

        var ctx = getContext("2d");
        ctx.beginPath();
        for (var i = 0; i < points.length; i++) {
            var point = points[i];
            if (i === 0) {
                ctx.moveTo(point.x, point.y);
            } else {
                ctx.lineTo(point.x, point.y);
            }
        }
        ctx.stroke();
    }

    // Left lane updated
    onLeftLaneCoefsChanged: {
        // console.log("Left lane updated:", leftLaneCoefs);
        requestPaint();
    }

    // Right lane updated
    onRightLaneCoefsChanged: {
        // console.log("Right lane updated:", rightLaneCoefs);
        requestPaint();
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height);

        ctx.lineWidth = 6;
        ctx.shadowBlur = 12;
        ctx.shadowColor = "rgba(0, 255, 0, 0.5)";
        ctx.globalAlpha = 1.0;

        if (leftLaneCoefs && "a" in leftLaneCoefs) {
            ctx.strokeStyle = "#ee4426";
            drawLane(leftLaneCoefs.a, leftLaneCoefs.b, leftLaneCoefs.c);
        }

        if (rightLaneCoefs && "a" in rightLaneCoefs) {
            ctx.strokeStyle = "#dde021";
            drawLane(rightLaneCoefs.a, rightLaneCoefs.b, rightLaneCoefs.c);
        }
    }
}
