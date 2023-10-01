namespace BookShelfHW1;



public partial class ItemList : ContentPage
{
	ScrollView View = new ScrollView();

	static List<List<string>> list = new(){
	 	new(){"Title","Description","Country of origin","Price","Additional info"}
	};

	static Grid grid = new Grid
	{
		RowDefinitions =
			{
				new RowDefinition(),
				new RowDefinition(),
				new RowDefinition(),
				new RowDefinition(),
				new RowDefinition(),
			},
		ColumnDefinitions =
			{
				new ColumnDefinition(),
				new ColumnDefinition(),
				new ColumnDefinition(),
				new ColumnDefinition(),
				new ColumnDefinition()
			}
	};

	public ItemList()
	{
		View.Content = grid;

		Draw();

		Content = grid;

		InitializeComponent();
	}

	public static void AddEntry(List<string> newItem)
	{
		list.Add(newItem);
		Draw();
	}

	static void Draw()
	{
		for (int i = 0; i < list[list.Count - 1].Count; i++)
		{
			Label label = new Label
			{
				Text = list[list.Count - 1][i],
				HorizontalOptions = LayoutOptions.Center,
				VerticalOptions = LayoutOptions.Center
			};
			grid.Add(label, i, list.Count - 1);
		}
		if (list[list.Count - 1].Count == 4)
		{
			Label label = new Label
			{
				Text = "No Additional info",
				HorizontalOptions = LayoutOptions.Center,
				VerticalOptions = LayoutOptions.Center
			};
			grid.Add(label, 4, list.Count - 1);
		}
		// grid.Add(new BoxView { Color = Colors.Teal }, j, list.Count - 1);
		// grid.Add(new Label { Text = value }, j, list.Count - 1);
		// return value;
	}

}

