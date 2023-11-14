using System.Collections.ObjectModel;
using System.Xml;
using System.Xml.Serialization;

namespace lab2XML;
public class XMLDataHandlers
{
    public List<MainPageViewModel.StudentItem> students;
    public List<MainPageViewModel.Discepline> myCourses;

    XmlDocument document;
    public XMLDataHandlers()
    {
        myCourses = new();
        document = new();
        document.Load(@"C:\Users\Roman\Desktop\univ-projects\c#\lab2XML\assets\data.xml");
        XmlNodeList nodes = document.GetElementsByTagName("student");
        students = new();
        foreach (XmlNode node in nodes)
        {
            List<MainPageViewModel.Discepline> disceplines = new();
            foreach (XmlNode disc in node.ChildNodes[3])
            {
                disceplines.Add(new MainPageViewModel.Discepline { Title = disc.ChildNodes[0].InnerText, Grade = disc.ChildNodes[1].InnerText });
            }
            double all = 0;
            disceplines.ForEach(disc =>
            {
                all += double.Parse(disc.Grade);
            });
            double AVG = all / (double)disceplines.Count;
            var items = disceplines.Select(item => item.Title + ":" + item.Grade).ToArray();
            students.Add(new MainPageViewModel.StudentItem
            {
                Name = "Name:" + node.ChildNodes[0].InnerText,
                Faculty = "Faculty:" + node.ChildNodes[1].InnerText,
                Department = "Department:" + node.ChildNodes[2].InnerText,
                Disceplines = "Grades:\n\t" + string.Join("\n\t", disceplines.Select(item => item.Title + ":" + item.Grade).ToArray()),
                AVGGrade = AVG,
            });
        }
    }

    public List<MainPageViewModel.StudentItem> DOM_Search(MainPageViewModel.StudentItem student)
    {
        students.Clear();
        using (XmlReader reader = XmlReader.Create(@"C:\Users\Roman\Desktop\univ-projects\c#\lab2XML\assets\data.xml"))
        {
            while (reader.Read())
            {
                if (reader.NodeType == XmlNodeType.Element && reader.Name == "students")
                {
                    while (reader.Read())
                    {
                        if (reader.NodeType == XmlNodeType.Element && reader.Name == "student")
                        {
                            ReadStudentData(reader, student);
                        }
                    }
                }
            }
        }
        return students;
    }


    void ReadStudentData(XmlReader reader, MainPageViewModel.StudentItem student)
    {
        myCourses.Clear();
        string name = "";
        string faculty = "";
        string department = "";

        while (reader.Read())
        {
            if (reader.NodeType == XmlNodeType.Element)
            {
                switch (reader.Name)
                {
                    case "name":
                        name = reader.ReadElementContentAsString();
                        break;
                    case "faculty":
                        faculty = reader.ReadElementContentAsString();
                        break;
                    case "department":
                        department = reader.ReadElementContentAsString();
                        break;
                    case "courses":
                        ReadCourses(reader);
                        break;
                }
            }

            double all = 0;
            myCourses.ForEach(disc =>
            {
                all += double.Parse(disc.Grade);
            });
            double AVG = all / (double)myCourses.Count;
            var items = myCourses.Select(item => item.Title + ":" + item.Grade).ToArray();

            if (reader.NodeType == XmlNodeType.EndElement && reader.Name == "student")
            {
                if (!faculty.Contains(student.Faculty)) break;
                if (!department.Contains(student.Department)) break;
                if (!name.Contains(student.Name)) break;
                if (AVG < student.AVGGrade) break;
                students.Add(new MainPageViewModel.StudentItem
                {
                    Name = "Name: " + name,
                    Faculty = "Faculty: " + faculty,
                    Department = "Department: " + department,
                    Disceplines = "Grades:\n\t" + string.Join("\n\t", myCourses.Select(item => item.Title + ":" + item.Grade).ToArray()),
                    AVGGrade = AVG
                });
                break;
            }
        }
    }

    void ReadCourses(XmlReader reader)
    {
        while (reader.Read())
        {
            if (reader.NodeType == XmlNodeType.Element && reader.Name == "course")
            {
                string courseName = "";
                string grade = "";

                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.Element)
                    {
                        switch (reader.Name)
                        {
                            case "course_name":
                                courseName = reader.ReadElementContentAsString();
                                break;
                            case "grade":
                                grade = reader.ReadElementContentAsString();
                                break;
                        }
                    }

                    if (reader.NodeType == XmlNodeType.EndElement && reader.Name == "course")
                    {
                        myCourses.Add(new MainPageViewModel.Discepline { Title = "courseName", Grade = grade });
                        break;
                    }
                }
            }

            if (reader.NodeType == XmlNodeType.EndElement && reader.Name == "courses")
            {
                break;
            }
        }
    }

    public List<MainPageViewModel.StudentItem> SAX_Search(MainPageViewModel.StudentItem student)
    {
       return DOM_Search(student);
    }


    public XmlDocument CreateXmlDocument()
    {
        XmlDocument xmlDoc = new XmlDocument();

        // Create XML declaration
        XmlDeclaration xmlDeclaration = xmlDoc.CreateXmlDeclaration("1.0", "UTF-8", null);
        xmlDoc.AppendChild(xmlDeclaration);

        // Create root element
        XmlElement rootElement = xmlDoc.CreateElement("students");
        xmlDoc.AppendChild(rootElement);

        // Iterate through the list and add student elements
        foreach (var student in students)
        {
            XmlElement studentElement = xmlDoc.CreateElement("student");

            XmlElement nameElement = xmlDoc.CreateElement("name");
            nameElement.InnerText = student.Name;
            studentElement.AppendChild(nameElement);

            XmlElement departmentElement = xmlDoc.CreateElement("department");
            departmentElement.InnerText = student.Department;
            studentElement.AppendChild(departmentElement);

            XmlElement facultyElement = xmlDoc.CreateElement("faculty");
            facultyElement.InnerText = student.Faculty;
            studentElement.AppendChild(facultyElement);

            XmlElement disciplinesElement = xmlDoc.CreateElement("disciplines");
            disciplinesElement.InnerText = student.Disceplines;
            studentElement.AppendChild(disciplinesElement);

            rootElement.AppendChild(studentElement);
        }

        return xmlDoc;
    }


}