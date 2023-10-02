using System;
using System.Collections.Generic;

namespace ConverterApp;

class Menu
{
    private int index = 0;

    private static List<Option> Options = new();
    public Menu() { }

    public void SetMenu(List<Option> options)
    {
        Options = options;
        GetInfo();
    }

    private void ChangeIndex(Boolean side)
    {
        if (side)
        {
            index = Options.Count > index + 1 ? index + 1 : 0;
        }
        else
        {
            index = 0 <= index - 1 ? index - 1 : Options.Count - 1;
        }
    }

    public void InvokeListener()
    {
        ConsoleKeyInfo keyinfo;
        keyinfo = Console.ReadKey();
        if (keyinfo.Key == ConsoleKey.DownArrow)
        {
            ChangeIndex(true);
            GetInfo();
        }
        else if (keyinfo.Key == ConsoleKey.UpArrow)
        {
            ChangeIndex(false);
            GetInfo();
        }
        else if (keyinfo.Key == ConsoleKey.Enter)
        {
            Options[index].Selected();
        }
        else
        {
            GetInfo();
        }
    }

    public void GetInfo()
    {
        Console.ForegroundColor = ConsoleColor.Gray;
        Console.Clear();
        foreach (Option option in Options)
        {
            if (option == Options[index])
            {
                Console.Write("> ");
            }
            else
            {
                Console.Write(" ");
            }
            Console.WriteLine(option.Name);
        }
        InvokeListener();
    }
}