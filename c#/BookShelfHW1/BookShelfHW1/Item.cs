namespace BookShelfHW1;


class Item{
	 string title;
	 string description;
	 string origin;
	double price;

    public Item(string title,string description,string origin,double price){
        this.title = title;
        this.description = description;
        this.origin = origin;
        this.price = price;
    }

    public virtual List<string> GetInfo() => new List<string>(){title,description,origin,price > 0 ? price.ToString():"Wrong Input"};

}
