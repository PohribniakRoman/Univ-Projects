import {useParams} from 'react-router';
import useWebRTC, {LOCAL_VIDEO} from '../hooks/useWebRTC';
import { Navabar } from '../components/Navbar';
import { useEffect, useState } from 'react';
import { ENDPOINTS } from '../services/ENDPOINTS';
import Cookies from "universal-cookie";
import { Loading } from '../components/Loading';
const cookies = new Cookies();

function layout(clientsNumber = 1) {
  const pairs:any = Array.from({length: clientsNumber})
    .reduce((acc:any, next, index, arr) => {
      if (index % 2 === 0) {
        acc.push(arr.slice(index, index + 2));
      }

      return acc;
    }, []);

  const rowsNumber = pairs.length;
  const height = `${100 / rowsNumber}%`;

  return pairs.map((row:any, index:any, arr:any) => {

    if (index === arr.length - 1 && row.length === 1) {
      return [{
        width: '100%',
        height,
      }];
    }

    return row.map(() => ({
      width: '50%',
      height,
    }));
  }).flat();
}

export const Room:React.FC = () => {
  const {id: roomID} = useParams();
  const {clients, provideMediaRef} = useWebRTC(roomID);
  const videoLayout = layout(clients.length);

  const [user,setUser] = useState<any>({login:"loading..."})

  useEffect(()=>{
      (async ()=>{
          const {user} = await (await fetch(ENDPOINTS.host+ENDPOINTS.getData,{...ENDPOINTS.params,body:JSON.stringify({token:cookies.get("token")})})).json()
          setUser(user);
        })()  
    },[])

    return (
    <>
    <Navabar user={user}/>
    <div style={{
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        flexWrap: 'wrap',
        height: '100vh',
    }}>
      {clients.map((clientID:any, index:any) => {
          return (
          <div key={clientID} style={videoLayout[index]} id={clientID}>
            <video
              width='100%'
              height='100%'
              ref={instance => {
                  provideMediaRef(clientID, instance);
                }}
                autoPlay
                playsInline
                muted={clientID === LOCAL_VIDEO}
                />
          </div>
        );
    })}
    </div>
    </>
  );
}