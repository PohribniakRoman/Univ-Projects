import { CircularProgress } from "@mui/material"

export const centerContainer = {
    overflow:"hidden",
    height:"100vh",
    width:"100vw",
    display:"flex",
    backgroundColor:"#fefefe",
    alignItems:"center",
    justifyContent:"center",
    color:"#2a9df4",
} as React.CSSProperties

export const Loading:React.FC = () => {
    return <section style={centerContainer}>
        <CircularProgress color="inherit" />
    </section>
}