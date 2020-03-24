var host = 'ws://' + window.location.hostname + ':81';

var socket = new WebSocket(host);

// Lorsque la connexion est établie.
socket.onopen = function(event) {
    if (event.currentTarget.readyState == 1) {
        console.log("Connexion établie.");
    }
};

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