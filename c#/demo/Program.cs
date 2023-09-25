using System;

namespace ConsoleApp1;

class Program{
    static void Main(string[] args){
        Group k26 = new Group("K26");
        k26.AddStudent(new GoodStudent("Andrew"));
        k26.AddStudent(new BadStudent("John"));
        Console.WriteLine(k26.GetInfo());
    }
}