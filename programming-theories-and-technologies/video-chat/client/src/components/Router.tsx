import { BrowserRouter,Route,Routes } from "react-router-dom"
import React from "react"
import { Auth } from "../pages/Auth"
import { PortectedRouter } from "./ProtectedRouter"
import { Home } from "../pages/Home"
import { ErrorPage } from "../pages/ErrorPage"
import { Room } from "../pages/Room"

export const Router:React.FC = () => {
    return <BrowserRouter>
        <Routes>
            <Route path="/auth" element={<Auth/>}/>
            <Route path="/room/:id" element={<PortectedRouter Component={Room} />}/>
            <Route path="/home" element={<PortectedRouter Component={Home} />}/>
            <Route path="*" element={<ErrorPage />}/>
        </Routes>
    </BrowserRouter>
}