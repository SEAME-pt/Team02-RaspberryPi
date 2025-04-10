import QtQuick 2.15

Canvas {
    id: laneCanvas
    width: 1280
    height: 400
    anchors.horizontalCenter: parent.horizontalCenter

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

    function generateLaneFromCoefficients(a, b, c) {
        var lanePoints = [];

        for (var y = height; y >= height / 100; y -= 5) { //for (var y = originalHeight; y >= originalHeight / 3; y -= 5)
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
        ctx.lineJoin = "round";
        ctx.lineCap = "round";
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

    function drawLaneWithGradient(a, b, c, startColor, endColor) {
        var points = generateLaneFromCoefficients(a, b, c, 256);
        if (points.length < 2) return;

        var ctx = getContext("2d");
        ctx.beginPath();
        ctx.lineJoin = "round";
        ctx.lineCap = "round";

        // Criando um gradiente que vai do topo para a base da tela
        var gradient = ctx.createLinearGradient(0, 0, 0, height);
        gradient.addColorStop(0, startColor); // Cor no topo (início da linha)
        gradient.addColorStop(1, endColor);   // Cor na base (final da linha)

        // Desenhando a linha
        for (var i = 0; i < points.length; i++) {
            var x = points[i].x;
            var y = points[i].y;
            if (i === 0) {
                ctx.moveTo(x, y);
            } else {
                ctx.lineTo(x, y);
            }
        }

        // Aplicando sombra
        ctx.shadowColor = "rgba(0, 0, 0, 0.5)";
        ctx.shadowBlur = 10;
        ctx.shadowOffsetX = 5;
        ctx.shadowOffsetY = 5;

        // Aplicando o gradiente ao contexto
        ctx.strokeStyle = gradient;
        ctx.stroke();

        // Resetando a sombra para não afetar outros desenhos
        ctx.shadowColor = "transparent";
        ctx.shadowBlur = 0;
        ctx.shadowOffsetX = 0;
        ctx.shadowOffsetY = 0;
    }


    onLeftLaneCoefsChanged: {
        requestPaint();
    }

    onRightLaneCoefsChanged: {
        requestPaint();
    }

    function drawRoadBackground(leftPoints, rightPoints) {
        var ctx = getContext("2d");
        ctx.beginPath();

        // Move pela esquerda de cima pra baixo
        for (var i = 0; i < leftPoints.length; i++) {
            var p = leftPoints[i];
            if (i === 0)
                ctx.moveTo(p.x, p.y);
            else
                ctx.lineTo(p.x, p.y);
        }

        // Agora volta pela direita de baixo pra cima
        for (var j = rightPoints.length - 1; j >= 0; j--) {
            var p = rightPoints[j];
            ctx.lineTo(p.x, p.y);
        }

        ctx.closePath();

        // Cria o degradê vertical de cinza com transparência no topo
        var gradient = ctx.createLinearGradient(0, 0, 0, height);
        gradient.addColorStop(0.0, "rgba(68, 68, 68, 0)");   // Topo da tela: transparente
        gradient.addColorStop(0.3, "rgba(68, 68, 68, 0.5)");
        gradient.addColorStop(1.0, "rgba(68, 68, 68, 1)");   // Base da tela: totalmente visível

        ctx.fillStyle = gradient;
        ctx.fill();
    }


    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height);

        ctx.lineWidth = 5;
        ctx.shadowBlur = 0;
        ctx.globalAlpha = 1.0;

        var leftPoints = [];
        var rightPoints = [];

        if (leftLaneCoefs && "a" in leftLaneCoefs) {
            leftPoints = generateLaneFromCoefficients(leftLaneCoefs.a, leftLaneCoefs.b, leftLaneCoefs.c, 256);
        }

        if (rightLaneCoefs && "a" in rightLaneCoefs) {
            rightPoints = generateLaneFromCoefficients(rightLaneCoefs.a, rightLaneCoefs.b, rightLaneCoefs.c, 256);
        }

        if (leftPoints.length > 0 && rightPoints.length > 0) {
            drawRoadBackground(leftPoints, rightPoints);
            drawLaneWithGradient(leftLaneCoefs.a, leftLaneCoefs.b, leftLaneCoefs.c, "rgba(200, 200, 200, 1)", "rgba(150, 150, 150, 1)");
            drawLaneWithGradient(rightLaneCoefs.a, rightLaneCoefs.b, rightLaneCoefs.c, "rgba(200, 200, 200, 1)", "rgba(150, 150, 150, 1)");
            drawCenterDashedLine(leftPoints, rightPoints);
        }
    }

}
