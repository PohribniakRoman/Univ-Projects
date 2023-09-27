import React, { useState } from "react";
import { Button } from "react-bootstrap";
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import Form from 'react-bootstrap/Form';
import { useDispatch,useSelector } from "react-redux/es/exports";
import { todoAction, todoItem } from "../reducers/todoReducer";
import { State } from "../reducers/combinedReducer";



export const ToDo:React.FC = () => {
    const [isActive,setActive] = useState(true);
    const [isForm,setForm] = useState(false);
    const todo = useSelector((state:State)=>state.todo);
    const dispatch = useDispatch();

    const [description,setDescription] = useState<null|todoItem>(null)
    
    return <>
        <section className={`todo ${isActive?"active":""}`}>
        {isForm?
        <Form className="todo__form" onSubmit={(event:React.FormEvent)=>{
            event.preventDefault();
            const el = event.target as HTMLFormElement;
            console.log(el.taskName);
            const payload = {name:el.taskName.value.trim(),description:el.taskDescr.value.trim()}
            dispatch({type:"ADD_TASK",payload}as todoAction)
            el.taskDescr.value = ""
            el.taskName.value = ""
        }}>
            <Form.Label htmlFor="taskName">Task Name</Form.Label>
            <Form.Control name="taskName" id="taskName" required/>
            <Form.Text muted className="todo__form--text">Enter Task Name</Form.Text>
            <br/>
            <Form.Label htmlFor="taskDescr">Task Description</Form.Label>
            <Form.Control name="taskDescr" id="taskDescr" required/>
            <Form.Text muted className="todo__form--text">Enter Task Description</Form.Text>
            <br/>
            <Button type="submit">Add Task</Button>
        </Form>:
        <Container className="todo__wrapper">
            <Row className="todo__container">
                <Col sm="3" className="todo__list">
                    <h1 className="todo__list--title">Task List</h1>
                    {todo.map((entry,i)=>{
                        return <div key={entry.id} className={`todo__list--entry ${entry.completed && "completed"}`} onClick={()=>{
                            setDescription(entry);
                        }}>{i+1}.{entry.name}</div>
                    })}
                </Col>
                <Col sm="8" className="todo__task">
                    <h1 className="todo__list--title">Task Description</h1>
                    {description?
                    <>
                        <h3 className="todo__task--id">ID:{description.id}</h3>
                        <div className="todo__task--description">Description: {description.description}</div>
                        <Container>
                            <Row>
                                <Col>
                                <Button variant="danger"
                                onClick={()=>{
                                    dispatch({type:"ERASE_TASK",payload:{id:description.id}} as todoAction)
                                    setDescription(null)
                                }}>Delete Task</Button>
                                </Col>
                                <Col>
                                <Button variant="success" disabled={description.completed}
                                onClick={()=>dispatch({type:"UPDATE_TASK",payload:{id:description.id,completed:true}} as todoAction)}>Complete Task</Button>
                                </Col>
                                <Col>
                                <Button variant="info" disabled={!description.completed}
                                onClick={()=>dispatch({type:"UPDATE_TASK",payload:{id:description.id,completed:false}} as todoAction)}>UnComplete Task</Button>
                                </Col>
                            </Row>
                        </Container>
                    </>
                    :"Select Task"}
                </Col>
            </Row>
        </Container>}
        <Button onClick={()=>setForm(prev=>!prev)}> {!isForm?"Add new Task":"Watch Task List"}</Button>
        </section>
        <Button className="todo__btn" variant={`${isActive?"dark":"light"}`}  onClick={()=>{
            setActive(prev=>!prev);            
        }}>{!isActive?"Hide":"Show"}</Button>
    </>
}