import QtQuick 2.15

Canvas {
    property var detectedObjects: instrumentCluster.detectedObjects

    onDetectedObjectsChanged: {
        requestPaint();
    }

    function drawObjects(objects) {
        var ctx = getContext("2d");

        objects.forEach(function(obj) {
            ctx.beginPath();
            ctx.rect(obj.x, obj.y, obj.width, obj.height);

    
            switch (obj.type) { // no futuro serao imagens!! 
                case "car":
                    ctx.strokeStyle = "#7c7c7c"; 
                    break;
                case "pedestrian":
                    ctx.strokeStyle = "#7c7c7c";
                    break;
                case "traffic_light":
                    ctx.strokeStyle = "#7c7c7c";
                    break;
                ctx.strokeStyle = "#7c7c7c";
                break;
                default:
                    ctx.strokeStyle = "#7c7c7c"; 
                    break;
            }
            

            // image.onload = function() {
            //     ctx.drawImage(image, obj.x, obj.y, obj.width, obj.height);
            // };

            ctx.lineWidth = 2;
            ctx.stroke();

            ctx.font = "14px sans-serif";
            ctx.fillStyle = ctx.strokeStyle;
            ctx.fillText(obj.type, obj.x + 5, obj.y - 5);
        });
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height); // limpa o canvas

        if (detectedObjects && detectedObjects.length > 0) {
            drawObjects(detectedObjects);   
        }
    }
}

// Repeater {
//     model: instrumentCluster.detectedObjects

//     Image {
//         source: {
//             switch (modelData.type) {
//                 // case "car": return "images/car.png";
//                 // case "pedestrian": return "images/pedestrian.png";
//                 case "traffic_light": return  "../assets/images/car.png";
//                 default: return "";
//             }
//         }
//         x: modelData.x
//         y: modelData.y
//         width: modelData.width
//         height: modelData.height
//     }
// }
