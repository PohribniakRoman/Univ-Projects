// using System;

// class Program
// {
//     public static void Main(string[] args)
//     {
//         Console.WriteLine("Enter Value and ");
//         var raw = Console.ReadLine();
//         int amount;
//         if(int.TryParse(raw,out amount)){
//             Console.WriteLine(amount);
//         }else{
//             Console.WriteLine("");
//         };


//     }
// }
namespace ConverterApp;

    class Program
    {
        static void Main(string[] args)
        {
            
        Menu menu = new Menu();
        menu.GetInfo();
        menu.InvokeListener();
        
        }
    }

