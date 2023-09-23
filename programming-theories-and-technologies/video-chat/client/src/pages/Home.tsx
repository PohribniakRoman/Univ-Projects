import {v4} from "uuid";
import {useState,useEffect, useRef} from "react";
import { useNavigate } from "react-router-dom"
import { ENDPOINTS } from "../services/ENDPOINTS";
import { Loading } from "../components/Loading";
import { Navabar } from "../components/Navbar";
import socket from "../services/websocket";
import { Button, Typography } from "@mui/material";
import { ACTIONS } from "../services/actions";
import Cookies from "universal-cookie";
const cookies = new Cookies();

export const Home:React.FC = () => {
    const navigate = useNavigate();
    const [rooms,setRooms] = useState<string[]>([]);
    const [user,setUser] = useState<any>({})
    const rootNode = useRef<any>();

    useEffect(() => {
        socket.on(ACTIONS.SHARE_ROOMS, ({rooms = []} = {}) => {
          if (rootNode.current) {
            setRooms(rooms);
          }
        });
      }, []);
    
    useEffect(()=>{
        (async ()=>{
            const {user} = await (await fetch(ENDPOINTS.host+ENDPOINTS.getData,{...ENDPOINTS.params,body:JSON.stringify({token:cookies.get("token")})})).json()
            setUser(user);
        })()  
    },[])


    if(!user.login)return <Loading/>

    return <section className="page" ref={rootNode}>
        <Navabar user={user}/>
        <ul className="rooms">
        {rooms.map(room=>{
            return <li key={room} className="rooms__item">
                <Typography className="rooms__item--name">Room ID:{room}</Typography>
                <Button className="rooms__item--btn" variant="contained" onClick={()=>navigate(`/room/${rooms}`)}>Join</Button>    
            </li>
        })}
        </ul>
        <Button onClick={()=>navigate(`/room/${v4()}`)}>Create Room</Button>
    </section>
}