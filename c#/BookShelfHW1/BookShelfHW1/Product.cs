namespace BookShelfHW1;
class Product : Item{
    int Amount;
    string Expires,Measurement;
    public Product(string title,string description,string origin,double price,string expires,string measurement,int amount) : base(title,description,origin,price){
        Expires = expires;
        Measurement = measurement;
        Amount = amount;
    }

    public override List<string> GetInfo(){
        List<string> value = base.GetInfo();
        value.Add($"Amount: {(Amount > 0?Amount : "Wrong Input")}\nExpires:{Expires}\nMeasurement:{Measurement}");
        return value;
    } 
}