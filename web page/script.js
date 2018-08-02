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
}