namespace BookShelfHW1;



public partial class MainPage : ContentPage
{
	ScrollView View = new ScrollView();
	VerticalStackLayout Components = new VerticalStackLayout();

	List<Entry> CurrentList = new();

	int SelectedIndex = -1;

	Button button = new Button
	{
		Text = "Add Product",
		VerticalOptions = LayoutOptions.Center,
		HorizontalOptions = LayoutOptions.Center,
	};

	public MainPage()
	{
		View.Content = Components;
		button.Clicked += Submit;

		var itemsList = new List<string>();
		itemsList.Add("Defult Item");
		itemsList.Add("Book");
		itemsList.Add("Product");
		
		Picker picker = new Picker
		{
			Title = "Select item type",
			ItemsSource = itemsList
		};
		picker.SelectedIndexChanged += PickIndex;

		Components.Children.Add(picker);
		Content = View;

		InitializeComponent();
	}

	public async void Submit(object sender, EventArgs e)
	{
		List<string> newItem = new();
		int fieldsFilled = 4;
		if (SelectedIndex != 0) fieldsFilled = 7;

		CurrentList.ForEach(field =>
		{
			if (field.Text.Length > 0)
			{
				newItem.Add(field.Text);
				field.Text = "";
			};
		});
		if (fieldsFilled == newItem.Count)
		{
			double price = -1;
			double.TryParse(newItem[3], out price);
			if (SelectedIndex == 0)
			{
				var listItem = new Item(newItem[0], newItem[1], newItem[2], price);
				ItemList.AddEntry(listItem.GetInfo());
			}
			if (SelectedIndex == 1)
			{
				int pages = -1;
				int.TryParse(newItem[6], out pages);
				var listItem = new Book(newItem[0], newItem[1], newItem[2], price, newItem[4], newItem[5], pages);
				ItemList.AddEntry(listItem.GetInfo());
			}
			if (SelectedIndex == 2)
			{
				int amount = -1;
				int.TryParse(newItem[6], out amount);
				var listItem = new Product(newItem[0], newItem[1], newItem[2], price, newItem[4], newItem[5], amount);
				ItemList.AddEntry(listItem.GetInfo());
			}

			await DisplayAlert("Success!", "Product has been added.", "ok");
		}
		else
		{
			await DisplayAlert("Failed!", "Fill all gaps!", "ok");
		}
	}
	public void PickIndex(object sender, EventArgs e)
	{
		var picker = (Picker)sender;
		SelectedIndex = picker.SelectedIndex;
		if (SelectedIndex != -1)
		{
			Components.Children.Remove(button);
			CurrentList.ForEach(entry => Components.Children.Remove(entry));
			if (SelectedIndex == 0) CurrentList = IEGenerator.Item();
			if (SelectedIndex == 1) CurrentList = IEGenerator.Book();
			if (SelectedIndex == 2) CurrentList = IEGenerator.Product();
			DisplayList();
			Components.Children.Add(button);
		}
	}

	void DisplayList()
	{
		CurrentList.ForEach(entry => Components.Children.Add(entry));
	}
}

