import { useParams } from "react-router-dom"
import { socket } from "../services/websocket";
import { useEffect } from "react";

export const Room:React.FC = () => {
    const params  = useParams();
    socket;
    useEffect(()=>{

    },[])
    return <section>
        {params.id}
    </section>
}