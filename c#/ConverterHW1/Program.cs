using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Threading;

namespace ConverterApp;

class Program
{
    static void Main(string[] args)
    {
        Menu menu = new();
        Option exit = new("Exit", () => Environment.Exit(0));

        menu.SetMenu(new List<Option>
        {
            new Option("Enter Amount", () => {

                Console.Clear();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Enter USD exchange rate please:", Console.ForegroundColor);

                string? rawUsdExchangeRate = Console.ReadLine();
                decimal usdExchangeRate,eurExchangeRate;
                Console.WriteLine("Enter EUR exchange rate please:");
                string? rawEurExchangeRate = Console.ReadLine();

                if (decimal.TryParse(rawUsdExchangeRate,out usdExchangeRate) && decimal.TryParse(rawEurExchangeRate,out eurExchangeRate))
                {
                    Converter converter = new(usdExchangeRate,eurExchangeRate);
                    Console.ForegroundColor = ConsoleColor.Cyan;

                    menu.SetMenu(new List<Option>
                        {
                            new Option("Convert to USD",()=>{
                                Console.Clear();
                                Console.WriteLine("Enter amount to exchange:");
                                string? rawAmount = Console.ReadLine();
                                decimal amount;
                                if(decimal.TryParse(rawAmount,out amount))
                                {
                                    Console.Clear();
                                    Console.ForegroundColor = ConsoleColor.Cyan;
                                    Console.WriteLine("Converted!\nYou have: "+converter.ConvertToUSD(amount)+" USD\nPress any btn to get back");
                                    ConsoleKeyInfo key = Console.ReadKey();
                                }
                                menu.GetInfo();

                            }),
                            new Option("Convert to EUR",()=>{
                                Console.Clear();
                                Console.WriteLine("Enter amount to exchange:");
                                string? rawAmount = Console.ReadLine();
                                decimal amount;
                                if(decimal.TryParse(rawAmount,out amount))
                                {
                                    Console.Clear();
                                    Console.ForegroundColor = ConsoleColor.Cyan;
                                    Console.WriteLine("Converted!\nYou have: "+converter.ConvertToEUR(amount)+" EUR\nPress any btn to get back");
                                    ConsoleKeyInfo key = Console.ReadKey();
                                }
                                menu.GetInfo();

                            }),
                            new Option("Convert from USD",()=>{
                                Console.Clear();
                                Console.WriteLine("Enter amount to exchange:");
                                string? rawAmount = Console.ReadLine();
                                decimal amount;

                                if(decimal.TryParse(rawAmount,out amount))
                                {
                                    Console.Clear();
                                    Console.ForegroundColor = ConsoleColor.Cyan;
                                    Console.WriteLine("Converted!\nYou have: "+converter.ConvertFromUSD(amount)+" UAH\nPress any btn to get back");
                                    ConsoleKeyInfo key = Console.ReadKey();
                                }

                                menu.GetInfo();
                            }),
                            new Option("Convert from EUR",()=>{
                                    Console.Clear();
                                Console.WriteLine("Enter amount to exchange:");
                                string? rawAmount = Console.ReadLine();
                                decimal amount;
                                if(decimal.TryParse(rawAmount,out amount))
                                {
                                    Console.Clear();
                                    Console.ForegroundColor = ConsoleColor.Cyan;
                                    Console.WriteLine("Converted!\nYou have: "+converter.ConvertFromEUR(amount)+" UAH\nPress any btn to get back");
                                    ConsoleKeyInfo key = Console.ReadKey();
                                }
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

