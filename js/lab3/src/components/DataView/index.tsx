import Table from "@mui/material/Table";
import TableBody from "@mui/material/TableBody";
import TableCell from "@mui/material/TableCell";
import TableContainer from "@mui/material/TableContainer";
import TableHead from "@mui/material/TableHead";
import TableRow from "@mui/material/TableRow";
import Paper from "@mui/material/Paper";

const Capitalize = (str: any) => {
  if (typeof str === "object")
    return (
      <p onClick={() => alert("Data:\n" + JSON.stringify(str))}>
        Click to see data
      </p>
    );
  str = new String(str);
  return str.charAt(0).toUpperCase() + str.slice(1);
};

interface DataViewProps {
  data: Record<string, any>[];
  setData: Function;
}

export const DataView = ({ data, setData }: DataViewProps) => {
  const keys = Object.keys(data[0]);

  return (
    <section className="table">
      <TableContainer component={Paper}>
        <Table sx={{ minWidth: 650 }}>
          <TableHead>
            <TableRow>
              {keys.map((key, index) => (
                <TableCell key={index + key}>{Capitalize(key)}</TableCell>
              ))}
            </TableRow>
          </TableHead>
          <TableBody>
            {data.map((row) => (
              <TableRow
                key={row.name}
                sx={{ "&:last-child td, &:last-child th": { border: 0 } }}
              >
                {keys.map((key, index) => (
                  <TableCell key={index + key} onClick={()=>{
                    const data = prompt("Write new value");
                    if(data){
                      setData((prev:Record<string,any>[]) => [...prev.filter(el=>el.id !== row.id),{...row,[key]:data}]);
                    }
                  }}>
                    {Capitalize(row[key])}
                  </TableCell>
                ))}
                <TableCell
                  className="delete"
                  onClick={() =>
                    setData((prev:Record<string,any>[]) => prev.filter((el) => el.id !== row.id))
                  }
                >
                  Delete
                </TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </section>
  );
};
