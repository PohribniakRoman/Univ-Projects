import { BrowserRouter,Route,Routes } from "react-router-dom"
import { Events } from "../pages/Events"
import { EventPage } from "../pages/EventPage"
import { Auth } from "../pages/Auth"

export const Router:React.FC = () => {
    return <BrowserRouter>
        <Routes>
            <Route path="/" element={<Events/>}/>
            <Route path="/event/:id" element={<EventPage/>} />
            <Route path="/auth" element={<Auth/>} />
        </Routes>
    </BrowserRouter>
}