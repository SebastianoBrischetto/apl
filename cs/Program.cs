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
                    "Enter 'start' to initiate a new game or 'join' to join an existing game:");
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
                        Console.WriteLine("Enter a valid input!");
                        break;
                }
            }
        }
    }
}
