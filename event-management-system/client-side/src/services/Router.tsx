import { BrowserRouter,Route,Routes } from "react-router-dom"
import { Events } from "../pages/Events"
import { EventPage } from "../pages/EventPage"

export const Router:React.FC = () => {
    return <BrowserRouter>
        <Routes>
            <Route path="/" element={<Events/>}/>
            <Route path="/event/:id" element={<EventPage/>} />
        </Routes>
    </BrowserRouter>
}