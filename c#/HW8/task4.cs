using System.Runtime.CompilerServices;

interface IPrice
{
    void SetPrice(double price);
}

interface IColor
{
    void SetColor(string color);
}

interface ISize
{
    void SetSize(double size);
}

interface IDiscount
{
    void ApplyDiscount(double discount);
}

interface IPromocode
{
    void ApplyPromocode(string promocode);
}

class Book : IPrice, IDiscount
{
    private double price;
    private double discount;

    public void SetPrice(double price)
    {
        this.price = price;
    }

    public void ApplyDiscount(double discount)
    {
        this.discount = discount;
        if (discount > 0)
        {
            price -= price * (discount / 100);
        }
    }
}

class Clothing : IPrice, IDiscount, IPromocode, IColor, ISize
{
    private double price;
    private double discount;
    private string? promocode;
    private double size;
    private string color;

    public void SetColor(string color)
    {
        this.color = color;
    }

    public void SetSize(double size)
    {
        this.size = size;
    }

    public void SetPrice(double price)
    {
        this.price = price;
    }

    public void ApplyDiscount(double discount)
    {
        this.discount = discount;
        if (discount > 0)
        {
            price -= price * (discount / 100);
        }
    }

    public void ApplyPromocode(string promocode)
    {
        this.promocode = promocode;
    }
}