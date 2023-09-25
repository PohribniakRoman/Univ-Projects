namespace ConsoleApp1;

abstract class Student
{
    public string Name { get; }

    protected string state;

    public Student(string name) 
    {
        this.Name = name;
        this.state = "";
    }

    public void Relax() 
    {
        this.state += "Relax";
    }

    public void Read()
    {
        this.state += "Read";
    }

    public void Write()
    {
        this.state += "Write";
    }

    public abstract void Study();


}