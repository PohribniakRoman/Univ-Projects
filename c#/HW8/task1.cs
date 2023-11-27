class Item { }
class OrderItemManager
{
    private List<Item>? itemList;

    public void AddItem(Item item) {/*...*/}
    public void DeleteItem(Item item) {/*...*/}
    public List<Item> GetItems() { return itemList; }
    public int GetItemCount() { return itemList.Count; }
    public void CalculateTotalSum() {/*...*/}
}

class OrderDataManager
{
    public void Load() {/*...*/}
    public void Save() {/*...*/}
    public void Update() {/*...*/}
    public void Delete() {/*...*/}
}

class Order
{
    private OrderItemManager itemManager;
    private OrderDataManager dataManager;

    public Order()
    {
        itemManager = new OrderItemManager();
        dataManager = new OrderDataManager();
    }

    public void PrintOrder() {/*...*/}
    public void ShowOrder() {/*...*/}
}