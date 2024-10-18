const width = 256;
const height = 256;
const fps = 60;
const delay = 1000 / fps;

const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');
const imageData = new ImageData(width, height);

const tempCanvas = document.createElement('canvas');
tempCanvas.width = width;
tempCanvas.height = height;

const tempContext = tempCanvas.getContext('2d');

context.imageSmoothingEnabled = false;
context.scale(2, 2);

var t = 0;
function update() {
    var i = 0;
    for (var y = 0; y < height; y++) {
        var i = y * width * 4;
        for (var x = 0; x < width; x++) {
            color = ((x + t) & 255) ^ (y & 255);
            imageData.data[i++] = color;
            imageData.data[i++] = color;
            imageData.data[i++] = color;
            imageData.data[i++] = 255;
        }
    }
    t++;

    // Blit to temporary canvas
    tempContext.putImageData(imageData, 0, 0);

    // Draw temporary canvas to real canvas (necessary for scaling)
    context.drawImage(tempCanvas, 0, 0, canvas.width, canvas.height)
}

setInterval(update, delay);
