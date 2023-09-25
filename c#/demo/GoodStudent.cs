namespace ConsoleApp1;

class GoodStudent : Student
{
    public GoodStudent(string name) : base(name)
    {
        this.state += "good";
    }

    public override void Study()
    {
        Read();
        Write();
        Read();
        Write();
        Relax();
    }
}