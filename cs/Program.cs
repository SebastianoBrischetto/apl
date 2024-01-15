//QUELLO DA TESTARE
using cs.Logic.GameLogic.Managers;
using cs.Logic.UserLogic;
namespace cs
{
    static class Program
    {
        private static async Task Main()
        {
            await GameManager.Login();
            Console.WriteLine(
                "Vuoi creare una nuova partita (start) o partecipare ad una partita già avviata (join)?: ");
            string mode = Console.ReadLine();
            if (mode == "start")
            {
                await GameManager.InizializeGame(User.Instance.Username, User.Instance.Token);
            }
            else
            {
                await GameManager.JoinGame();
            }
        }
    }
}