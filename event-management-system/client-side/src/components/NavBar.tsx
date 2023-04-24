import { Button, Typography } from "@mui/material";
import { Link, useLocation } from "react-router-dom";
import {useState} from "react";
import {RxEnter} from "react-icons/rx"
export const NavBar = () =>{
    const [isLogined,setLogined] = useState(false);
    const location = useLocation();
    
    return <div className="navbar">
        <div className="navbar__wrapper">
            <ul className="navbar__menu">
                <Link to="/" className={`navbar__menu--item ${location.pathname === "/"?"active":""}`}>
                <Typography>Events</Typography>
                </Link>
            </ul>
            {isLogined?
        <div className="navbar__avatar"></div>:
        <Link to="/auth">
        <Button className="navbar__btn">Log in <RxEnter/></Button>
        </Link>}
        </div> 
    </div>
}