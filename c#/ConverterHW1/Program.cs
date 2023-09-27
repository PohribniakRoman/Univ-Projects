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
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Threading;

namespace ConverterApp;

class Program
{
    static void Main(string[] args)
    {
        Menu menu = new Menu();
        Option exit = new Option("Exit", () => Environment.Exit(0));

        menu.SetMenu(new List<Option>
        {
            new Option("Enter Amount",()=>{
                Console.Clear();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Enter Amount please:",Console.ForegroundColor);

                string? rawData = Console.ReadLine();
                double amount;

                if(double.TryParse(rawData,out amount)){

                    Converter converter = new Converter(amount);
                    Console.ForegroundColor = ConsoleColor.Cyan;

                    menu.SetMenu(new List<Option>
                        {
                            new Option("Check Balance",()=>{

                                Console.Clear();
                                Console.ForegroundColor = ConsoleColor.Green;
                                Console.WriteLine("Yout current balance: "+converter.GetInfo()+"\nHit Enter to get back");
                                ConsoleKeyInfo key;

                                do
                                {
                                    key = Console.ReadKey();
                                    Console.Clear();
                                    Console.WriteLine("Yout current balance: "+converter.GetInfo()+"\nHit Enter to get back");

                                } while(key.Key != ConsoleKey.Enter);

                                menu.GetInfo();
                            }),
                            new Option("Convert to USD",()=>{

                                converter.ToUSD();
                                Console.Clear();
                                Console.ForegroundColor = ConsoleColor.Cyan;
                                Console.WriteLine("Converted!\nYout current balance: "+converter.GetInfo()+"\nPress any btn to get back");
                                ConsoleKeyInfo key = Console.ReadKey();
                                menu.GetInfo();

                            }),
                            new Option("Convert to EUR",()=>{

                                converter.ToEUR();
                                Console.Clear();
                                Console.ForegroundColor = ConsoleColor.Cyan;
                                Console.WriteLine("Converted!\nYout current balance: "+converter.GetInfo()+"\nPress any btn to get back");
                                ConsoleKeyInfo key = Console.ReadKey();
                                menu.GetInfo();

                            }),
                            new Option("Convert to UAH",()=>{

                                converter.ToBase();
                                Console.Clear();
                                Console.ForegroundColor = ConsoleColor.Cyan;
                                Console.WriteLine("Converted!\nYout current balance: "+converter.GetInfo()+"\nPress any btn to get back");
                                ConsoleKeyInfo key = Console.ReadKey();
                                menu.GetInfo();

                            }),
                            exit
                        });

                }else{

                    Console.Clear();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Wrong Input!",Console.ForegroundColor);

                    Thread.Sleep(500);

                    menu.GetInfo();

                };
            }),
            exit
        });


    }
}

