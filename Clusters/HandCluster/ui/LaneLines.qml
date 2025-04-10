import QtQuick 2.15

Canvas {
    id: laneCanvas
    width: 1280
    height: 400
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 100
    anchors.topMargin: 100

    property var leftLaneCoefs: instrumentCluster.leftLaneCoefs
    property var rightLaneCoefs: instrumentCluster.rightLaneCoefs
    property var lastPaintTime: Date

    function shouldRequestPaint() {
        var now = new Date();
        if (!lastPaintTime || (now - lastPaintTime) >= 100) {
            lastPaintTime = now;
            return true;
        }
        return false;
    }

    function generateLaneFromCoefficients(a, b, c, originalHeight) {
        var scaleY = height / originalHeight;
        var lanePoints = [];

        for (var y = originalHeight; y >= originalHeight / 3; y -= 5) {
            var x = a * y * y + b * y + c;
            lanePoints.push({
                "x": x,
                "y": y
            });
        }
        return lanePoints;
    }

    function drawLane(a, b, c, color) {
        var points = generateLaneFromCoefficients(a, b, c, 256);
        if (points.length < 2) return;

        var ctx = getContext("2d");
        ctx.beginPath();
        // ctx.lineJoin = "round";
        // ctx.lineCap = "round";
        for (var i = 0; i < points.length; i++) {
            var x = points[i].x;
            var y = points[i].y;
            if (i === 0) {
                ctx.moveTo(x, y);
            } else {
                ctx.lineTo(x, y);
            }
        }
        ctx.strokeStyle = color;
        ctx.stroke();
    }

    onLeftLaneCoefsChanged: {
        requestPaint();
    }

    onRightLaneCoefsChanged: {
        requestPaint();
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height);

        ctx.lineWidth = 5;
        ctx.shadowBlur = 0;
        ctx.globalAlpha = 1.0;

        if (leftLaneCoefs && "a" in leftLaneCoefs) {
            drawLane(leftLaneCoefs.a, leftLaneCoefs.b, leftLaneCoefs.c, "#0000ff"); // Azul
        }

        if (rightLaneCoefs && "a" in rightLaneCoefs) {
            drawLane(rightLaneCoefs.a, rightLaneCoefs.b, rightLaneCoefs.c, "#00ff00"); // Verde
        }
    }
}
