var context, width, height;

document.addEventListener('DOMContentLoaded', (event) => {
	initializeCanvas();
	initializeEventHandlers();
})

function initializeCanvas() {
	var canvas = document.getElementById("canvas");
	context = canvas.getContext("2d");
	width = canvas.width;
	height = canvas.height;
}

function initializeEventHandlers() {
	document.getElementById("button").addEventListener("click", (event) => {
		// These examples are based on https://www.w3schools.com/html/html5_canvas.asp
		
		// Draw a line
		context.moveTo(250, 50);
		context.lineTo(450, 100);
		context.stroke();
		
		// Draw a rectangle
		context.beginPath();
		context.rect(0, 0, width, height);
		context.stroke();
		
		// Draw a circle
		context.beginPath();
		context.arc(450, 150, 40, 0, 2 * Math.PI);
		context.stroke();
		
		// Draw some text
		context.font = "30px Arial";
		context.fillText("Hello World!", 10, 300);
		
		// Stroke text
		context.font = "30px Arial";
		context.strokeText("Hello World!", 250, 300);
		
		// Draw a gradient
		var gradient = context.createLinearGradient(0, 0, 200, 0);
		gradient.addColorStop(0, "red");
		gradient.addColorStop(1, "white");
		context.fillStyle = gradient;
		context.fillRect(10, 100, 150, 80);
		
		var radialGradient = context.createRadialGradient(75, 50, 5, 90, 60, 100);
		radialGradient.addColorStop(0, "red");
		radialGradient.addColorStop(1, "white");
		context.fillStyle = radialGradient;
		context.fillRect(10, 10, 150, 80);
		
		// Draw image
		var image = new Image();
		image.src = 'https://www.w3schools.com/tags/img_the_scream.jpg';
		image.onload = () => { context.drawImage(image, 500, 10); }
	});
}
