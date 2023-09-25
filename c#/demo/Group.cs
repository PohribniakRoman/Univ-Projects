using System.Collections.Generic;
using System.Linq;

namespace ConsoleApp1;

class Group
{
    private string name;

    private List<Student> students;

    public Group(string name)
    {
        this.name = name;
        students = new ();
    }
    
    public void AddStudent(Student student)
    {
        students.Add(student);
    }

    public string GetInfo()
    {
        string result = "Назва групи: " + name + "\n";
        result += string.Join("\n", students.Select((student, index) => {
            return (index + 1) + ". " + student.Name;
        }));

        return result;
    }

}