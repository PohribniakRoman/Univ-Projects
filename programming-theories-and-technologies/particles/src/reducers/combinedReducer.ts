import { combineReducers } from "@reduxjs/toolkit";
import { todoReducer } from "./todoReducer";

export type State = {
    todo:todoReducer
}

export const combinedReducer = combineReducers({
    todo:todoReducer,
})