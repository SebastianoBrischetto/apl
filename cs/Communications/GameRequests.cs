using System.Text;
using cs.Logic.GameLogic.GameElements;
using cs.Logic.GameLogic.MatchElements;
using cs.Logic.UserLogic;
using Newtonsoft.Json;
using Formatting = System.Xml.Formatting;   
    
namespace cs.Communications
{
    public static class GameRequests
    { 
        public static async Task<bool> StartGame(string jsonRequest, string serverUrl)
        {
            using (HttpClient client = new HttpClient())
            {
                
                client.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));
                var content = new StringContent(jsonRequest, Encoding.UTF8, "application/json");
                Console.WriteLine("Invio richiesta...");
                Console.WriteLine("");
                try
                {
                    HttpResponseMessage response = await client.PostAsync(serverUrl, content);
                    if (response.IsSuccessStatusCode)
                    {
                        Console.WriteLine("Partita avviata!");
                        Console.WriteLine(response);
                        return true;
                    }
                    Console.WriteLine($"Errore nella richiesta. Codice di stato: {response.StatusCode}");
                    return false;
                }
                catch (Exception e)
                {
                    Console.WriteLine("ECCEZIONE.\nErrore nella richiesta: " + e);
                    Console.WriteLine(e.Message);
                    return false;
                }
            }
        }
        //Metodo per formattare i dati in un JSON da passare come contenuto della richiesta POST
        public static string JsonCreateGame(string username, string token, string gameType, string gameCode, int columns, int rows, Ship[] ships)
        {
            if (gameType == "bot")
            {
                var requestData = new
                {
                    username,
                    access_token = token,
                    game_type = gameType,
                    game_data = new
                    {
                        game_code = gameCode,
                        columns,
                        rows,
                        ships = ships.Select(s => new
                        {
                            init_x = s.X,
                            init_y = s.Y,
                            ship_type = s.ShipCode,
                            direction = s.Direction
                        }).ToArray()
                    }
                };
                return JsonConvert.SerializeObject(requestData, (Newtonsoft.Json.Formatting)Formatting.Indented);
            }
            else
            {
                var requestData = new
                {
                    username,
                    access_token = token,
                    game_type = gameType,
                    game_data = new
                    {
                        columns,
                        rows,
                        ships = ships.Select(s => new
                        {
                            init_x = s.X,
                            init_y = s.Y,
                            ship_type = s.ShipCode,
                            direction = s.Direction
                        }).ToArray()
                    }
                };
                return JsonConvert.SerializeObject(requestData, (Newtonsoft.Json.Formatting)Formatting.Indented);
            }
        }
        public static string JsonJoinGame(string gameCode, int columns, int rows, Ship[] ships)
        { 
            var requestData = new
            {
                username = User.Instance.Username,
                access_token = User.Instance.Token,
                game_type = "player",
                game_data = new
                {
                    game_code = gameCode,
                    columns,
                    rows,
                    ships = ships.Select(s => new
                    {
                        init_x = s.X,
                        init_y = s.Y,
                        ship_type = s.ShipCode,
                        direction = s.Direction
                    }).ToArray()
                }
                };
                return JsonConvert.SerializeObject(requestData, (Newtonsoft.Json.Formatting)Formatting.Indented);
            
        }
        public static async Task CheckOpponentRequest()
        {
            try
            {
                string url = "http://localhost:8080/get-game?game_id=" + User.Instance.Username;
                using (HttpClient client = new HttpClient())
                {
                    HttpResponseMessage response = await client.GetAsync(url);
                    if (response.IsSuccessStatusCode)
                    {
                        string responseData = await response.Content.ReadAsStringAsync();
                        if (responseData.Contains("\"p2_ocean\""))
                        {
                            Match.Instance.ExistOpponent = true;
                            Console.WriteLine("Avversario trovato!");
                        }
                        else
                        {
                            Console.WriteLine("Aspettando un avversario...");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"Errore nella richiesta: {response.StatusCode} - {response.ReasonPhrase}");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Errore durante l'esecuzione del metodo: {ex.Message}");
            }
        }
        
        public static async Task<bool> CheckGameToJoin(string code)
        {
            try
            {
                string url = "http://localhost:8080/get-game?game_id=" + code;
                using (HttpClient client = new HttpClient())
                {
                    HttpResponseMessage response = await client.GetAsync(url);
                    if (response.IsSuccessStatusCode)
                    {
                        //la partita esiste
                        string responseData = await response.Content.ReadAsStringAsync();
                        // Deserializza la risposta JSON in un oggetto dynamic
                        dynamic jsonResponse = JsonConvert.DeserializeObject(responseData);
                        // Estrai i valori desiderati
                        int columns = jsonResponse.p1_ocean.columns;
                        int rows = jsonResponse.p1_ocean.rows;
                        int[] shipsCodes = jsonResponse.ships.ToObject<int[]>();
                        Match.Instance.Rows = rows;
                        Match.Instance.Columns = columns;
                        Match.Instance.ShipsCodes = shipsCodes;
                        Console.WriteLine(Match.Instance.Rows);
                        Console.WriteLine(Match.Instance.Columns);
                        Console.WriteLine(Match.Instance.ShipsCodes);
                        
                        return true;
                    }
                        //la partita non esiste
                        Console.WriteLine("Partita non provata, inserisci un codice valido!");
                        return false;
                    
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Partita non provata, inserisci un codice valido!");
                return false;
            }
        }
    }
    
}