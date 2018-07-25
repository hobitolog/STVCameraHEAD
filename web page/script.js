


direction = "";

function moveLeft() {
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    direction = "&L1=L";
    request.open("GET", "ajax_inputs" + direction + nocache, true);
    request.send(null);
}
function moveRight() {
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    direction = "&L1=R";
    request.open("GET", "ajax_inputs" + direction + nocache, true);
    request.send(null);
}
function moveClockwise() {
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    direction = "&L1=C";
    request.open("GET", "ajax_inputs" + direction + nocache, true);
    request.send(null);
}
function moveCounterClockwise() {
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    direction = "&L1=A";
    request.open("GET", "ajax_inputs" + direction + nocache, true);
    request.send(null);
}