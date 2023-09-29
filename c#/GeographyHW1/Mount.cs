using System;

namespace GeoApp;
class Mount : GeoObject{
    double Piek;
    public Mount(double x,double y,double piek,string name,string description) : base(x,y,name,description){
        Piek = piek;
    }
    public override string GetInfo(){
        return base.GetInfo()+$"\tThe highest point: {Piek} meters\n";
    }
}