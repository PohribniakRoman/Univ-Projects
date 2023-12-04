using System;
using System.Xml.Linq;
using System.Linq;
using Microsoft.Maui.Controls;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Xsl;
using Microsoft.Extensions.Logging;

namespace Lab2
{
    public interface IXmlProcessingStrategy
    {
        IEnumerable<string> ProcessXml(XDocument xmlDocument, string selectedAttribute);
    }

    public class LinqToXmlStrategy : IXmlProcessingStrategy
    {
        public IEnumerable<string> ProcessXml(XDocument xmlDocument, string selectedAttribute)
        {
            return xmlDocument.Descendants("teacher")
                              .Where(x => x.Element(selectedAttribute) != null)
                              .Select(x => x.Element(selectedAttribute).Value);
        }
    }

    public class DomXmlStrategy : IXmlProcessingStrategy
    {
        public IEnumerable<string> ProcessXml(XDocument xmlDocument, string selectedAttribute)
        {
            var xmlDoc = new XmlDocument();
            xmlDoc.LoadXml(xmlDocument.ToString());
            var results = new List<string>();

            var nodes = xmlDoc.GetElementsByTagName("teacher");
            foreach (XmlNode node in nodes)
            {
                if (node[selectedAttribute] != null)
                {
                    results.Add(node[selectedAttribute].InnerText);
                }
            }

            return results;
        }
    }

    public class SaxXmlStrategy : IXmlProcessingStrategy
    {
        public IEnumerable<string> ProcessXml(XDocument xmlDocument, string selectedAttribute)
        {
            var results = new List<string>();
            using (var reader = xmlDocument.CreateReader())
            {
                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.Element && reader.Name == "teacher")
                    {
                        if (reader.MoveToAttribute(selectedAttribute))
                        {
                            results.Add(reader.Value);
                        }
                    }
                }
            }

