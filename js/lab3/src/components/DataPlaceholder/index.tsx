import { Box, SxProps, Typography } from "@mui/material";

export const DataPlaceholder = () => {
    return <Box sx={styles}>
        <Typography>There is no avalible data :(</Typography>
    </Box>;
}
 

const styles = {
    width:'80%',
    display:'flex',
    justifyContent:'center',
    alignItems:'center',
} as SxProps