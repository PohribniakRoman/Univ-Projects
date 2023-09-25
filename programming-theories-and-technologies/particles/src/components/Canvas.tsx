import { useEffect, useRef } from "react";
import { CONNECT_DISTANCE, FADE_DISTANCE, Particle, SIZE_X, SIZE_Y, generateParticles } from "./Particles";




interface Mouse{
    x:number;
    y:number;
}

const PARTICLES_AMOUNT = 100;
export const Canvas:React.FC = () => {
    const canvas = useRef<HTMLCanvasElement|null>(null);
    const mouse = useRef<Mouse>({x:0,y:0})
    const controlledParticle = new Particle();
    const particles = useRef<Particle[]>([...generateParticles(PARTICLES_AMOUNT),controlledParticle])

    useEffect(()=>{
        if (canvas.current) {
           const ctx = canvas.current.getContext("2d") as CanvasRenderingContext2D;
            setInterval(()=>{
            ctx.clearRect(0,0,SIZE_X,SIZE_Y);
            particles.current.forEach((particle,i) => {
                if(canvas.current){
                    ctx.beginPath();
                    ctx.arc(particle.x , particle.y, particle.size, 0, 2 * Math.PI,true);
                    ctx.fillStyle = "rgba(255,255,255,1)";
                    ctx.fill();
                    particles.current.forEach((satellite,j)=>{
                        if(j>i){
                            const x1 = Math.abs(satellite.x - particle.x);
                            const y1 = Math.abs(satellite.y - particle.y);
                            const distance = Math.sqrt(x1*x1+y1*y1);
                            if(distance <= CONNECT_DISTANCE){
                                ctx.beginPath();
                                ctx.moveTo(satellite.x,satellite.y);
                                ctx.lineTo(particle.x,particle.y);
                                ctx.lineWidth = 1;
                                ctx.strokeStyle = "rgba(255,255,255,1)";
                                ctx.stroke();
                            } else if(distance < FADE_DISTANCE){
                                ctx.beginPath();
                                ctx.moveTo(satellite.x,satellite.y);
                                ctx.lineTo(particle.x,particle.y);
                                ctx.lineWidth = 1;
                                ctx.strokeStyle = `rgba(255,255,255,${(FADE_DISTANCE-Math.sqrt(x1*x1+y1*y1)) / (FADE_DISTANCE-CONNECT_DISTANCE)})`;
                                ctx.stroke(); 
                            }
                        }
                    })
                }
                // const diffx = Math.abs(particle.x - mouse.current.x);
                // const diffy = Math.abs(particle.y - mouse.current.y);
                // if(Math.sqrt(diffy*diffy+diffx*diffx) < RADIUS && mouse.current.x && mouse.current.y){
                //     particle.x += particle.currentDirectionX*Math.abs(particle.x - mouse.current.x);
                //     particle.y += particle.currentDirectionY*Math.abs(particle.y - mouse.current.y);
                // }
                if(mouse.current.x && mouse.current.y){
                    controlledParticle.x = mouse.current.x;
                    controlledParticle.y = mouse.current.y;
                    controlledParticle.size = 2;
                }
                particle.move()
            });
            });
        }
    },[])
    

    return <section className="canvas">
        <canvas className="canvas__item" ref={canvas} width={SIZE_X} height={SIZE_Y} onMouseMove={(event:React.MouseEvent)=>{
            mouse.current.x = event.pageX;
            mouse.current.y = event.pageY;
        }}>
        </canvas>
    </section>
}