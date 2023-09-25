using System;
using WorkerApp;

class Program{
    static void Main(string[] args){
        Team team = new Team("Команда 1");
        Developer roman = new Developer("Roman");
        Manager alex = new Manager("Alex");
        team.AddWorker(roman);
        team.AddWorker(alex);
        roman.FillWorkDay();
        alex.FillWorkDay();
        Console.WriteLine(team.GetInfo()); 
        Console.WriteLine(team.GetFullInfo()); 
    }
}