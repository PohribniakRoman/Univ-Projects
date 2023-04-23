import express from "express";
import fs from "fs";
import cors from "cors";
import path from "path";
import * as url from 'url';

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



// app.post("/newAttendee",(req,res)=>{
//     const {data} = req.body;
//     console.log(data);
// })

app.get("/events",(req,res)=>{
  loadAttendee();
  loadEvents();
  res.send({events:Events})
})

app.listen(PORT,()=>{
    console.log(`Server has been started on port:${PORT}`);
})


