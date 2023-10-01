namespace BookShelfHW1;
class Book : Item{
    int Pages;
    string AuthorList,Publishing;
    public Book(string title,string description,string origin,double price,string authorList,string publishing,int pages) : base(title,description,origin,price){
        Pages = pages;
        AuthorList = authorList;
        Publishing = publishing;
    }

    public override List<string> GetInfo(){
        List<string> value = base.GetInfo();
        value.Add($"Pages: {(Pages > 0?Pages : "Wrong Input")}\nAuthor:{AuthorList}\nPublishing:{Publishing}");
        return value;
    } 
}