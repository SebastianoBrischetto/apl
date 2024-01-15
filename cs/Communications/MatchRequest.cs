using System.Text;
using cs.Logic.GameLogic.MatchElements;
using cs.Logic.GameLogic.MatchElements.Structs;
using cs.Logic.UserLogic;
using Newtonsoft.Json;

namespace cs.Communications;
public static class MatchRequest
{
    public static async Task CheckPlayersTurn()
    {
        try
        {
            string url = "http://localhost:8080/get-game?game_id=" + Match.Instance.Code;
            using (HttpClient client = new HttpClient())
            {
                HttpResponseMessage response = await client.GetAsync(url);
                if (response.IsSuccessStatusCode)
                {
                    string responseData = await response.Content.ReadAsStringAsync();
                    if (responseData.Contains("\"p1_turn\":true"))
                    {
                        Console.WriteLine("Turno del giocatore 1");
                        Match.Instance.IsPlayerOneTurn = true;
                    }
                    else if (responseData.Contains("\"p1_turn\":false"))
                    {
                        Match.Instance.IsPlayerOneTurn = false;
                        Console.WriteLine("Turno del giocatore 2");
                    }
                    else
                    {
                        Console.WriteLine("Errore nella creazione della partita");
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
     public static async Task SendMoves(string gameId, int x, int y)
    {
        using (HttpClient client = new HttpClient())
        {
            string url = "http://localhost:8080/do-move";
            var data = new
            {
                username = User.Instance.Username,
                access_token = User.Instance.Token,
                game_id = gameId,
                coords = new
                {
                    x,
                    y
                }
            };
            string jsonData = JsonConvert.SerializeObject(data);
            Console.WriteLine("Invio la seguente mossa:");
            Console.WriteLine(jsonData);
            client.DefaultRequestHeaders.Accept.Add
                (new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));
            var content = new StringContent(jsonData, Encoding.UTF8, "application/json");
            try
            {
                HttpResponseMessage response = await client.PostAsync(url, content);
                if (response.IsSuccessStatusCode)
                {
                    Match.Instance.PlayersLastMoves.Add(new Move { X = x, Y = y });
                    if (Match.Instance.PlayersLastMoves.Count > 0)
                    {
                        Console.WriteLine("Mosse precedenti:");
                        foreach (Move move in Match.Instance.PlayersLastMoves)
                        {
                            Console.WriteLine(move.X);
                            Console.WriteLine(move.X);
                        }
                    }
                    Match.Instance.IsPlayerOneTurn = true;
                    string jsonResponse = await response.Content.ReadAsStringAsync();
                    Console.WriteLine(jsonResponse);
                    dynamic responseObject = JsonConvert.DeserializeObject(jsonResponse);
                    if (responseObject.is_occupied != null)
                    {
                        Match.Instance.LastMoveHit = responseObject.is_occupied;
                    }
                    else
                    {
                        Match.Instance.IsGameOver = true;
                    }
                    if (responseObject.last_move != null)
                    {
                        Match.Instance.OpponentLastMove= new Move {X = responseObject.last_move.x, Y = responseObject.last_move.y};
                        Console.WriteLine(Match.Instance.OpponentLastMove.X);
                        Console.WriteLine(Match.Instance.OpponentLastMove.Y);
                    }
                }
                else
                {
                    Console.WriteLine("ERRORE DURANTE L'INVIO DELLA MOSSA");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Errore durante l'invio della richiesta HTTP: {ex.Message}");
            }
        }
    }

   public static async Task<bool> GetBotMoves()
    {
        string url = $"http://localhost:8080/get-game?game_id={User.Instance.Username}";

        using (HttpClient client = new HttpClient())
        {
            try
            {
                HttpResponseMessage response = await client.GetAsync(url);
                if (response.IsSuccessStatusCode)
                {
                    string jsonResponse = await response.Content.ReadAsStringAsync();
                    var result = JsonConvert.DeserializeObject<dynamic>(jsonResponse);
                    if (result != null)
                    {
                        List<Move> moves = null;
                        List<OccupiedCoordinates> occupiedCoords = null;
                        bool p1Turn = false;
                        Move lastMove = new Move();
                        if (result.moves != null && result.moves.moves != null)
                        {
                            moves = JsonConvert.DeserializeObject<List<Move>>(result.moves.moves.ToString());
                            Match.Instance.Bot.Moves = moves;
                        }

                        if (result.moves != null && result.moves.occupied_coords != null)
                        {
                            occupiedCoords = JsonConvert.DeserializeObject<List<OccupiedCoordinates>>(result.moves.occupied_coords.ToString());
                            Match.Instance.Bot.OccupiedCoordinates = occupiedCoords;
                        }

                        if (result.p1_turn != null)
                        {
                            p1Turn = result.p1_turn;
                            Match.Instance.IsPlayerOneTurn = p1Turn;
                        }

                        if (result.last_move != null)
                        {
                            lastMove = JsonConvert.DeserializeObject<Move>(result.last_move.ToString());
                            Match.Instance.OpponentLastMove = lastMove;
                        }
                        return true;
                    }
                    Console.WriteLine("Risposta JSON nulla o non conforme alla struttura attesa.");
                    return false;
                }
                Console.WriteLine($"Errore nella richiesta HTTP. Codice di stato: {response.StatusCode}");
                return false;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Errore durante la richiesta HTTP: {ex.Message}");
                return false;
            }
        }
    }
}
    