import { Button, TextField,Typography } from "@mui/material";
import { NavBar } from "../components/NavBar";
import {useState} from "react";

export const Auth:React.FC = () =>{
    const [isLogin,setLogin] = useState(false);
    return<>
        <NavBar/>
        <section className="auth">
            {!isLogin?
            <form className="auth__wrapper">
                <Typography variant="h5">Registrate</Typography>
                <div className="auth__input-container">
                <TextField label="Name" variant="standard" required />
                </div>
                <div className="auth__input-container">
                <TextField label="Surname" variant="standard" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Email" variant="standard" type="email" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Phone Number" variant="standard" type="tel" required/>
                </div>
                <div className="auth__input-container">
                <TextField label="Age" type="number" variant="standard" required/>
                </div>
                <Button className="auth__submit" type="submit">Enter</Button>
                <Typography className="auth__change" onClick={()=>{setLogin(true)}}>Already have an account?</Typography>
            </form>:
            <form className="auth__wrapper">
                <Typography variant="h5">Login</Typography>
                <div className="auth__input-container">
                <TextField label="Name" variant="standard" required />
                </div>
                <div className="auth__input-container">
                <TextField label="Surname" variant="standard" required/>
                </div>
                <Button className="auth__submit" type="submit">Enter</Button>
                <Typography className="auth__change" onClick={()=>{setLogin(false)}}>Don't have any account?</Typography>
            </form>}
            
        </section>
    </>
}