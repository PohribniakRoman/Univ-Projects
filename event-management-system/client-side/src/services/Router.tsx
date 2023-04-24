import { BrowserRouter,Route,Routes } from "react-router-dom"
import { Events } from "../pages/Events"
import { EventPage } from "../pages/EventPage"
import { Auth } from "../pages/Auth"
import { CreateEvent } from "../pages/CreateEvent"
import { validate } from "uuid";
import {useEffect} from "react";
import { useDispatch } from "react-redux"

export const Router:React.FC = () => {
    const dispatch = useDispatch();
    useEffect(()=>{
        const id = localStorage.getItem("id");
        if(id !== null && validate(id)){
            fetch("http://localhost:5000/isExist",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify({id})}).then(data=>data.json().then(({exsit,data}:any)=>{
                console.log(exsit);
                if(exsit){
                    let newState = {...data};
                    newState.isAuthorized = exsit;
                    dispatch({type:"LOAD_ATTENDEE",payload:newState})
                }
        }))
        }
    },[])
    return <BrowserRouter>
        <Routes>
            <Route path="/" element={<Events/>}/>
            <Route path="/event/:id" element={<EventPage/>} />
            <Route path="/auth" element={<Auth/>} />
            <Route path="/create-event" element={<CreateEvent/>} />
        </Routes>
    </BrowserRouter>
}