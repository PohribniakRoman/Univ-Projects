(() => {
    if (!localStorage.getItem("todo")) {
        localStorage.setItem("todo", JSON.stringify([]))
    }
})()


export type todoReducer = todoItem[];

export interface todoItem{
    name:String;
    description:String;
    id:number;
    completed:boolean;
}

export interface todoAction{
    type:"ADD_TASK" | "ERASE_TASK" | "UPDATE_TASK";
    payload:any;
}


const updateStorage = (state: todoReducer) => {
    localStorage.setItem("todo", JSON.stringify(state));
    return (state);
}

const todo = localStorage.getItem("todo");
let defaultState:todoReducer = [];
if (todo) defaultState = JSON.parse(todo);


export const todoReducer = (state = defaultState, action: todoAction) => {
    switch (action.type) {
        case "ADD_TASK":{
            return updateStorage([...state,{...action.payload,id:new Date().getTime(),completed:false}])       
        };
        case "ERASE_TASK":{
            return updateStorage(state.filter(task=>task.id !== action.payload.id))    
        };
        case "UPDATE_TASK":{
            return updateStorage(state.map(task=>{
                if(task.id === action.payload.id){
                    task.completed = action.payload.completed;
                }
                return task;
            }))
        }
        default:{
            return state;
        }
    }
}