using cs.Logic.GameLogic.Managers;
using cs.Logic.UserLogic;

namespace cs
{
    static class Program
    {
        private static async Task Main()
        {
            await GameManager.Login();
            bool valid = false;
            while (!valid)
            {
                Console.WriteLine(
                    "Digita 'start' per creare una nuova partito o digita 'join' per accedere ad una partita già creata:");
                string mode = Console.ReadLine();
                switch (mode)
                {
                    case "start":
                        await GameManager.StartGame(User.Instance.Username, User.Instance.Token);
                        valid = true;
                        break;
                    case "join":
                        await GameManager.JoinGame();
                        valid = true;
                        break;
                    default:
                        Console.WriteLine("Inserisci un'opzione valida!");
                        break;
                }
            }
        }
    }
}