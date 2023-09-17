import { useParams } from "react-router-dom"
import { socket } from "../services/websocket";
import { useEffect, useRef, useState } from "react";
import { Button, TextField } from "@mui/material";
import { ENDPOINTS } from "../services/ENDPOINTS";
import { Loading } from "../components/Loading";
import Cookies  from "universal-cookie";
const cookies = new Cookies();

interface Message{
    text:string;
    date:number;
    userName:string;
}

export const Room:React.FC = () => {
    const params  = useParams();
    const text = useRef<HTMLInputElement|null>(null)
    const [chat,setChat] = useState<Message[]>([]); 
    const once = useRef<boolean>(true);

    const [user,setUser] = useState<any>({})
    useEffect(()=>{
        (async ()=>{
            const {user} = await (await fetch(ENDPOINTS.host+ENDPOINTS.getData,{...ENDPOINTS.params,body:JSON.stringify({token:cookies.get("token")})})).json()
            setUser(user);
        })()  
    },[])
   

    useEffect(()=>{
        socket.emit("JOIN__ROOM",{roomId:params.id})
        
        socket.on("HISTORY",(history)=>{
            setChat([...history])
        })
        
        if(once.current){
            once.current = false;
            socket.on("MESSAGE",(msg)=>{
                setChat(prev=>[...prev,msg]);
            })
        }
        
        return ()=>{
            socket.emit("LEAVE__ROOM")
        }
    },[])
    
    if(!user.login)return <Loading/>
    return <section>
        <ul>
            {chat.map((msg,id)=>{
                return <li key={id}>{msg.userName}:{msg.text}</li>
            })}
        </ul>
        <form onSubmit={(event)=>{
            event.preventDefault();
            if(text.current){
                socket.emit("SEND__MESSAGE",({roomId:params.id,text:text.current.value,date:new Date().getTime(),userName:user.login}))
                text.current.value = "";
            }
        }}>
            <TextField name="text"  onChange={(event)=>text.current = event.target as HTMLInputElement}/>
            <Button type="submit">send</Button>
        </form>
    </section>
}