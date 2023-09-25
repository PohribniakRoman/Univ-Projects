namespace ConsoleApp1;

class BadStudent : Student
{
    public BadStudent(string name) : base(name)
    {
        this.state += "bad";
    }

    public override void Study()
    {
        Relax();
        Relax();
        Relax();
        Relax();
        Read();
    }
}