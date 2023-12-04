import { Box, CircularProgress, SxProps } from "@mui/material";


export const Loader = () => {
    return (
    <Box sx={loaderStyles}>
        <Box sx={loaderWrapper}>
        <CircularProgress />
        </Box>
    </Box>
  );
};

const loaderStyles = {
    top:0,
    position:'absolute',
    backgroundColor:'rgba(0,0,0,0.15)',
    width:"100svw",
    height:"100svh",
    display:'flex',
    justifyContent:'center',
    alignItems:'center',
} as SxProps


const loaderWrapper = {
    borderRadius:"20px",
    padding:"30px",
    backgroundColor:"#fff",
} as SxProps