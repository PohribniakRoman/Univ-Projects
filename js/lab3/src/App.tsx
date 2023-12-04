import { useEffect, useRef, useState } from "react";
import { LoadInput } from "./components/LoadInput";
import { Loader } from "./components/Loader";
import { DataPlaceholder } from "./components/DataPlaceholder";
import { DataView } from "./components/DataView";
import React from "react";
import { SearchForm, SearchParams } from "./components/SearchForm";
import { Box, Button, Link, Modal, TextareaAutosize, Typography } from "@mui/material";
import { PDForm } from "./components/PDForm";

export const App = () => {
  const textArea = useRef<any>();
  const [isLoading, setLoading] = useState<boolean>(false);
  const [isOpened, setOpened] = useState<boolean>(false);
  const [isOpenedAdd, setOpenedAdd] = useState<boolean>(false);
  const [data, setData] = useState<Record<string, any>[] | null>(null);
  const [visualisedData, setVisualisedData] = useState(data);
  const [searchParams, setSearchParams] = useState<SearchParams[]>([]);

  useEffect(() => {
    setVisualisedData(data);
  }, [data]);

  useEffect(() => {
    const newState =
      data?.filter((user) => {
        let result = true;
        searchParams.forEach((entry) => {
          console.log(new String(user[entry.query]).includes(entry.value));
          if (!new String(user[entry.query]).includes(entry.value)) {
            result = false;
            return;
          }
        });
        return result;
      }) || [];
    setVisualisedData(newState);
  }, [searchParams]);

  return (
    <React.Fragment>
      <Modal open={isOpened} onClose={() => setOpened(false)}>
        <Box className="modal">
          <Typography variant="h4">About</Typography>
          <PDForm/>
          <Button onClick={()=>setOpened(false)}>Close</Button>
        </Box>
      </Modal>
      <Modal open={isOpenedAdd} onClose={() => setOpenedAdd(false)}>
        <Box className="modal">
          <Typography variant="h4">Add Entry</Typography>
          <div>
            <Typography>Add Entry</Typography>
            <TextareaAutosize ref={textArea}/>
          </div>
          <Button onClick={()=>{
            console.log(JSON.parse(textArea.current.value));
            try {
              const newEntry = JSON.parse(textArea.current.value);
              data && setData([...data,newEntry])
              setOpenedAdd(false)
            } catch (_) {}
            }}>Submit</Button>
        </Box>
      </Modal>
      <section className="wrapper">
        <section className="container">
          {data && <SearchForm setParams={setSearchParams} />}
          <LoadInput setLoading={setLoading} setState={setData} />
          <Link
            onClick={(event: any) => {
              const element = event.target;
              const dataStr =
                "data:text/json;charset=utf-8," +
                encodeURIComponent(JSON.stringify(visualisedData));
              element.setAttribute("href", dataStr);
              element.setAttribute("download", "Search_Result.json");
            }}
          >
            Download Data
          </Link>
          <Button onClick={() => setOpenedAdd(true)}>Add Entry</Button>
          <Button onClick={() => setOpened(true)}>About</Button>
        </section>
        {visualisedData?.length ? (
          <DataView data={visualisedData} />
        ) : (
          <DataPlaceholder />
        )}
      </section>
      {isLoading && <Loader />}
    </React.Fragment>
  );
};
