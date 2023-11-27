import { Box, TextField, Typography, capitalize } from "@mui/material";
import { useEffect, useState } from "react";
import { useDebounceWithCallback } from "../../hooks/useDebounce";
import { SearchParams } from "../SearchForm";

interface QueryEntryProps {
  query: string;
  setSearchParams:Function;
}

export const QueryEntry = ({ query,setSearchParams }: QueryEntryProps) => {
  const initialValue = "";
  const [value, setValue] = useState(initialValue);
  const debounce = useDebounceWithCallback<string>("", 200, (value) =>
    setValue(value)
  );

  useEffect(()=>{
      setSearchParams((prev:SearchParams[])=>{
        const newState = prev.filter(entry=>entry.query !== query);
        newState.push({query,value})
        return newState;
      })
  },[value])
  
  return (
    <Box>
      <Typography variant="h6">{capitalize(query)}</Typography>
      <TextField
        placeholder="Query value"
        onInput={(event: React.ChangeEvent<HTMLInputElement>) =>
          debounce(event.target.value)
        }
      />
    </Box>
  );
};
