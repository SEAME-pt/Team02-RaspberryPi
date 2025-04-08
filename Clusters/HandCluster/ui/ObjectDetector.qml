import QtQuick 2.15

Canvas {
    id: objectCanvas
    width: 1280
    height: 400
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 100
    anchors.topMargin: 100

    // Exposed QVariantMap from C++
    property var detectedObject: instrumentCluster.object
    property var lastPaintTime: Date

    // Repaint logic (optional, for throttling)
    function shouldRequestPaint() {
        var now = new Date();
        if (!lastPaintTime || (now - lastPaintTime) >= 100) {
            lastPaintTime = now;
            return true;
        }
        return false;
    }

    // Trigger repaint when object changes
    onDetectedObjectChanged: {
        requestPaint();
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height);

        if (detectedObject && "x" in detectedObject) {
            var obj = detectedObject;
            var x = obj.x - obj.width / 2;
            var y = obj.y - obj.height / 2;

            // Draw bounding box
            ctx.strokeStyle = "#00bfff"; // sky blue
            ctx.lineWidth = 3;
            ctx.strokeRect(x, y, obj.width, obj.height);

            // Label the object type
            ctx.font = "20px sans-serif";
            ctx.fillStyle = "#00bfff";
            ctx.fillText(obj.object_type || "Unknown", x + 5, y - 10);
        }
    }
}
