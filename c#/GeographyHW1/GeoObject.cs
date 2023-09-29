namespace GeoApp;

class GeoObject
{
    double X, Y;
    string Name, Description;

    public GeoObject(double x, double y, string name, string description)
    {
        X = x;
        Y = y;
        Name = name;
        Description = description;
    }

    public virtual string GetInfo()
    {
        return $"Name: {Name}\n\tCoords: X - {X} / Y - {Y};\n\tDescription: {Description}\n";
    }
}