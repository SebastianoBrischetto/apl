﻿using System.Text;
using System.Text.Json;

namespace cs.Communications
{
    public static class LoginRequest
    { 
        public static async Task<string> GetToken(string username, string password) 
        {
            string url = "http://localhost:5000/api/authorize"; 
            string jsonPayload = "{\"username\": \"" + username + "\", \"password\": \"" + password + "\"}";
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    var content = new StringContent(jsonPayload, Encoding.UTF8, "application/json");
                    HttpResponseMessage response = await client.PostAsync(url, content);
                    if (response.IsSuccessStatusCode)
                    {
                        string responseBody = await response.Content.ReadAsStringAsync();
                        var jsonResponse = JsonSerializer.Deserialize<Dictionary<string, string>>(responseBody);
                        if (jsonResponse.ContainsKey("access_token"))
                        {
                            string accessToken = jsonResponse["access_token"];
                            return accessToken;
                        }
                        Console.WriteLine("Token di accesso non trovato nella risposta.");
                    }
                    else
                    {
                        Console.WriteLine("Errore nella richiesta: " + response.StatusCode);
                    }
                }
                catch (HttpRequestException e)
                {
                    Console.WriteLine("Errore durante la richiesta: " + e.Message);
                }
                return null;
            }
        }
    }
}