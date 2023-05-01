import { useEffect, useState } from "react";
import { NavBar } from "../components/NavBar";
import { WorkshopEntry } from "../components/WorkshopEntry";
import { Typography } from "@mui/material";

export const Workshop:React.FC = () =>{
    
    const [eventList,setEventList] = useState<Record<string,any>[]>([]);
    useEffect(()=>{
        (async ()=>{
           const {workshops} = await (await fetch("http://localhost:5000/workshops")).json();
           setEventList(workshops);
        })();

    },[])

    return <>
        <NavBar/>
            <section className="events">
            <Typography variant="h3">Workshops</Typography>
            {eventList.map(e=>{
                return <WorkshopEntry data={e}/>
            })}
        </section>
    </>
}