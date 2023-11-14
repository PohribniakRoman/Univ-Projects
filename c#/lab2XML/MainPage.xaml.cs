using System;
using System.Xml;
using System.Xml.Xsl;

namespace lab2XML;

public partial class MainPage : ContentPage
{
	MainPageViewModel mainPageViewModel;
	XMLDataHandlers dataHandlers;
	public MainPage()
	{
		InitializeComponent();
		BindingContext = mainPageViewModel = new MainPageViewModel();
		dataHandlers = new();
	}
	void Search_Submit(Object sender,EventArgs e)
	{
		if (Linq.IsChecked)
		{
			var data = from student in mainPageViewModel.StudentItems.AsEnumerable()
					   where student.Name.Contains(string.IsNullOrWhiteSpace(Name.Text) ? "" : Name.Text)
					   where student.Department.Contains(string.IsNullOrWhiteSpace(Department.Text) ? "" : Department.Text)
					   where student.Faculty.Contains(string.IsNullOrWhiteSpace(Faculty.Text) ? "" : Faculty.Text)
					   where student.AVGGrade > (string.IsNullOrWhiteSpace(Grade.Text) ? 0 : double.Parse(Grade.Text))
					   orderby student.AVGGrade ascending
					   select student;

			MyCollectionViews.ItemsSource = data;
		}

		if (Sax.IsChecked)
		{
			dataHandlers = new XMLDataHandlers();
			MyCollectionViews.ItemsSource = dataHandlers.SAX_Search(new MainPageViewModel.StudentItem
			{
				Name = string.IsNullOrWhiteSpace(Name.Text) ? "" : Name.Text,
				Department = string.IsNullOrWhiteSpace(Department.Text) ? "" : Department.Text,
				Faculty = string.IsNullOrWhiteSpace(Faculty.Text) ? "" : Faculty.Text,
				AVGGrade = string.IsNullOrWhiteSpace(Grade.Text) ? 0 : double.Parse(Grade.Text),
				Disceplines = "",
			});
		}

		if (Dom.IsChecked)
		{
			dataHandlers = new XMLDataHandlers();
			MyCollectionViews.ItemsSource = dataHandlers.DOM_Search(new MainPageViewModel.StudentItem
			{
				Name = string.IsNullOrWhiteSpace(Name.Text) ? "" : Name.Text,
				Department = string.IsNullOrWhiteSpace(Department.Text) ? "" : Department.Text,
				Faculty = string.IsNullOrWhiteSpace(Faculty.Text) ? "" : Faculty.Text,
				AVGGrade = string.IsNullOrWhiteSpace(Grade.Text) ? 0 : double.Parse(Grade.Text),
				Disceplines = "",
			});
		}
	}
	void Clear_Fields(Object sender,EventArgs e){
		Name.Text = "";
		Faculty.Text = "";
		Department.Text = "";
		Grade.Text = "";
	}
	void Export_HTML(Object sender,EventArgs e){
		XslCompiledTransform xct = new XslCompiledTransform();
		xct.Load(@"C:\Users\Roman\Desktop\univ-projects\c#\lab2XML\assets\styles.xsl");
		XmlDocument newDoc = dataHandlers.CreateXmlDocument();
		newDoc.Save(@"C:\Users\Roman\Desktop\univ-projects\c#\lab2XML\assets\curent.xml");
		xct.Transform(@"C:\Users\Roman\Desktop\univ-projects\c#\lab2XML\assets\curent.xml",@"C:\Users\Roman\Desktop\univ-projects\c#\lab2XML\assets\export.html");
	}
}

