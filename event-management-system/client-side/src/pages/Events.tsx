import { Typography } from "@mui/material";
import { useState,useEffect } from "react"
import { EventEntry } from "../components/EventEntry";
import { NavBar } from "../components/NavBar";

export const Events:React.FC = () =>{
    const [eventList,setEventList] = useState<Record<string,any>[]>([]);

    useEffect(()=>{
        (async ()=>{
           const {events} = await (await fetch("http://localhost:5000/events")).json();
           setEventList(events);
        })();

    },[])

    if(eventList.length < 1){
        return <Typography variant="h3">Loading...</Typography>;
    }

    return<>
    <NavBar/>
    <section className="events">
        <Typography variant="h3">Events</Typography>
        {eventList.map(event=>{
            return <EventEntry key={event.id} data={event}/>
        })}
    </section>
    </>
}