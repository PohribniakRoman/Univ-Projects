import { useParams } from "react-router-dom"
import { socket } from "../services/websocket";
import { useEffect, useState } from "react";

interface Message{
    userId:string;
    content:string;
    date:number;
    userName:string;
}

export const Room:React.FC = () => {
    const params  = useParams();
    const [chat,setChat] = useState<Message[]>([]); 
   
    useEffect(()=>{
        socket.emit("JOIN__ROOM",{roomId:params.id})
        socket.on("HISTORY",(history)=>{

        })
        socket.on("MESSAGE",(msg)=>{

        })
        return ()=>{
            socket.emit("LEAVE__ROOM")
        }
    },[])
    return <section>
        {params.id}
    </section>
}