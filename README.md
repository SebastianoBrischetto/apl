generare chiave ssh => https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent#generating-a-new-ssh-key <br />
associare chiave ssh ad account git => https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account#adding-a-new-ssh-key-to-your-account <br />
nella pagina del repository cliccare su code, selezionare ssh e copiare la stringa <br />
usare il comando: git clone stringaCopiata <br />

client(login con username e password) ->                                                            python
client(error / ok e codice di auth)                                                              <- python

//partita bot
client(richiede partita vs bot (codice auth, id bot, +dati init game)) ->                           golang (username)  -> python
client(ok (socket)/ error (posiz navi sbagliata-bot non conosciuto - auth sbagliato))            <- golang (auth code) <- python
(game)

//partita player (init)
client1(richiede creazione partita (codice auth, dati init game, game id)) ->                       golang (username)  -> python
client1(ok (socket)/ errore (griglia sbagliata / auth sbagliato)) <-                                golang (auth code) <- python
client1 (standby finche non viene ricontattato da golang)
(game)

//partita player (join)
client2(richiede join partita esistente (codice auth, game id)) ->                                  golang (username)  -> python
client2(ok (socket, grid data) / errore (se non esiste il codice / auth sbagliato)) <-              golang (auth code) <- python
client2(init grid (grid data) e la popola) ->                                                       golang
client2(ok / errore) <-                                                                             golang
(game)

//game
while(!game over){
    client1(coords da colpire) ->                     golang
    client1(ok / error) <-                            golang -> client2(hit(coords))
                                                      golang <- client2(coords da colpire)
    client1(hit(coords)) <-                           golang -> client2(ok / error)
}
                                                      golang ->                                     python(id1, id2, who won)
                                                      golang <-                                     python(score id1, score id2)
client1(who won - new score)                       <- golang -> client2(who won - new score)
client1(ok e chiude)                               -> golang <- client2(ok e chiude)

close socket


//json init game
{
    "codice_auth": ricevuto da python login
    "columns:
    "rows":
    "game_type": bot / player
    "code": identificativo bot/ codice accesso a instance game
    "ships": [
        {
        "init_x": 0,
        "init_y": 0,
        "ship_type": 2,     //destroyer (2pos): 2, submarine (3pos) 3, cruiser (3pos) 1, battleship(4pos) 4, carrier(5pos) 5
        "direction": 1      //up 0, right 1, down 2, left 3
        },
    ]
}

//json hit client
{
    x:
    y:
}
//json golang
{
    x:
    y:
    is_hit_on_ship:
    sunk_ship_type:
    is_game_over:
}