using System;

namespace GeoApp;
class Mount : GeographicalObject{
    double Piek;
    public Mount(double x,double y,double piek,string name,string description) : base(x,y,name,description){
        if (piek <= 0)
        {
            throw new ArgumentException("The highest point can not be 0 or negative",nameof(piek));
        }
        Piek = piek;
    }
    public override string GetInfo(){
        return base.GetInfo()+$"\tThe highest point: {Piek} meters\n";
    }
}