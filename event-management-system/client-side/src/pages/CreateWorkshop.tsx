import { Button, TextField, Typography } from "@mui/material";
import { NavBar } from "../components/NavBar";
import {useState} from "react";
import { useSelector } from "react-redux";
import { useNavigate } from "react-router-dom";

export const CreateWorkshop = () =>{
    const [title,setTitle] = useState<string>("");
    const [description,setDescription] = useState<string>("");
    const [orator,setOrator] = useState<string>("");
    const [theme,setTheme] = useState<string>("");
    const [time,setTime] = useState<any>();
    const user = useSelector((state:any)=>state.user);
    const navigate = useNavigate();
    return <>
    <NavBar/>
    <section className="auth">
            <form className="auth__wrapper" onSubmit={(e)=>{
                e.preventDefault();
                if(new Date().getTime()<=time && orator.trim() && theme.trim() && !title.includes("|") && !description.includes("|") && !title.includes(":") && title.trim() && description.trim() && !description.includes(":")){
                const fetchData = {
                    title,
                    description,
                    date:time,
                    author:user.id,
                    orator,
                    theme
                }
                fetch("http://localhost:5000/createWorkshop",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify({data:fetchData})})
                setTimeout(()=>{
                    navigate("/workshops");
                    location.reload();
                },3000)
                }else{
                    alert("Wrong input data")
                }
            }}>
                <Typography variant="h5">Create Event</Typography>
                <div className="auth__input-container">
                <TextField label="Title" value={title} onChange={(e)=>{setTitle(e.target.value)}} variant="standard" required />
                </div>
                <div className="auth__input-container">
                <TextField label="Description" value={description} onChange={(e)=>{setDescription(e.target.value)}} variant="standard" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Orator" value={orator} onChange={(e)=>{setOrator(e.target.value)}} variant="standard" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Theme" value={theme} onChange={(e)=>{setTheme(e.target.value)}} variant="standard" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Start Date" onChange={(e)=>{setTime(new Date(e.target.value).getTime())}} variant="standard" type="date" required/>
                </div>
                <Button className="auth__submit" type="submit">Create</Button>
            </form>
    </section>
    </>
}