            return results;
        }
    }
    public class Teacher
    {
        public string Name { get; set; }
        public string Department { get; set; }
        public string Chair { get; set; }
        public string Room { get; set; }
        public string Students { get; set; }
        public string Lectures { get; set; }
        public string Details =>
            $"Name: {Name}\nDepartment: {Department}\nChair: {Chair}\nRoom: {Room} \nStudents: {Students})\n Lectures: {Lectures}\n";
    }

    public partial class MainPage : ContentPage
    {
        private List<Teacher> _savedScientists = new List<Teacher>();
        private XDocument _xmlDocument;
        private IXmlProcessingStrategy _currentStrategy;
        private Dictionary<string, IXmlProcessingStrategy> _strategies;
        private static readonly string HtmlFilePath = "C:\\Users\\Home\\Downloads\\Lab2-20231203T221344Z-001\\Lab2\\exportedData.html";
        private static readonly string XmlFilePath = "C:\\Users\\Home\\Downloads\\Lab2-20231203T221344Z-001\\Lab2\\data.xml";

        public MainPage()
        {
            InitializeComponent();

            _strategies = new Dictionary<string, IXmlProcessingStrategy>
    {
        { "LINQ to XML", new LinqToXmlStrategy() },
        { "SAX", new SaxXmlStrategy() },
        { "DOM", new DomXmlStrategy() }
    };

            _currentStrategy = _strategies["LINQ to XML"];

            LoadXmlFile(); 

            foreach (var strategyName in _strategies.Keys)
            {
                strategyPicker.Items.Add(strategyName);
            }
            strategyPicker.SelectedIndex = 0;
        }
        private string TransformXmlToHtml(string xmlFilePath, string xslPath)
        {
            try
            {
                XDocument xmlDocument = XDocument.Load(xmlFilePath);
                XslCompiledTransform transform = new XslCompiledTransform();
                transform.Load(xslPath);

                using (StringWriter writer = new StringWriter())
                {
                    transform.Transform(xmlDocument.CreateReader(), null, writer);
                    return writer.ToString();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error in XML to HTML transformation: {ex.Message}");
                return string.Empty;
            }
        }

        private XDocument CreateXmlFromSavedScientists(List<Teacher> teachers)
        {
            var xmlDocument = new XDocument(
                new XElement("ScheduleDataBase",
                    teachers.Select(s => new XElement("teacher",
                        new XElement("name", s.Name),
                        new XElement("department", s.Department),
                        new XElement("chair", s.Chair),
                        new XElement("room", s.Room),
                        new XElement("students", s.Students)
                        new XElement("lectures", s.Lectures)
                    ))
                )
            );

            return xmlDocument;
        }
        private void SaveXmlToFile(XDocument xmlDocument, string filePath)
        {
            xmlDocument.Save(filePath);
        }



        private List<Teacher> GetAllScientists()
        {
            return _xmlDocument.Descendants("teacher")
                               .Select(x => new Scientist
                               {
                                   Name = x.Element("name")?.Value,
                                   Department = x.Element("department")?.Value,
                                   Chair = x.Element("chair")?.Value,
                                   Room = x.Element("room")?.Value,
                                   Students = x.Element("students")?.Value,
                                   lectures = x.Element("lectures")?.Value,
                               })
                               .ToList();
        }
        private void LoadXmlFile()
        {
            try
            {
                _xmlDocument = XDocument.Load(XmlFilePath);
                UpdatePicker();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error loading XML file: {ex.Message}");
                DisplayAlert("Error", $"Failed to load XML file: {ex.Message}", "OK");
            }
        }


        private void UpdatePicker()
        {
            if (_xmlDocument != null)
            {
                attributePicker.Items.Clear();

                var attributes = _xmlDocument.Descendants("teacher").Elements()
                                             .Select(x => x.Name.LocalName)
                                             .Distinct()

                foreach (var attr in attributes)
                {
                    attributePicker.Items.Add(attr);
                }
            }
        }

        private void OnSearchClicked(object sender, EventArgs e)
        {
            if (_xmlDocument == null || attributePicker.SelectedIndex == -1)
            {
                return;
            }

            var selectedAttribute = attributePicker.Items[attributePicker.SelectedIndex];
            var searchPhrase = searchEntry.Text?.ToLower() ?? "";

            var scientists = _savedScientists.Any() ? _savedScientists : GetAllScientists();

            if (!string.IsNullOrWhiteSpace(searchPhrase))
            {
                scientists = scientists.Where(s =>
                {
                    switch (selectedAttribute.ToLower())
                    {
                        case "name":
                            return s.Name?.ToLower().Contains(searchPhrase) == true;
                        case "department":
                            return s.Department?.ToLower().Contains(searchPhrase) == true;
                        case "chair":
                            return s.Chair?.ToLower().Contains(searchPhrase) == true;
                        case "room":
                            return s.Room?.ToLower().Contains(searchPhrase) == true;
                        case "lectures":
                            return s.Lectures?.ToLower().Contains(searchPhrase) == true;
                        case "students":
                            return s.Students?.ToLower().Contains(searchPhrase) == true;
                        default:
                            return false;
                    }
                }).ToList();
            }
            logLabel.Text = $"Found {scientists.Count} results";
            resultsListView.ItemsSource = scientists;
        }

        private void OnSaveClicked(object sender, EventArgs e)
        {
            string savedXmlPath = "C:\\Users\\Home\\Downloads\\Lab2-20231203T221344Z-001\\Lab2\\savedTeachers.xml";

            _savedScientists = resultsListView.ItemsSource as List<Teacher>;

            if (_savedScientists != null && _savedScientists.Any())
            {
                if (File.Exists(savedXmlPath))
                {
                    File.Delete(savedXmlPath);
                }

                var xmlDocument = CreateXmlFromSavedScientists(_savedScientists);

                SaveXmlToFile(xmlDocument, savedXmlPath);

                DisplayAlert("Success", "Results saved successfully.", "OK");
            }
            else
            {
                DisplayAlert("Info", "No results to save.", "OK");
            }
        }

        private void OnClearClicked(object sender, EventArgs e)
            {
                resultLabel.Text = string.Empty;
                attributePicker.SelectedIndex = -1;
                _savedScientists.Clear();
                resultsListView.ItemsSource = null;
            }

        public void SetProcessingStrategy(IXmlProcessingStrategy strategy)
        {
            _currentStrategy = strategy;
        }

        private async void OnTransformButtonClicked(object sender, EventArgs e)
        {
            string xslPath = "C:\Users\Home\Downloads\Lab2-20231203T221344Z-001\Lab2\dateStyles.xslt";
            string savedXmlPath = "C:\\Users\\Home\\Downloads\\Lab2-20231203T221344Z-001\\Lab2\\savedTeachers.xml";

            try
            {
                if (_savedScientists.Any())
                {
                    var xmlDocument = CreateXmlFromSavedScientists(_savedScientists);
                    SaveXmlToFile(xmlDocument, savedXmlPath);

                    string htmlContent = TransformXmlToHtml(savedXmlPath, xslPath);

                    if (!string.IsNullOrEmpty(htmlContent))
                    {
                        SaveHtmlToFile(htmlContent, HtmlFilePath);
                        await DisplayAlert("Success", $"HTML saved to {HtmlFilePath}", "OK");
                    }
                    else
                    {
                        await DisplayAlert("Error", "Failed to generate HTML content.", "OK");
                    }
                }
                else
                {
                    await DisplayAlert("Info", "No saved scientists to transform.", "OK");
                }
            }
            catch (Exception ex)
            {
                await DisplayAlert("Error", $"An error occurred: {ex.Message}", "OK");
            }
        }



        private void SaveHtmlToFile(string htmlContent, string filePath)
        {
            File.WriteAllText(filePath, htmlContent);
        }

        private async void OnItemSelected(object sender, SelectedItemChangedEventArgs e)
        {
            if (e.SelectedItem is Teacher selectedScientist)
            {
                await DisplayAlert("Scientist Details", selectedScientist.Details, "OK");
            }
        }



        private void StrategyPicker_SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedStrategy = strategyPicker.Items[strategyPicker.SelectedIndex];
            _currentStrategy = _strategies[selectedStrategy];
        }


        private async void OnExitButtonClicked(object sender, EventArgs e)
        {
            bool answer = await DisplayAlert("Exit Programme", "Do you really want to exit the programme?", "Yes", "No");
            if (answer)
            {
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
        }


    }
}