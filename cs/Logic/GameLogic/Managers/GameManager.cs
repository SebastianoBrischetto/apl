using cs.Logic.GameLogic.GameElements;
using cs.Communications.HttpRequests;
using cs.GUIConsole;
using cs.Logic.UserLogic;
using cs.Logic.GameLogic.MatchElements;

namespace cs.Logic.GameLogic.Managers
{
     public static class GameManager
    {
        private static Ocean CreateOcean()
        {
            int row = GUI.GetIntInput("Inserisci il numero di righe", 5);
            int column = GUI.GetIntInput("Inserisci il numero di colonne", 5);
            int shipsNumber = GUI.GetIntInput("Inserisci il numero di navi", 1, row * column - 1);
            Ocean ocean = new Ocean(row, column, shipsNumber);
            return ocean;
        }
        public static Ocean CreateOcean(int rows, int columns, int[] shipsCodes)
        {
            Ocean ocean = new Ocean(rows, columns, shipsCodes.Length, shipsCodes);
            return ocean;
        }
        
        public static async Task Login()
        {
            string username = GUI.GetStringInput("Inserisci username: ", 8);
            string password = GUI.GetStringInput("Inserisci password: ", 8);
            Console.WriteLine("Eseguo login");
            string token = await LoginRequest.GetToken(username, password);
            User.Instance.Username = username;
            User.Instance.Password = password;
            User.Instance.Token = token;
            Console.WriteLine($"Creato l'utente:");
            Console.WriteLine(User.Instance.ToString());
        }

        public static async Task InizializeGame(string username, string token)
        {
            string gameType = GUI.GetStringInput("Vuoi giocare contro un bot o contro un avversario online?");
            string gameCode = User.Instance.Username;
            if (gameType == "bot")
            {
                //gameCode = GUI.GetIntInput("Inserisci il livello del bot ", 0, 3);
                gameCode = GUI.GetStringInput("Inserisci il livello de bot (da 0 a 3)");
            }
            Console.WriteLine("Iniziamo!");
            Ocean ocean = CreateOcean();
            string request = GameRequests.JsonCreateGame
                (username, token, gameType, gameCode, ocean.Columns, ocean.Rows, ocean.Ships);
            /*
             Console.WriteLine("Stai per mandare la seguente richiesta:");
            Console.WriteLine(request);
            */
            string serverUrl = "http://localhost:8080/start-game";
            bool response = await GameRequests.StartGame(request, serverUrl);
            if (response)
            {
                MatchManager.PlayerOcean = ocean;
                Console.WriteLine("Stanza creata!");
                bool isBot = gameType == "bot";
                Match.Instance.InizializeMatch(gameCode, ocean.Rows, ocean.Columns, ocean.Ships.Length, true);
                if(isBot)
                {
                    Match.Instance.InizializeMatchBot(gameCode, ocean.Rows, ocean.Columns, ocean.Ships.Length);
                    await MatchManager.InizializeBot();
                }
                else
                {
                    Match.Instance.InizializeMatch(gameCode, ocean.Rows, ocean.Columns, ocean.Ships.Length, true);
                    while (!Match.Instance.ExistOpponent)
                    {
                        await GameRequests.CheckOpponentRequest();
                        Thread.Sleep(3000);
                    }
                }
                MatchManager.Turns(isBot);
            }
            else
            {
                Console.WriteLine("Errore.");
            }
        }

        public static async Task JoinGame()
        {
            bool gameFound = false;
            string code = "";
            while (!gameFound)
            {
                code = GUI.GetStringInput("Inserisci il codice della stanza a cui accedere:");
                gameFound = await GameRequests.CheckGameToJoin(code);
                Console.WriteLine(gameFound);
            }
            //La partita esiste e ho i dati, adesso devo fare richiesta per accedere
            Match.Instance.InizializeMatch(code, Match.Instance.Rows, Match.Instance.Columns, Match.Instance.ShipsCodes.Length, false);
            Ocean ocean = new Ocean(Match.Instance.Rows, Match.Instance.Columns, Match.Instance.ShipsCodes.Length, Match.Instance.ShipsCodes);
            MatchManager.PlayerOcean = ocean;
            string request = GameRequests.JsonJoinGame(code, Match.Instance.Rows, Match.Instance.Columns, ocean.Ships);
            string serverUrl = "http://localhost:8080/join-game";
            bool response = await GameRequests.StartGame(request, serverUrl);
            if (response)
            {
                MatchManager.TurnsJoin();
            }
            else
            {
                Console.WriteLine("Errore.");
            }
        }
    }
}