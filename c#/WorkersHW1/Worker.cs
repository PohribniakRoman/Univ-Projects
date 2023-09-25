namespace WorkerApp;

abstract class Worker
{
    public string Name { get; }
    public string Position { get; }
    public string WorkDay { get; private set; }


    public Worker(string name, string position)
    {
        Name = name;
        Position = position;
        WorkDay = "";
    }

    public void Call()
    {
        WorkDay += "Call ";
    }

    public void WriteCode()
    {
        WorkDay += "Wirte Code ";
    }

    public void Relax()
    {
        WorkDay += "Relax ";

    }

    public abstract void FillWorkDay();
}