import {v4} from "uuid";
import {useState,useEffect} from "react";
import { useNavigate } from "react-router-dom"
import { socket } from "../services/websocket";
import Cookies from "universal-cookie";
import { ENDPOINTS } from "../services/ENDPOINTS";
import { Loading } from "../components/Loading";
const cookies = new Cookies();

export const Home:React.FC = () => {
    const navigate = useNavigate();
    const [user,setUser] = useState<any>({})
    const [rooms,setRooms] = useState<string[]>([]);
    useEffect(()=>{
        (async ()=>{
            const {user} = await (await fetch(ENDPOINTS.host+ENDPOINTS.getData,{...ENDPOINTS.params,body:JSON.stringify({token:cookies.get("token")})})).json()
            setUser(user);
        })()  
    },[])
    useEffect(()=>{
        socket.on("SHARE__ROOMS",(rooms)=>{
            setRooms([...rooms]);
        })
    },[])

    if(!user.login)return <Loading/>

    return <section>
        {rooms.map(room=>{
            return <li onClick={()=>navigate(`/room/${rooms}`)}>{room}</li>
        })}
        <button onClick={()=>navigate(`/room/${v4()}`)}>Create Room</button>
        <button onClick={()=>{
            cookies.remove("token");
            navigate(`/auth`);
        }}>Log out</button>
        <div>{user.login}</div>
    </section>
}