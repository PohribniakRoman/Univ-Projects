export const ENDPOINTS = {
    host:"http://localhost:5000",
    login:"/login",
    register:"/register",
    isAuth:"/isAuth",
    getData:"/getData",
    params:{
        method:"POST",
        mode: "cors",
        headers:{"Content-Type":"application/json"}
    }  as RequestInit
}