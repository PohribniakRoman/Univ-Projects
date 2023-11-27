import { useEffect, useState } from "react"
import { QueryEntry } from "../QueryEntry";

interface SearchFormParams{
    setParams:Function;
}

export interface SearchParams {
    query:string;
    value:string;
}

export const SearchForm = ({setParams}:SearchFormParams) => {
    const [searchParams,setSearchParams] = useState<SearchParams[]>([{query:"email",value:''},{query:"id",value:''},{query:'name',value:''}]);
    
    useEffect(()=>{
        setParams(searchParams);
    },[searchParams])
    

    return <section>
        {searchParams.map(input=>{
            return <QueryEntry key={input.query} query={input.query} setSearchParams={setSearchParams}/> 
        })}
    </section>
}