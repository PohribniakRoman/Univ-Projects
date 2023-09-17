const express = require("express");
const cors = require("cors");
const { v4, version, validate } = require("uuid");
const http = require("http");
const { Server } = require("socket.io");
const { error } = require("console");

const PORT = process.env.PORT || 5000;

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.post("/register", (req, res) => {
  const { email, login, password } = req.body;
  const token = v4();
  res.send({ success: true, token: token });
});

app.post("/login", (req, res) => {
  const { login, password } = req.body;
  const token = v4();
  res.send({ success: true, token: token });
});

const shareRooms = () => {
  const rawRooms = io.of("/").adapter.rooms.keys();  
  const rooms = Array.from(rawRooms).filter(roomId=>validate(roomId) && version(roomId) === 4);  
  io.emit("SHARE__ROOMS",rooms)
}

io.on("connection", (socket) => {
  socket.on("JOIN__ROOM",({roomId})=>{
    const rawRooms = socket.adapter.rooms.keys();  
    const rooms = Array.from(rawRooms).filter(roomId=>validate(roomId) && version(roomId) === 4);  
    if(rooms.includes(roomId)){
      console.log("Already in room!");
      console.log(rooms);
    }else{
      socket.join(roomId);
      shareRooms();
    }
  })
});

app.post("/isAuth", (req, res) => {
  const { token } = req.body;

  res.send({ authorized: true });
});

server.listen(PORT, () => {
  console.log(`Server has been started on port:${PORT}`);
});
