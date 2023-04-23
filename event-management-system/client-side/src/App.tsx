import { useEffect } from "react"
import { Router } from "./services/Router"

export const App:React.FC = () => {
    useEffect(()=>{
        fetch("http://localhost:5000/newAttendee",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify({data:"ne ny a sho"})})
    },[])
    return(<Router/>)
}