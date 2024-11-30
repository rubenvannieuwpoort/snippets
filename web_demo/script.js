const width = 320;
const height = 240;
const fps = 30;


const screenBuffer = new Uint8ClampedArray(width * height);

const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');

const imageData = context.getImageData(0, 0, width, height);


const pallette = new Array(256);
for (var i = 0; i < 256; i++) {
    pallette[i] = [i, i, i];
}

function blitToScreen() {
  for (let i = 0; i < screenBuffer.length; i++) {
    const color = pallette[screenBuffer[i]];
    imageData.data[i * 4] = color[0];
    imageData.data[i * 4 + 1] = color[1];
    imageData.data[i * 4 + 2] = color[2];
    imageData.data[i * 4 + 3] = 255;
  }
  context.putImageData(imageData, 0, 0);
}


var t = 0;
function update() {
    var i = 0;
    for (var y = 0; y < height; y++) {
        for (var x = 0; x < width; x++) {
            screenBuffer[i++] = ((x + t) & 255) ^ (y & 255);
        }
    }
    t++;
    blitToScreen();
}

setInterval(update, 33);