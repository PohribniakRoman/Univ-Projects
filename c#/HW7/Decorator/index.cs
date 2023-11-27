using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public interface IChristmasTree
{
    string Decorate();
}

public class ChristmasTree : IChristmasTree
{
    public string Decorate()
    {
        return "Christmas tree";
    }
}

public abstract class TreeDecorator : IChristmasTree
{
    protected IChristmasTree tree;

    public TreeDecorator(IChristmasTree tree)
    {
        this.tree = tree;
    }

    public virtual string Decorate()
    {
        return tree.Decorate();
    }
}

public class OrnamentsDecorator : TreeDecorator
{
    public OrnamentsDecorator(IChristmasTree tree) : base(tree) { }

    public override string Decorate()
    {
        return base.Decorate() + " with Ornaments";
    }
}

public class GarlandDecorator : TreeDecorator
{
    public GarlandDecorator(IChristmasTree tree) : base(tree) { }

    public override string Decorate()
    {
        return base.Decorate() + " with Garland";
    }
}

class Program
{
    static void Main(string[] args)
    {
        IChristmasTree tree = new ChristmasTree();

        Console.WriteLine(tree.Decorate());

        tree = new OrnamentsDecorator(tree);

        Console.WriteLine(tree.Decorate());

        tree = new GarlandDecorator(tree);

        Console.WriteLine(tree.Decorate());

        Console.Read();
    }
}