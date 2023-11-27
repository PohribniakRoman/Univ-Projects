import { useEffect, useState } from "react";
import { LoadInput } from "./components/LoadInput";
import { Loader } from "./components/Loader";
import { DataPlaceholder } from "./components/DataPlaceholder";
import { DataView } from "./components/DataView";
import React from "react";
import { SearchForm, SearchParams } from "./components/SearchForm";
import { Box, Button, Link, Modal, Typography } from "@mui/material";

export const App = () => {
  const [isLoading, setLoading] = useState<boolean>(false);
  const [isOpened, setOpened] = useState<boolean>(false);
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
          <div>
            <Typography>Full Name:Pohrbniak Roman</Typography>
            <Typography>Course:2</Typography>
            <Typography>Group:K-26</Typography>
            <Typography>Year:2023</Typography>
            <Typography>
              Info: This project involves building a data management application
              in WEB for handling JSON files. It
              includes features like reading, visualizing, editing data through
              a form, and implementing LINQ-based search criteria, all within a
              grid-based interface. The "About" section provides personal
              details and a brief program description.
            </Typography>
          </div>
          <Button onClick={()=>setOpened(false)}>Close</Button>
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
