import { combineReducers } from "redux";
import { user } from "./userReducer";


export const combineReducer = combineReducers({
    user,
})