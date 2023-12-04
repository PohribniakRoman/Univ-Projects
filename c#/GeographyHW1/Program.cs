
using System;
using System.Collections.Generic;
using System.Linq;

namespace GeoApp;




class Program
{

    static void Main(string[] args)
    {
        var names = new List<string> { "Anna", "Bob", "Clark", "Denis", "Frenk" };
        var query = from n in names where (n.Length < 5) orderby n descending select n.Length;
        foreach (var x in query)
        {
            Console.Write(x + " ");
        }
    }
}