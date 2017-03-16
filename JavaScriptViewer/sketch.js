var x = 0, y = 0;
var socket;
var shutdown = false;

function setup() {
  createCanvas(500, 500);
}

function draw() {
  background(0);
  noFill();
  
  stroke(255);
  rect(x, y, 10, 10);
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
      x = values[0];
      y = values[1];
    };
  }
};
  
connectToController();