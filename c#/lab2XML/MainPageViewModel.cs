using System.Collections.ObjectModel;

namespace lab2XML;

public class MainPageViewModel : BindableObject
{
    public struct Discepline{
        public string Title{get;set;}
        public string Grade{get;set;}
    }
    public struct StudentItem{
        public string Name {get;set;}
        public string Department {get;set;}
        public string Faculty {get;set;}
        public string Disceplines {get;set;}
        public double AVGGrade {get;set;}
    }

    private ObservableCollection<StudentItem> studentItems;
    public ObservableCollection<StudentItem> StudentItems
    {
        get => studentItems;
        set{
            if(studentItems != value ){
                studentItems = value;
                OnPropertyChanged("StudentItems");
            }
        }
    }

    public MainPageViewModel(){
        StudentItems = new ObservableCollection<StudentItem>{};
        foreach(var student in new XMLDataHandlers().students){
            StudentItems.Add(student);
        };
    }
}