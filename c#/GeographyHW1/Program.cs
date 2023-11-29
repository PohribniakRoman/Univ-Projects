
using System;
using System.Collections.Generic;
using System.Linq;

namespace GeoApp;



class Program
{

    static void Main(string[] args)
    {
        var nameList = new List<string>() { "Adler", "Tomas", "Bob", "Toni", "Xavier" };
        var a = nameList.First(e => e.Contains("To"));
        var b = nameList.Single(e => e.Contains("To"));
        Console.WriteLine(a = b);
        Console.ReadLine();
    }
}