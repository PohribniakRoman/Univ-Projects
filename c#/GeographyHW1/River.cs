namespace GeoApp;
class River : GeoObject{
    double Speed,Length;
    public River(double x,double y,double speed,double length,string name,string description) : base(x,y,name,description){
        Speed = speed;
        Length = length;
    }
    public override string GetInfo(){
        return base.GetInfo()+$"\tSpeed: {Speed} m/s\n\tLength: {Length} km\n";
    }

}