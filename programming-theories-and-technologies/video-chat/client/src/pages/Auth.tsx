import {useRef,useState} from "react";
import {TextField,Button,Typography} from '@mui/material';
import { centerContainer } from "../components/Loading";
import { ENDPOINTS } from "../services/ENDPOINTS";
import Cookies from 'universal-cookie';
import { useNavigate } from "react-router-dom";
const cookies = new Cookies();

const formStyle = {
    display:"flex",
    alignItems:"center",
    justifyContent:"center",
    flexDirection:"column",
    gap:"25px",
} as React.CSSProperties

const changeBtn = {
    cursor:"pointer",
    fontSize:"12px",
} as React.CSSProperties

const insertData = (event:React.FormEvent<HTMLDivElement>,ref:React.MutableRefObject<Record<string,HTMLInputElement>>) => {
    const element = event.target as HTMLInputElement;
    ref.current[element.name]=element;
}

export const Auth:React.FC = () => {
    const data = useRef<Record<string,HTMLInputElement>>({})
    const [authState,setAuthState] = useState<boolean>(true)
    const navigate = useNavigate();

    return <section style={centerContainer}>
        {authState?
        <form style={formStyle} onSubmit={(event)=>{
            event.preventDefault();
            const parsedData:Record<string,string> = {};
            for(let value in data.current)parsedData[value] = data.current[value].value;
            fetch(ENDPOINTS.host+ENDPOINTS.register,{...ENDPOINTS.params,body:JSON.stringify(parsedData)}).then((rawRes)=>rawRes.json().then(res=>{
                if(res.success){
                    cookies.set("token",res.token,{path: "/", maxAge: 60 * 60 * 24 * 7})
                    navigate("/home");
                }
            }))
            for(let value in data.current)data.current[value].value = "";
        }}>
            <Typography variant="h3">Registration</Typography>
            <TextField onInput={(event)=>insertData(event,data)} required name="email" label="Email" type="email" variant="standard" />
            <TextField onInput={(event)=>insertData(event,data)} required name="login" label="login" variant="standard" />
            <TextField onInput={(event)=>insertData(event,data)} required name="password" label="Password" type="password" variant="standard" />
            <Button type="submit" variant="contained">Sing Up</Button>
            <Typography style={changeBtn} onClick={()=>setAuthState(!authState)}>Swap to login!</Typography>
        </form>
        
        :
        
        <form style={formStyle} onSubmit={(event)=>{
            event.preventDefault();
            const parsedData:Record<string,string> = {};
            for(let value in data.current)parsedData[value] = data.current[value].value;
            fetch(ENDPOINTS.host+ENDPOINTS.login,{...ENDPOINTS.params,body:JSON.stringify(parsedData)}).then((rawRes)=>rawRes.json().then(res=>{
                if(res.success){
                    cookies.set("token",res.token,{path: "/", maxAge: 60 * 60 * 24 * 7})
                    navigate("/home");
                }    
            }))
            for(let value in data.current)data.current[value].value = "";
        }}>
            <Typography variant="h3">Login</Typography>
            <TextField onInput={(event)=>insertData(event,data)} required name="login" label="login" variant="standard" />
            <TextField onInput={(event)=>insertData(event,data)} required name="password" label="Password" type="password" variant="standard" />
            <Button type="submit" variant="contained">Sing Up</Button>
            <Typography style={changeBtn} onClick={()=>setAuthState(!authState)}>Swap to registration!</Typography>
        </form>
        }

    </section>
}