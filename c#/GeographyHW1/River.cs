// using System;

// namespace GeoApp;
// class River : GeographicalObject{
//     double Speed,Length;
//     public River(double x,double y,double speed,double length,string name,string description) : base(x,y,name,description){
//         if (speed <= 0)
//         {
//             throw new ArgumentException("Speed can not be 0 or negative",nameof(speed));
//         }
//         if (length <= 0)
//         {
//             throw new ArgumentException("Length can not be 0 or negative",nameof(speed));
//         }
//         Speed = speed;
//         Length = length;
//     }
//     public override string GetInfo(){
//         return base.GetInfo()+$"\tSpeed: {Speed} m/s\n\tLength: {Length} km\n";
//     }

// }