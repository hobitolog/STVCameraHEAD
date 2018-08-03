speedU = "";
speedD = "";

angleU = "";
angleD = "";



function SendSpeed(){
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    request.open("GET", "ajax_inputs&L1=" + "U" + speedU + "D" + speedD + "E" + nocache, true);
    request.send(null);
}

function SendAngle(){
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    request.open("GET", "ajax_inputs&L1=" + "U" + angleU + "D" + angleD + "E" + nocache, true);
    request.send(null);
<<<<<<< HEAD
} 

var radius = 100;

var sampleJoystick = {
    mode: 'static',
    position: {
      left: '50%',
      top: '50%'
    },
    size: radius*2,
    color: 'black'
};

var joystick;
var position;
joystick = nipplejs.create(sampleJoystick);
joystick.on('start end', function(evt, data) {
  position = data;
}).on('move', function(evt, data) {
  position = data;
}).on('dir:up plain:up dir:left plain:left dir:down' +
      'plain:down dir:right plain:right',
      function(evt, data) {
  //position=data;
}
     ).on('pressure', function(evt, data) {
  position=data;
});
=======
}


function SendCoord(X,Y){
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    request.open("GET", "ajax_inputs&L1=" + "X" + X + "Y" + Y + "E" + nocache, true);
    request.send(null);
}


>>>>>>> f08b94ff9fe897109bf481ed2dfc6b608733706b
