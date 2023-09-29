using System;

namespace GeoApp;
class Program
{
    static void Main(string[] args)
    {
        GeoObject obj = new GeoObject(1.1,2.2,"Object","Some description");
        River dnipr = new River(1.1,2.2,2.5,391,"Dnipro","It is located in the eastern part of Ukraine,southeast of the Ukrainian capital Kyiv on the Dnieper River");
        Mount hoverla = new Mount(1.1,2.2,2061,"Hoverla","Mount at 2,061 metres (6,762 ft), is the highest mountain in Ukraine and part of the Ukrainian Carpathians.");
        Console.WriteLine(obj.GetInfo());
        Console.WriteLine(dnipr.GetInfo());
        Console.WriteLine(hoverla.GetInfo());
    }
}