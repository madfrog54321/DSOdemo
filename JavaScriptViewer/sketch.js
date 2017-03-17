var x = 0, y = 0, z=0;
var socket;
var shutdown = false;
var points = [];
var rotX= 0, rotXold = 0;
var rotY= 0, rotYold = 0;
var rotZ= 0, rotZold = 0;
var mouseDownX = 0, mouseDownY = 0;

function setup() {
  createCanvas(700, 700, WEBGL);
}

function mousePressed() {
  rotXold = rotX;
  rotYold = rotY;
  rotZold = rotZ;
  mouseDownX = mouseX;
  mouseDownY = mouseY;
}

function mouseDragged(){
  rotY = (mouseX- mouseDownX) * 0.01 + rotYold;
  rotX = (mouseY- mouseDownY) * 0.01 + rotXold;
}

function draw() {
  //translate(250, 250);
  background(220);
  //noFill();
  
  rotateX(rotX);
  rotateY(rotY);
  rotateZ(rotZ);
  
  fill(255, 0, 0, 50);
  plane(200, 200);
  fill(0, 255, 0, 50);
  rotateY(PI/2);
  plane(200, 200);
  rotateY(-PI/2);
  fill(0, 0, 255, 50);
  rotateX(PI/2);
  plane(200, 200);
  rotateX(-PI/2);
  
  normalMaterial();
  
  beginShape();
  stroke(200);
  strokeWeight(10);
  var delta = 1 + floor(points.length / 100);
  for(var i = 0; i < points.length; i+=delta){
    translate(points[i][0], points[i][1], points[i][2]);
    sphere(2);
    translate(-points[i][0], -points[i][1], -points[i][2]);
  }
  
  endShape();
  strokeWeight(1);
  
  
  //fill(100);
  stroke(200, 0, 0);
  translate(x, y, z) 
  box(20, 20, 20);
  translate(-x, -y, z) 
}

var connectToController = function(){
  if(!shutdown){
    socket = new WebSocket("ws://localhost:9090");

    socket.onopen = function(event){
      
    };

    socket.onclose = function(event){
      socket = null;
      if(!shutdown)
        setTimeout(connectToController, 2000);
    };

    socket.onmessage = function(event) {
      console.log("Received Message: " + event.data)
      var values = event.data.split(",");
      x = values[0]* 100;
      y = values[1] * 100;
      z = values[2] * 100;
      points.push([x, y, z]);
    };
  }
};
  
connectToController();