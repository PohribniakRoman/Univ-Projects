namespace WorkerApp;

class Developer : Worker
{
    public Developer(string name) : base(name, "Розробник") {}

    public override void FillWorkDay()
    {
        WriteCode();
        Call();
        Relax();
    }

}