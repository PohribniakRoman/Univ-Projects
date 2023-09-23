const express = require("express");
const cors = require("cors");
const { v4, version, validate } = require("uuid");
const http = require("http");
const { Server } = require("socket.io");
const mongoose = require("mongoose");
const bcrypt = require('bcrypt');
const saltRounds = 10;
const app = express();

const ACTIONS = require('./actions');
const PORT = process.env.PORT || 5000;

const server = http.createServer(app);
const io = new Server(server);

const userScheme = new mongoose.Schema({login: String, password: String,email:String});
const User = mongoose.model("User", userScheme);
const tokenScheme = new mongoose.Schema({token: String});
const Token = mongoose.model("Token", tokenScheme);


app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.post("/register", async (req, res) => {
  const { email, login, password } = req.body;
  const hash = bcrypt.hashSync(password, saltRounds);
  const rawToken = v4();
  const candidate = await User.findOne({login});
  if(!candidate){
    const user = new User({login,password:hash,email});
    const token = new Token ({token:rawToken,_id:user._id});
    await user.save();
    await token.save();
    res.send({ success: true, token: rawToken });
  }else{
    res.send({success:false})
  }
});

app.post("/login", async (req, res) => {
  const { login, password } = req.body;
  const candidate = await User.findOne({login});
  if(candidate && bcrypt.compareSync(password,candidate.password)){
    const rawToken = v4();
    await Token.findByIdAndDelete(candidate._id);
    const token = new Token ({token:rawToken,_id:candidate._id});
    await token.save();
    res.send({ success: true, token: rawToken });
  }else{
    res.send({ success: false });
  }
});

app.post("/getData", async (req,res)=>{
  const {token} = req.body;
  const {_id} = await Token.findOne({token});
  const user = await User.findById(_id);
  res.send({user:{
    login:user.login,
    email:user.email
  }});
})


app.post("/isAuth", async (req, res) => {
  const { token } = req.body;
  const candidate = await Token.findOne({token});
  res.send({ authorized: candidate?true:false });
});

function getClientRooms() {
  const {rooms} = io.sockets.adapter;

  return Array.from(rooms.keys()).filter(roomID => validate(roomID) && version(roomID) === 4);
}

function shareRoomsInfo() {
  io.emit(ACTIONS.SHARE_ROOMS, {
    rooms: getClientRooms()
  })
}

io.on('connection', socket => {
  shareRoomsInfo();

  socket.on(ACTIONS.JOIN, config => {
    const {room: roomID} = config;
    const {rooms: joinedRooms} = socket;

    if (Array.from(joinedRooms).includes(roomID)) {
      return console.warn(`Already joined to ${roomID}`);
    }

    const clients = Array.from(io.sockets.adapter.rooms.get(roomID) || []);

    clients.forEach(clientID => {
      io.to(clientID).emit(ACTIONS.ADD_PEER, {
        peerID: socket.id,
        createOffer: false
      });

      socket.emit(ACTIONS.ADD_PEER, {
        peerID: clientID,
        createOffer: true,
      });
    });

    socket.join(roomID);
    shareRoomsInfo();
  });

  function leaveRoom() {
    const {rooms} = socket;

    Array.from(rooms)
      // LEAVE ONLY CLIENT CREATED ROOM
      .filter(roomID => validate(roomID) && version(roomID) === 4)
      .forEach(roomID => {

        const clients = Array.from(io.sockets.adapter.rooms.get(roomID) || []);

        clients
          .forEach(clientID => {
          io.to(clientID).emit(ACTIONS.REMOVE_PEER, {
            peerID: socket.id,
          });

          socket.emit(ACTIONS.REMOVE_PEER, {
            peerID: clientID,
          });
        });

        socket.leave(roomID);
      });

    shareRoomsInfo();
  }

  socket.on(ACTIONS.LEAVE, leaveRoom);
  socket.on('disconnecting', leaveRoom);

  socket.on(ACTIONS.RELAY_SDP, ({peerID, sessionDescription}) => {
    io.to(peerID).emit(ACTIONS.SESSION_DESCRIPTION, {
      peerID: socket.id,
      sessionDescription,
    });
  });

  socket.on(ACTIONS.RELAY_ICE, ({peerID, iceCandidate}) => {
    io.to(peerID).emit(ACTIONS.ICE_CANDIDATE, {
      peerID: socket.id,
      iceCandidate,
    });
  });

});



  server.listen(PORT, async () => {
  await mongoose.connect("mongodb+srv://romanpohribniak:qweasdzxc123@cluster0.4ou7epu.mongodb.net/");
  console.log(`Server has been started on port:${PORT}`);
});
