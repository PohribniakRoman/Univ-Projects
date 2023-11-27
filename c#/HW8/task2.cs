using System;

class Email
{
    public String Theme { get; set; }
    public String From { get; set; }
    public String To { get; set; }
}

class Logger
{
    public Action<string> LogAction { get; set; }

    public Logger()
    {
        LogAction = (message) => Console.WriteLine("Log: " + message);
    }

    public void Log(string message)
    {
        LogAction(message);
    }
}

class EmailSender
{
    private Logger logger;

    public EmailSender(Logger logger)
    {
        this.logger = logger;
    }

    public void Send(Email email)
    {
        // ... sending...
        logger.Log("Email from '" + email.From + "' to '" + email.To + "' sent!");
    }
}
class Program
{
    static void Main(string[] args)
    {
        Email email_1 = new Email()
        {
            From = "Me",
            To = "Mike",
            Theme = "Hi how are you?"
        };
        Email email_2 = new Email()
        {
            From = "Mike",
            To = "Me",
            Theme = "hello text asd"
        };
        Email email_3 = new Email()
        {
            From = "123",
            To =
        "user",
            Theme = "test1123!"
        };
        Email email_4 = new Email()
        {
            From = "Roman",
            To = "Andrew",
            Theme = "Loading files!"
        };
        Email email_5 = new Email()
        {
            From = "Me",
            To = "Mike",
            Theme = "Access denied!"
        };
        Email email_6 = new Email()
        {
            From = "Gaben",
            To =
        "Fork",
            Theme = "2023.9.11"
        };

        Logger logger = new Logger();

        EmailSender email_sender = new EmailSender(logger);
        email_sender.Send(email_1);
        email_sender.Send(email_2);
        email_sender.Send(email_3);
        email_sender.Send(email_4);
        email_sender.Send(email_5);
        email_sender.Send(email_6);
    }
}