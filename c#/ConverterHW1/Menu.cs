using System;
using System.Collections.Generic;

namespace ConverterApp;

class Menu{
    private int index = 0;
    private static List<Option> options = new();
    public Menu(){
        options = new List<Option>
            {
                new Option("Watch Amount", () => {}),
                new Option("Convert to USD", () =>  {}),
                new Option("Convert to UAH", () =>  {}),
                new Option("Exit", () => Environment.Exit(0)),
            };
    }

    private void ChangeIndex(Boolean side){
        if(side){
            index = options.Count > index+1 ? index+1:0; 
        }else{
            index = 0 <= index-1 ? index-1:options.Count-1; 
        }
    }

    public void InvokeListener(){
     ConsoleKeyInfo keyinfo;
        do
        {
            keyinfo = Console.ReadKey();
            if (keyinfo.Key == ConsoleKey.DownArrow)
            {
                ChangeIndex(true);
                GetInfo();
            }
            if (keyinfo.Key == ConsoleKey.UpArrow)
            {
                ChangeIndex(false);
                GetInfo();
            }
            if (keyinfo.Key == ConsoleKey.Enter)
            {
            }
        }
        while (keyinfo.Key != ConsoleKey.X);
   
    }

    public void GetInfo()
        {
            Console.Clear();
            foreach (Option option in options)
            {
                if (option == options[index])
                {
                    Console.Write("> ");
                }
                else
                {
                    Console.Write(" ");
                }

                Console.WriteLine(option.Name);
            }
        }
}