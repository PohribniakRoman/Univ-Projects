import { Router } from "./services/Router"
import { configureStore } from "@reduxjs/toolkit";
import { Provider } from "react-redux";
import { combineReducer } from "./reducers/combinedReducers";


const store = configureStore({reducer:combineReducer});

export const App:React.FC = () => {
    return(<Provider store = {store}>
        <Router/>
    </Provider>)
}