import { v4, validate } from "uuid";

let defaultState = {
    name:"",
    surname:"",
    email:"",
    phone:"",
    age:0,
    date:new Date().getTime(),
    id:"",
    isAuthorized:false
}

export const user = (state = defaultState,action:any) => {
    switch (action.type) {
        case "LOAD_ATTENDEE":{
            return({...action.payload});
        };
        case "CLEAR_ATTENDEE":{
            console.log("WORK!");
            return({...defaultState})
        }
        default:{
            return state;
        }
    }
}