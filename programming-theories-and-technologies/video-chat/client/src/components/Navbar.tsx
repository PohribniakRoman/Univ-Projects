import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import { AppBar, Avatar, Box, Button } from '@mui/material';
import { Link, useNavigate } from 'react-router-dom';
import {BsDoorOpen} from "react-icons/bs";
import { deepPurple } from '@mui/material/colors';
import Cookies from "universal-cookie";
const cookies = new Cookies();

export const Navabar:React.FC<any> = ({user}) =>{
    const navigate = useNavigate();
    return <Box sx={{ flexGrow: 1 }}>
    <AppBar position="static">
      <Toolbar>
        <Box sx={{ flexGrow: 1,display:'flex',alignItems:"center",gap:"50px"}}>
            <Typography variant="h5" sx={{ userSelect:"none",cursor:"context-menu" }}>
            Chat-App
            </Typography>
            <Link to="/home">
                <Typography>
                    Home
                </Typography>
            </Link>
        </Box>
        <Box sx={{display:'flex',alignItems:"center",gap:"10px",marginRight:"20px"}}>
            <Typography>{user.login}</Typography>
            <Avatar sx={{background: deepPurple[500]}}>{user.login[0].toUpperCase()}</Avatar>
            <Button variant='contained' id="logOut" onClick={()=>{
            cookies.remove("token");
            navigate(`/auth`);
            }}><BsDoorOpen/></Button>
        </Box>
      </Toolbar>
    </AppBar>
  </Box>
}