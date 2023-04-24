import { useEffect, useState } from "react";
import { Button, Chip, Typography } from "@mui/material";
import {useParams} from "react-router-dom";
import { NavBar } from "../components/NavBar";
import { useSelector } from "react-redux";

export const EventPage:React.FC = () =>{
    const {id} = useParams();

    const [event,setEvent] = useState<any>({});
    const [isUserIn,setIsIn] = useState<boolean>(false);

    useEffect(()=>{
        (async ()=>{
           const {events} = await (await fetch("http://localhost:5000/events")).json();
           console.log(events);
           if(events.filter((event:any)=>event.id === id).length>0)setEvent(events.filter((event:any)=>event.id === id)[0]);
        })();
    },[])
    const user = useSelector((state:any)=>state.user);

    if(!event.hasOwnProperty("title")){
        return <Typography variant="h3">Loading...</Typography>;
    }
    return<>
        <NavBar/>
        <section className="event-page">
            <Typography className="event-page__header" variant="h3">{event.title}</Typography>
            <Typography className="event-page__subheader" variant="h5">Author:</Typography>
            <Typography className="event-page__description" style={{textTransform:"capitalize"}}>{event.author.name+" "+event.author.surname}</Typography>
            <Typography className="event-page__subheader" variant="h5">Description:</Typography>
            <Typography className="event-page__description">{event.description}</Typography>
            <Typography className="event-page__subheader" variant="h5">Attendees:</Typography>
            <div className="event-page__container">
            {event.attendees.map((e:any)=>{
                if(e.name === user.name && e.surname === user.surname && !isUserIn){setIsIn(true)}
                return <Chip label={e.name+" "+e.surname} className="event-page__container-item" variant="outlined" />;
            })}
            </div>
            {user.isAuthorized?<>{!isUserIn?<Button className="event-page__submit" onClick={()=>{
                fetch("http://localhost:5000/joinEvent",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify({data:{id:user.id,eventId:event.id}})})
                setTimeout(()=>{
                    location.reload();
                },3000)
            }}>Attend</Button>:
            <Button className="event-page__submit" id="leave" onClick={()=>{
                fetch("http://localhost:5000/leaveEvent",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify({data:{id:user.id,eventId:event.id}})})
                setTimeout(()=>{
                    location.reload();
                },3000)
            }}>leave</Button>}</>:""}
        </section>
    </>
}