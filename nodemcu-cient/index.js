
const express = require("express");

const app =express();

const port =4000;

app.get('/',function(req,res){
    res.sendFile(__dirname+"/index.html");
});

const server = app.listen(port,function(){
   console.log("server is running at port ="+port);
});

const SocketServer= require('ws').Server;

const wss = new SocketServer({server});
var data=0;
wss.on('connection',function(ws){
    ws.send(data.toString());
    console.log("client connected");
    ws.on('message',function(msg){
        data=msg.toString();
        console.log(data);
        Broadcast(data);
    });
    ws.on('close',function(){
        console.log("client disconnected");
    });
});

function Broadcast(msg){
    wss.clients.forEach(function(client){
        if(client.readyState==client.OPEN){
            client.send(msg);
        }
    });
}