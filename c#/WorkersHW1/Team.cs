using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WorkerApp;

class Team
{

    private string name;

    private List<Worker> workers;

    public Team(string name)
    {
        this.name = name;
        workers = new();
    }

    public void AddWorker(Worker worker)
    {
        workers.Add(worker);
    }

    public string GetInfo() => new StringBuilder().AppendLine("Команда - " + name).AppendJoin("\n", workers.Select((worker, i) => (i + 1) + ". " + worker.Name)).ToString();
    public string GetFullInfo() => new StringBuilder().AppendLine("Команда - " + name).AppendJoin("\n", workers.Select((worker, i) => (i + 1) + ". Name - " + worker.Name + "\n\t Position - " + worker.Position + "\n\t WorkDay - " + worker.WorkDay)).ToString();
}