const express = require("express");
const cors = require("cors");
const { v4 } = require("uuid");
const http = require("http");
const { Server } = require("socket.io");

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

io.on("connection", (socket) => {
  console.log(socket.id);
});

app.post("/isAuth", (req, res) => {
  const { token } = req.body;

  res.send({ authorized: true });
});

server.listen(PORT, () => {
  console.log(`Server has been started on port:${PORT}`);
});
