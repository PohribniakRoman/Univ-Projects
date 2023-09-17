import {useState,useEffect} from "react"; 
import { Loading } from "./Loading";
import { Auth } from "../pages/Auth";
import { ENDPOINTS } from "../services/ENDPOINTS";
import Cookies from 'universal-cookie';
import { useLocation } from "react-router-dom";
const cookies = new Cookies();

export type PortectedRouter = {
    Component:React.FC
}

export const PortectedRouter:React.FC<PortectedRouter> = ({Component}) =>{
    const location = useLocation();
    
    const [isAuthorized,setAuthorized] = useState<null|boolean>(null);

    useEffect(()=>{
        fetch(ENDPOINTS.host+ENDPOINTS.isAuth,{...ENDPOINTS.params,body:JSON.stringify({token:cookies.get("token")})}).then((rawRes)=>rawRes.json().then(res=>{
            setAuthorized(res.authorized ?? false);
        }))
    },[location.pathname])
    

    if(isAuthorized === null)return <Loading/>
    return <>
    {   isAuthorized ?  
        <Component/> :
        <Auth/>
    }
    </>
}