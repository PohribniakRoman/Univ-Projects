public abstract class MessageFactory
{
    public abstract IMessage CreateMessage();
}

public class HelloMessageFactory : MessageFactory
{
    public override IMessage CreateMessage()
    {
        return new HelloMessage();
    }
}

public class GoodbyeMessageFactory : MessageFactory
{
    public override IMessage CreateMessage()
    {
        return new GoodbyeMessage();
    }
}

public interface IMessage
{
    string GetMessage();
}

public class HelloMessage : IMessage
{
    public string GetMessage() => "Hello!";
}

public class GoodbyeMessage : IMessage
{
    public string GetMessage() => "Goodbye!";
}

public class CompositeMessage : IMessage
{
    private List<IMessage> messages = new List<IMessage>();

    public void Add(IMessage message)
    {
        messages.Add(message);
    }

    public string GetMessage()
    {
        return string.Join(" and ", messages.Select(m => m.GetMessage()));
    }
}

class Program
{
    static void Main()
    {
        MessageFactory helloFactory = new HelloMessageFactory();
        MessageFactory goodbyeFactory = new GoodbyeMessageFactory();

        var helloMessage = helloFactory.CreateMessage();
        var goodbyeMessage = goodbyeFactory.CreateMessage();

        var compositeMessage = new CompositeMessage();
        compositeMessage.Add(helloMessage);
        compositeMessage.Add(goodbyeMessage);

        Console.WriteLine(compositeMessage.GetMessage());

        Console.Read();
    }
}