import { Typography,Button } from "@mui/material";
import {BsFillPeopleFill} from "react-icons/bs";
import {Link} from "react-router-dom";
import { useSelector } from "react-redux";

export const EventEntry:React.FC<any> = ({data}) => {
    let descr = data.description;
    if(descr.length>100){
        descr = descr.substring(0,100).trim()+  "...";
    }
    const user = useSelector((state:any)=>state.user);

    return <div className="events__entry">
        <Typography className="events__entry--header" variant="h4">- {data.title}</Typography>
        <div className="events__entry--badge"> <Typography>{data.attendees.length}</Typography> <BsFillPeopleFill/></div>
        <Link to={`/event/${data.id}`}>
            <Button className="events__entry--btn" style={{right:"20px"}} id="details"> Details </Button>
        </Link>
        <Typography className="events__entry--descr">
            {descr}
        </Typography> 
        <div className="events__entry--author"> <Typography>{data.author.name}  {data.author.surname}</Typography></div>
    </div>
}