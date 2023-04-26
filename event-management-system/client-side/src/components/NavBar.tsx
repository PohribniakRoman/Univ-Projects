import { Avatar, Button, Typography } from "@mui/material";
import { Link, useLocation } from "react-router-dom";
import {RxEnter} from "react-icons/rx"
import { useDispatch, useSelector } from "react-redux";
export const NavBar = () =>{
    const location = useLocation();
    const user = useSelector((state:any)=>state.user);
    const dispatch = useDispatch();
    if(!user.name && user.exsit){
        return <Typography>Loading...</Typography>
    }
    return <div className="navbar">
        <div className="navbar__wrapper">
            <ul className="navbar__menu">
                <Link to="/" className={`navbar__menu--item ${location.pathname === "/"?"active":""}`}>
                <Typography>Events</Typography>
                </Link>
                {user.isAuthorized?
                <Link to="/create-event" className={`navbar__menu--item ${location.pathname === "/create-event"?"active":""}`}>
                <Typography>Create Event</Typography>
                </Link>:""}
                <Link to="/workshops" className={`navbar__menu--item ${location.pathname === "/workshops"?"active":""}`}>
                <Typography>Workshops</Typography>
                </Link>
                {user.isAuthorized?
                <Link to="/create-workshop" className={`navbar__menu--item ${location.pathname === "/create-workshop"?"active":""}`}>
                <Typography>Create Workshop</Typography>
                </Link>:""}
            </ul>

            {user.isAuthorized?
        <div className="navbar__avatar" style={{display:"flex",alignItems:"center"}}>
            <Typography sx={{color:"#fff",marginRight:"10px",textTransform:"capitalize"}}>{user.name+" "+user.surname}</Typography>
             <Avatar sx={{background:"#fff",color:"#000"}}>{user.name.toUpperCase()[0]+user.surname.toUpperCase()[0]}</Avatar>
            <Link to="/auth"  onClick={()=>{localStorage.removeItem("id");dispatch({type:"CLEAR_ATTENDEE"})}}>
             <Button className="navbar__btn" id="logout"><RxEnter/></Button>
             </Link>
        </div>:
        <Link to="/auth">
        <Button className="navbar__btn">Log in <RxEnter/></Button>
        </Link>}
        </div> 
    </div>
}