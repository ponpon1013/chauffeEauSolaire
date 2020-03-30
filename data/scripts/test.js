function getVals(event) {
    // get min an max value
    var vals = rangeList.map(x => (parseInt(x.value)));
    min = Math.min(...vals);
    max = Math.max(...vals);
    document.querySelector(".max").innerHTML = max;
    document.querySelector(".min").innerHTML = min;
}

//initialise oninput listener on every thumb
var rangeList = Array.from(document.querySelectorAll(".doubleThumb"));
rangeList.forEach(x => {
    x.addEventListener('input', getVals, true);
});

var host = 'ws://' + window.location.hostname + ':81';

var socket = new WebSocket(host);

// Lorsque le serveur envoi un message.
socket.onerror = function(event) {
    console.log("Error:", event.data);
};

// Lorsque la connexion se termine.
socket.onclose = function(event) {
    console.log("Connexion terminé.");
};

// Lorsque le serveur envoi un message.
socket.onmessage = function(event) {
    console.log("Message:", event.data);

};

// Lorsque la connexion est établie.
socket.onopen = function(event) {
    if (event.currentTarget.readyState == 1) {
        console.log("Connexion établie.");
    }
};