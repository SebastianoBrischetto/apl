using cs.Communications;
using cs.Logic.GameLogic.GameElements;
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
            string token = await LoginRequest.GetToken(username, password);
            User.Instance.Username = username;
            User.Instance.Password = password;
            User.Instance.Token = token;
        }

        public static async Task StartGame(string username, string token)
        {
            string gameType = "";
            bool valid = false;
            while (!valid)
            {
                gameType = GUI.GetStringInput
                    ("Digita 'bot' per giocare contro un algoritmo implementato nel server o digita 'player' per giocare contro un altro utente:");
                if (gameType == "bot" || gameType == "player")
                {
                    valid = true;
                }
            }
            string gameCode = User.Instance.Username;
            if (gameType == "bot")
            {
                valid = false;
                while (!valid)
                {
                    gameCode = GUI.GetStringInput("Inserisci il livello di intelligenza del bot: 0 = facile, 1 = intermedio, 2 = difficile, 3 = avanzato: ");
                    switch (gameCode)
                    {
                        case "0":
                            valid = true;
                            break;
                        case "1":
                            valid = true;
                            break;
                        case "2":
                            valid = true;
                            break;
                        case "3":
                            valid = true;
                            break;
                        default:
                            valid = false;
                            break;
                    }
                }
            }
            Ocean ocean = CreateOcean();
            string request = GameRequests.JsonCreateGame
                (username, token, gameType, gameCode, ocean.Columns, ocean.Rows, ocean.Ships);
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