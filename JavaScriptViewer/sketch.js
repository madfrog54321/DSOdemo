var x = 0, y = 0, z=0;
var socket;
var shutdown = false;
var points = [];
var rotX= 0;

function setup() {
  createCanvas(500, 500, WEBGL);
}

function draw() {
  //translate(250, 250);
  background(200);
  //noFill();
  
  rotX += 0.01;
  rotateX(rotX);
  rotateY(rotX);
  
  beginShape();
  stroke(200);
  strokeWeight(10);
  for(var i = 0; i < points.length; i++){
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