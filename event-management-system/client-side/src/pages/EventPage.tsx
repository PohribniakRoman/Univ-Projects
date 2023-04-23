import { useEffect, useState } from "react";
import { Typography } from "@mui/material";
import {useParams} from "react-router-dom";

export const EventPage:React.FC = () =>{
    const {id} = useParams();

    const [event,setEvent] = useState<any>({});

    useEffect(()=>{
        (async ()=>{
           const {events} = await (await fetch("http://localhost:5000/events")).json();
           console.log(events);
           setEvent(events.filter((event:any)=>event.id === id)[0]);
        })();
    },[])


    if(!event.hasOwnProperty("title")){
        return <Typography variant="h3">Loading...</Typography>;
    }
    return <section className="event-page">
        {event.attendees.map((e:any)=>{
            return e.name;
        })}
    </section>
}