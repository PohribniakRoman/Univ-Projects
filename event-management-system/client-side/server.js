import express from "express";
import fs from "fs";
import cors from "cors";
import path from "path";
import * as url from 'url';
import { v4 } from "uuid";

const PORT = process.env.PORT || 5000;
const allowedOrigins = ['http://localhost:5173'];

const __dirname = url.fileURLToPath(new URL('.', import.meta.url))

const options = {               
  origin: allowedOrigins
};

const app = express();

app.use(cors(options)); 
app.use(express.json());


const loadAttendee = () =>{
  Attendee=[];
  const data = fs.readFileSync(path.resolve(__dirname+"Attendee.txt"),{encoding:"utf-8"});
  data.split("\n").forEach((el,ind)=>{
    if(ind !== 0 && el){
      const newAt = {};
      el.split("|").forEach((entry,i)=>{
        switch(i){
          case 0:newAt.name = entry;break;
          case 1:newAt.surname = entry;break;
          case 2:newAt.mail = entry;break;
          case 3:newAt.phone = entry;break;
          case 4:newAt.age = parseInt(entry);break;
          case 5:newAt.date = parseInt(entry);break;
          case 6:newAt.id = entry.split("\r")[0];break;
        }
      });
      Attendee.push(newAt);
    }
  })
}
const loadEvents = () =>{
  Events=[];
  const data = fs.readFileSync(path.resolve(__dirname+"Event.txt"),{encoding:"utf-8"});
  data.split("\n").forEach((el,ind)=>{
    if(ind !== 0 && el){
      const newEv = {};
      el.split("|").forEach((entry,i)=>{
        switch(i){
          case 0:newEv.title = entry;break;
          case 1:newEv.description = entry;
          case 2:newEv.author = Attendee.filter(attendee=>attendee.id === entry)[0];break;
          case 3:newEv.dateOfBirth = parseInt(entry);break;
          case 4:newEv.dateOfStart = parseInt(entry);break;
          case 5:newEv.id = entry;break;
          case 6:{
            const attendees = [];
            entry.split(":").forEach(att=>{
              Attendee.forEach(store=>{
                if(store.id === att){attendees.push(store)}
              })
            })
            newEv.attendees = attendees;
          }
        }
      });
      Events.push(newEv);
    }
  })
};

let Attendee = [];
loadAttendee()
let Events = [];
loadEvents()

const sendCommand = (rawData) => {
  fs.writeFileSync("CommandBus.txt",rawData);
}

app.post("/isExist",(req,res)=>{
    const {id} = req.body;
    const response = {exsit:false};
    Attendee.forEach(e=>{
      if(e.id === id){
       response.exsit = true;
       response.data = e;
      }
    })
    res.send(response)
})

app.post("/leaveEvent",(req,res)=>{
    const {data} = req.body;
    const rawData = `LEAVE_EVENT/${data.id}|${data.eventId}`
    sendCommand(rawData)
})
app.post("/joinEvent",(req,res)=>{
    const {data} = req.body;
    const rawData = `JOIN_EVENT/${data.id}|${data.eventId}`
    sendCommand(rawData)
})

app.post("/createAttendee",(req,res)=>{
    const rawData = `ADD_ATTENDEE/${req.body.name}|${req.body.surname}|${req.body.mail}|${req.body.phone}|${req.body.age}|${new Date().getTime()}|${req.body.id}`
    sendCommand(rawData)
})

app.post("/createEvent",(req,res)=>{
    const {data} = req.body;
    const rawData = `ADD_EVENT/${data.title}|${data.description}|${data.author}|${new Date().getTime()}|${data.date}|${v4()}|`
    sendCommand(rawData)
})

app.post("/login",(req,res)=>{
  const {name,surname} = req.body;
  const response = {exsit:false};
  Attendee.forEach(e=>{
    if(e.name === name && e.surname === surname){
     response.exsit = true;
     response.id = e.id;
    }
  })
  res.send(response)
})
app.post("/deleteEvent",(req,res)=>{
  const {data} = req.body;
  const rawData = `REMOVE_EVENT/${data.id}`
  sendCommand(rawData)
})

app.post("/deleteAttendee",(req,res)=>{
  const {data} = req.body;
  const rawData = `REMOVE_ATTENDEE/${data.id}`
  sendCommand(rawData)
})

app.get("/events",(req,res)=>{
  loadAttendee();
  loadEvents();
  res.send({events:Events})
})

app.listen(PORT,()=>{
    console.log(`Server has been started on port:${PORT}`);
})


