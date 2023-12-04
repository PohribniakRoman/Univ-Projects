import { useEffect, useState } from "react";
import { LoadInput } from "./components/LoadInput";
import { Loader } from "./components/Loader";
import { DataPlaceholder } from "./components/DataPlaceholder";
import { DataView } from "./components/DataView";
import React from "react";
import { SearchForm, SearchParams } from "./components/SearchForm";
import {
  Box,
  Button,
  Link,
  Modal,
  TextField,
  Typography,
} from "@mui/material";
import { PDForm } from "./components/PDForm";

const defultFormState = {
  id: "",
  name: "",
  username: "",
  email: "",
  address: "",
  phone: "",
  website: "",
};

export const App = () => {
  const [isLoading, setLoading] = useState<boolean>(false);
  const [isOpened, setOpened] = useState<boolean>(false);
  const [isOpenedAdd, setOpenedAdd] = useState<boolean>(false);
  const [data, setData] = useState<Record<string, any>[] | null>(null);
  const [visualisedData, setVisualisedData] = useState(data);
  const [formData, setFormData] =
    useState<typeof defultFormState>(defultFormState);
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
          <PDForm />
          <Button onClick={() => setOpened(false)}>Close</Button>
        </Box>
      </Modal>
      <Modal open={isOpenedAdd} onClose={() => setOpenedAdd(false)}>
        <Box className="modal">
          <Typography variant="h4">Add Entry</Typography>
          <div className="addForm">
            {Object.keys(formData).map((el) => (
              <div>
                <Typography>{el}</Typography>
                <TextField
                  onChange={(event) => {
                    setFormData((prev) => ({
                      ...prev,
                      [el]: event.target.value,
                    }));
                  }}
                />
              </div>
            ))}
          </div>
          <Button
            onClick={() => {
              data && setData([...data, formData]);
              setOpenedAdd(false);
            }}
          >
            Submit
          </Button>
        </Box>
      </Modal>
      <section className="wrapper">
        <section className="container">
          {data && <SearchForm setParams={setSearchParams} />}
          <LoadInput setLoading={setLoading} setState={setData} />
          {data && <Link
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
          </Link>}
          {data && <Button onClick={() => setOpenedAdd(true)}>Add Entry</Button>}
          <Button onClick={() => setOpened(true)}>About</Button>
        </section>
        {visualisedData?.length ? (
          <DataView data={visualisedData} setData={setData} />
        ) : (
          <DataPlaceholder />
        )}
      </section>
      {isLoading && <Loader />}
    </React.Fragment>
  );
};
