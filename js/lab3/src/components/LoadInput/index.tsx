import { Button } from "@mui/material";
import {useRef} from 'react';


interface LoadInputProps {
  setState: Function;
  setLoading: Function;
}

export const LoadInput = ({ setState, setLoading }: LoadInputProps) => {
    const ref = useRef<any>();

  return (
    <>
      <Button onClick={()=>ref.current.click()}>Load File</Button>
      <input
        ref={ref}
        type="file"
        style={{ display: "none" }}
        onChange={(event: React.ChangeEvent<HTMLInputElement>) => {
          if (
            event.target.files &&
            event.target.files[0].type === "application/json"
          ) {
            setLoading(true);
            const reader = new FileReader();
            reader.onload = () => {
              if (typeof reader.result === "string") {
                const rawData = reader.result.split(",");
                setState(JSON.parse(atob(rawData[1])));
              }
              setLoading(false);
            };
            reader.readAsDataURL(event.target.files[0]);
          } else {
            alert("Invalid input data!");
          }
        }}
      />
    </>
  );
};
