import {useState,useEffect,useRef} from "react"; 
import { Loading } from "./Loading";
import { Auth } from "../pages/Auth";
import { ENDPOINTS } from "../services/ENDPOINTS";

export type PortectedRouter = {
    Component:React.FC
}

export const PortectedRouter:React.FC<PortectedRouter> = ({Component}) =>{
    const [isAuthorized,setAuthorized] = useState<null|boolean>(null);
    const once = useRef<boolean>(true);

    useEffect(()=>{
        if(once){
            once.current = false;
            fetch(ENDPOINTS.host+ENDPOINTS.isAuth,{...ENDPOINTS.params,body:JSON.stringify({token:"asd"})}).then((rawRes)=>rawRes.json().then(res=>{
                setAuthorized(res.authorized ?? false);
            }))
        }
    },[])
    

    if(isAuthorized === null)return <Loading/>
    return <>
    {   isAuthorized?  
        <Component/>:
        <Auth/>
    }
    </>
}