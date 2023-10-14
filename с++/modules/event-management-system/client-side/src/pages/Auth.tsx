import { Button, TextField,Typography } from "@mui/material";
import { NavBar } from "../components/NavBar";
import {useState} from "react";
import { v4 } from "uuid";
import { useNavigate } from "react-router-dom";

export const Auth:React.FC = () =>{
    const [isLogin,setLogin] = useState(false);
    const [name,setName] = useState("");
    const [surname,setSurname] = useState("");
    const [mail,setMail] = useState("");
    const [age,setAge] = useState("");
    const [phone,setPhone] = useState("");
    const navigate = useNavigate();
    return<>
        <NavBar/>
        <section className="auth">
            {!isLogin?
            <form className="auth__wrapper" onSubmit={(e)=>{
                e.preventDefault()
                if(parseInt(age)>7 && parseInt(age) < 90 && !name.includes("|") && !surname.includes("|") && !name.includes(":") && name.trim() && surname.trim() && !surname.includes(":")){
                    const id = v4();
                    localStorage.setItem("id",id);
                    const storeData = {name,surname,mail,phone,age,id}
                    fetch("http://localhost:5000/createAttendee",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify(storeData)});
                    setTimeout(()=>{
                        navigate("/");
                    },3000)
                }else{
                    alert("Worng input data!!!");
                }
            }}>
                <Typography variant="h5">Registrate</Typography>
                <div className="auth__input-container">
                <TextField label="Name" value={name} onChange={(e)=>setName(e.target.value)} variant="standard" required />
                </div>
                <div className="auth__input-container">
                <TextField label="Surname" value={surname} onChange={(e)=>setSurname(e.target.value)} variant="standard" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Email" value={mail} onChange={(e)=>setMail(e.target.value)} variant="standard" type="email" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Phone Number" value={phone} onChange={(e)=>setPhone(e.target.value)} variant="standard" type="tel" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Age" value={age} onChange={(e)=>setAge(e.target.value)} type="number" variant="standard" required/>
                </div>
                <Button className="auth__submit" type="submit">Enter</Button>
                <Typography className="auth__change" onClick={()=>{setLogin(true)}}>Already have an account?</Typography>
            </form>:
            <form className="auth__wrapper"  onSubmit={(e)=>{
                e.preventDefault()
                if(name.trim() && surname.trim()){
                    fetch("http://localhost:5000/login",{method:"POST",mode:"cors",headers:{"Content-Type":"application/json"},body:JSON.stringify({name,surname})}).then(data=>{
                        data.json().then(resp=>{
                            if(resp.exsit){
                                localStorage.setItem("id",resp.id);
                                navigate("/")
                                location.reload();
                            }else{
                                alert("Wrong input data!")
                            }
                        })
                    });
                }
                
                }}>
                <Typography variant="h5">Login</Typography>
                <div className="auth__input-container">
                <TextField label="Name" value={name} onChange={(e)=>setName(e.target.value)} variant="standard" required />
                </div>
                <div className="auth__input-container">
                <TextField label="Surname" value={surname} onChange={(e)=>setSurname(e.target.value)} variant="standard" required/>
                </div>
                <Button className="auth__submit" type="submit">Enter</Button>
                <Typography className="auth__change" onClick={()=>{setLogin(false)}}>Don't have any account?</Typography>
            </form>}
            
        </section>
    </>
}