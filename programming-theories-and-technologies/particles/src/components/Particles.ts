export const SIZE_X = window.innerWidth;
export const SIZE_Y = window.innerHeight;
export const RADIUS = 50;
export const CONNECT_DISTANCE = 50;
export const FADE_DISTANCE = 100;




export class Particle{
    size:number;
    x:number;
    y:number;
    currentDirectionX:number;
    currentDirectionY:number;
    speed:number;
    currentSpeed:number;

    constructor(){
        this.x = Math.random() * SIZE_X;
        this.y = Math.random() * SIZE_Y;
        this.size =Math.floor(Math.random() * 3)+1;
        this.speed = Math.max(Math.floor(Math.random() * 8)+1,3);
        this.currentSpeed = 0;
        this.currentDirectionX = Math.floor(Math.random()*2) === 0 ? -1:1;
        this.currentDirectionY = Math.floor(Math.random()*2) === 0 ? -1:1;
    }
    move(){
        if(this.speed === this.currentSpeed){
            if(this.x >= SIZE_X)this.currentDirectionX = -1;
            if(this.x <= 0)this.currentDirectionX = 1
            this.x = this.x+this.currentDirectionX
            if(this.y >= SIZE_Y)this.currentDirectionY = -1;
            if(this.y <= 0)this.currentDirectionY = 1
            this.y = this.y+this.currentDirectionY
            this.currentSpeed = 0;
        }
        this.currentSpeed++;
    }
}
export const generateParticles = (n:number):Particle[] => {
    return new Array(n).fill("").map(()=> new Particle())
}

