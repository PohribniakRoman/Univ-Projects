import {v4} from "uuid";
import {useState,useEffect} from "react";
import { useNavigate } from "react-router-dom"
import { socket } from "../services/websocket";

export const Home:React.FC = () => {
    const navigate = useNavigate();
    const [rooms,setRooms] = useState<string[]>([]);
    useEffect(()=>{
        socket.on("SHARE__ROOMS",(rooms)=>{
            setRooms([...rooms]);
        })
    })
    return <section>
        {rooms.map(room=>{
            return <li onClick={()=>navigate(`/room/${rooms}`)}>{room}</li>
        })}
        <button onClick={()=>navigate(`/room/${v4()}`)}>Create Room</button>
    </section>
}