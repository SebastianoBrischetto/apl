<<<<<<< Updated upstream
﻿//QUELLO DA TESTARE
using cs.Logic.GameLogic.Managers;
=======
﻿using cs.Logic.GameLogic.Managers;
>>>>>>> Stashed changes
using cs.Logic.UserLogic;
namespace cs
{
    static class Program
    {
        private static async Task Main()
        {
            await GameManager.Login();
<<<<<<< Updated upstream
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
=======
            bool valid = false;
            while(!valid){
                Console.WriteLine(
                    "Digita 'start' per avviare una nuova partita o digira 'join' per accedere ad una partita già avviata:");
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
                        Console.WriteLine("Inserisci un valore valido!");
                        valid = true;
                        break;
                }
>>>>>>> Stashed changes
            }
        }
    }
}