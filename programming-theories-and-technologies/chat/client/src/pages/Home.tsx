import {v4} from "uuid";

import { useNavigate } from "react-router-dom"

export const Home:React.FC = () => {
    const navigate = useNavigate();

    return <section>
        <button onClick={()=>{
            navigate(`/room/${v4()}`)}}>Create Room</button>
    </section>
}