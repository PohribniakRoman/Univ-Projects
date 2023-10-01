namespace BookShelfHW1;


class Item{
	 string Title { get; }
	 string Description { get; }
	 string Origin { get; }
	double Price { get; }

    public Item(string title,string description,string origin,double price){
        Title = title;
        Description = description;
        Origin = origin;
        Price = price;
    }

    public virtual List<string> GetInfo(){
        List<string> data = new(){Title,Description,Origin,Price > 0 ? Price.ToString():"Wrong Input"};
        return data;
    }
}
