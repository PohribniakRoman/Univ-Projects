﻿
using System;

namespace GeoApp;

public interface River
{
    string Name {get;set;}
}


class Program
{
    static void Main(string[] args)
    {
        // GeographicalObject obj = new GeographicalObject(1.1,2.2,"Object","Some description");
        // River dnipr = new River(1.1,2.2,2.5,391,"Dnipro","It is located in the eastern part of Ukraine,southeast of the Ukrainian capital Kyiv on the Dnieper River");
        // Mount hoverla = new Mount(1.1,2.2,2061,"Hoverla","Mount at 2,061 metres (6,762 ft), is the highest mountain in Ukraine and part of the Ukrainian Carpathians.");
        // Console.WriteLine(obj.GetInfo());
        // Console.WriteLine(dnipr.GetInfo());
        // Console.WriteLine(hoverla.GetInfo());
        DoSMT();


    }
    public void DoSMT(object obj){
    var emp = (River)obj;
    if(emp != null){
        Console.WriteLine(emp.Name);
    }
}
}