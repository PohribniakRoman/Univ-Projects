using System;

namespace GeoApp;

interface IGeographicalObject
{
    double X { get; }
    double Y { get; }
    string Name { get; }

    string Description { get; }
}

class GeographicalObject : IGeographicalObject
{
    public double X { get; }
    public double Y { get; }
    public string Name { get; }

    public string Description { get; }

    public GeographicalObject(double x, double y, string name, string description)
    {
        if (name.Length <= 0)
        {
            throw new ArgumentException("Name can not be null",nameof(name));
        }
        if (description.Length <= 0)
        {
            throw new ArgumentException("Name can not be null",nameof(name));
        }

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