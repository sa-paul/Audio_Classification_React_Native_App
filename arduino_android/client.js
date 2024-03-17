const net = require('net');
const fs = require('fs');

const PORT = 8080;
const HOST = "172.18.1.77";

const client = new net.Socket();

client.connect(PORT, HOST, function() {
    console.log('Connected to server');

    const audio_file = fs.createWriteStream('received_audio_JS.wav');

    client.on('data', function(data) {
        audio_file.write(data);
    });

    client.on('end', function() {
        console.log('Audio file received successfully');
        audio_file.end();
    });

    client.on('error', function(err) {
        console.error('Error: ' + err);
    });
});

client.on('close', function() {
    console.log('Connection closed');
});
