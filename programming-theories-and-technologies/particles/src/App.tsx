import React from "react";
import { Canvas } from "./components/Canvas";
import { ToDo } from "./components/Todo";

export const App:React.FC = () => {
    return <section>
        <Canvas/>
        <ToDo/>
    </section>
}