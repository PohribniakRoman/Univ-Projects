import { Box, Button, Container, Grid, Typography } from "@mui/material"
import {Link} from "react-router-dom"

export const ErrorPage:React.FC = () => {
    return  <Box
    sx={{
      display: 'flex',
      justifyContent: 'center',
      alignItems: 'center',
      minHeight: '100vh'
    }}
  >
    <Container maxWidth="md">
      <Grid container spacing={2}>
        <Grid xs={6} style={{display:"flex",flexDirection:"column",justifyContent:"center",alignItems:"center"}}>
          <Typography variant="h4" style={{margin:"3    0px",textAlign:"center"}}>
            The page you’re looking for doesn’t exist.
          </Typography>
          <Link to="/home">
            <Button variant="contained">Back Home</Button>
          </Link>
        </Grid>
        <Grid xs={6}>
          <img
            src="https://techblog.sdstudio.top/wp-content/uploads/2021/01/d8e891d3cf83ec1a1e43a71bef4fe4ea-1.png"
            alt="error"
            width={500} height={250}
          />
        </Grid>
      </Grid>
    </Container>
  </Box>
}