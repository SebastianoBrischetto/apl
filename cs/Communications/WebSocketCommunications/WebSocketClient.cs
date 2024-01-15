using System;
using System.Threading.Tasks;
using WebSocketSharp;

namespace cs.Communications.WebSocketCommunications;
class WebSocketClient
{
    private WebSocket webSocket;

    // Metodo per connettersi al server WebSocketCommunications in modo asincrono
    public async Task ConnectToWebSocketAsync(string serverUrl)
    {
        try
        {
            // Inizializza un nuovo oggetto WebSocketCommunications
            webSocket = new WebSocket(serverUrl);

            // Configura la gestione degli eventi
            webSocket.OnOpen += (sender, e) =>
            {
                Console.WriteLine("Connesso al server WebSocketCommunications.");
            };

            webSocket.OnMessage += (sender, e) =>
            {
                Console.WriteLine($"Messaggio ricevuto: {e.Data}");
                // Puoi aggiungere qui la logica per gestire il messaggio ricevuto
            };

            webSocket.OnClose += (sender, e) =>
            {
                Console.WriteLine("Connessione chiusa.");
                // Aggiungi la logica per gestire la riconnessione automatica qui se necessario
            };

            // Effettua la connessione asincrona al server WebSocketCommunications
            await Task.Run(() => webSocket.Connect());
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Errore durante la connessione: {ex.Message}");
            // Gestisci l'errore in modo appropriato
        }
    }

    // Metodo per inviare un messaggio al server WebSocketCommunications in modo asincrono
    public async Task SendMessageAsync(string message)
    {
        try
        {
            if (webSocket != null && webSocket.IsAlive)
            {
                // Invia il messaggio al server in modo asincrono
                await Task.Run(() => webSocket.Send(message));
            }
            else
            {
                Console.WriteLine("La connessione non è attiva.");
                // Puoi gestire la riconnessione qui o informare l'utente di riconnettersi
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Errore durante l'invio del messaggio: {ex.Message}");
            // Gestisci l'errore in modo appropriato
        }
    }

    // Metodo per disconnettersi dal server WebSocketCommunications in modo asincrono
    public async Task DisconnectAsync()
    {
        try
        {
            if (webSocket != null && webSocket.IsAlive)
            {
                // Chiudi la connessione WebSocketCommunications in modo asincrono
                await Task.Run(() => webSocket.Close());
            }
            else
            {
                Console.WriteLine("La connessione non è attiva.");
                // Puoi gestire la situazione in cui la connessione non è attiva
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Errore durante la disconnessione: {ex.Message}");
            // Gestisci l'errore in modo appropriato
        }
    }
}
