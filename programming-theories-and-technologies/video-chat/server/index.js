const express = require("express");
const cors = require("cors");
const { v4, version, validate } = require("uuid");
const http = require("http");
const { Server } = require("socket.io");
const mongoose = require("mongoose");
const bcrypt = require('bcrypt');
const saltRounds = 10;

const PORT = process.env.PORT || 5000;

const app = express();
const server = http.createServer(app);
const io = new Server(server);
const chatHistory = {}

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

const shareRooms = () => {
  const rawRooms = io.sockets.adapter.rooms;  
  const rooms = Array.from(rawRooms.keys()).filter(roomId=>validate(roomId) && version(roomId) === 4) || [];  
  io.emit("SHARE__ROOMS",rooms)
}

app.post("/isAuth", async (req, res) => {
  const { token } = req.body;
  const candidate = await Token.findOne({token});
  res.send({ authorized: candidate?true:false });
});

io.on("connection",()=>{
  io.emit("SHARE__ROOMS",[])
})

io.on("connection", (socket) => {
  socket.on("GET_ROOMS",()=>{
    const rawRooms = io.sockets.adapter.rooms;  
    const rooms = Array.from(rawRooms.keys()).filter(roomId=>validate(roomId) && version(roomId) === 4) || [];  
    io.to(socket.id).emit("SHARE__ROOMS",rooms)
  })
  socket.on("JOIN__ROOM",({roomId})=>{
    const {rooms:rawRooms} = socket;  
    const parsedRooms = Array.from(rawRooms.keys()).filter(id=>validate(id) && version(id) === 4);  
    if(!parsedRooms.includes(roomId)){
      if(chatHistory[roomId]){
        chatHistory[roomId].users = Array.from(io.sockets.adapter.rooms.get(roomId) || [])
        io.to(socket.id).emit("HISTORY",chatHistory[roomId].history)
      }else{
        chatHistory[roomId] = {
          history:[],
          users:Array.from(io.sockets.adapter.rooms.get(roomId) || [])
        }
      }
      socket.join(roomId);
      shareRooms();
    }
  })
  
  socket.on("SEND__MESSAGE",({roomId,text,date,userName})=>{
    const msg = {text,date,userName}
    chatHistory[roomId].history.push(msg)
    io.in(roomId).emit("MESSAGE",msg);
  })
  
  socket.on("LEAVE__ROOM",()=>{
      Array.from(socket.rooms).filter(id=>validate(id) && version(id) === 4).forEach(room=>{
        socket.leave(room);
        chatHistory[room].users = Array.from(io.sockets.adapter.rooms.get(room) || [])
      });
    })
  shareRooms();
  });
  
  
  server.listen(PORT, async () => {
  await mongoose.connect("mongodb+srv://romanpohribniak:qweasdzxc123@cluster0.4ou7epu.mongodb.net/");
  console.log(`Server has been started on port:${PORT}`);
});
