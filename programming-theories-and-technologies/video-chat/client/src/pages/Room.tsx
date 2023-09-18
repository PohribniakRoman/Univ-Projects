import { useParams } from "react-router-dom"
import { useEffect, useRef, useState } from "react";
import { Button, TextField, Typography } from "@mui/material";
import { ENDPOINTS } from "../services/ENDPOINTS";
import { Loading } from "../components/Loading";
import Cookies  from "universal-cookie";
import { Navabar } from "../components/Navbar";
import {FaTelegramPlane} from "react-icons/fa";
import socket from "../services/websocket";
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
    return <section className="page">
        <Navabar user={user}/>
        <Typography className="chat__id">Room ID: {params.id}</Typography>
        <ul className="chat">
            {chat.map((msg,id)=>{
                return <li className={`chat__msg ${msg.userName===user.login?"my":""}`} key={id}>
                    <Typography className="chat__msg--sender">{msg.userName}</Typography>
                    <Typography className="chat__msg--text">{msg.text}</Typography>
                    <Typography className="chat__msg--time">{new Date(msg.date).toLocaleTimeString()}</Typography>
                </li>
            })}
        </ul>
        <form className="chat__form" onSubmit={(event)=>{
            event.preventDefault();
            if(text.current){
                socket.emit("SEND__MESSAGE",({roomId:params.id,text:text.current.value,date:new Date().getTime(),userName:user.login}))
                text.current.value = "";
            }
        }}>
            <TextField name="text" className="chat__form--text" onChange={(event)=>text.current = event.target as HTMLInputElement}/>
            <Button type="submit" variant="contained" className="chat__form--btn"><FaTelegramPlane/></Button>
        </form>
    </section>
}