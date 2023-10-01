namespace BookShelfHW1;
class IEGenerator
{
    public static List<Entry> Item()
    {
        return new()
        {
            new Entry { Placeholder = "Title" },
            new Entry { Placeholder = "Description" },
            new Entry { Placeholder = "Country of origin" },
            new Entry { Placeholder = "Price" }
        };
    }

    public static List<Entry> Book()
    {
        var list = Item();
        list.Add(new Entry { Placeholder = "Authors" });
        list.Add(new Entry { Placeholder = "Publishing" });
        list.Add(new Entry { Placeholder = "Pages" });
        return list;
    }
    public static List<Entry> Product()
    {
        var list = Item();
        list.Add(new Entry { Placeholder = "Expires" });
        list.Add(new Entry { Placeholder = "Measurement" });
        list.Add(new Entry { Placeholder = "Amount" });
        return list;
    }
}