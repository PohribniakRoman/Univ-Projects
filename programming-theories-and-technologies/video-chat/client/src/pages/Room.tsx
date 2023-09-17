import { useParams } from "react-router-dom"
import { socket } from "../services/websocket";
import { useEffect, useState } from "react";
import { Button } from "@mui/material";

interface Message{
    userId:string;
    text:string;
    date:number;
    userName:string;
}

export const Room:React.FC = () => {
    const params  = useParams();
    const [chat,setChat] = useState<Message[]>([]); 
   
    useEffect(()=>{
        socket.emit("JOIN__ROOM",{roomId:params.id})
        socket.on("HISTORY",(history)=>{
            setChat([...history])
        })
        
        socket.on("MESSAGE",(msg)=>{
            setChat(prev=>[...prev,msg]);
        })

        return ()=>{
            socket.emit("LEAVE__ROOM")
        }
    },[])
    return <section>
        <ul>
            {chat.map(msg=>{
                return <li>{msg.text}</li>
            })}
        </ul>
        <form onSubmit={()=>{
            socket.emit("SEND__MESSAGE",({roomId:params.id,text:"asd"}))
        }}>
            <Button type="submit">send</Button>
        </form>
    </section>
}