generare chiave ssh => https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent#generating-a-new-ssh-key <br />
associare chiave ssh ad account git => https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account#adding-a-new-ssh-key-to-your-account <br />
nella pagina del repository cliccare su code, selezionare ssh e copiare la stringa <br />
usare il comando: git clone stringaCopiata <br />
<h2>Casi d'uso</h2>
<h4>client login/register</h4>
client(login con username e password) ->                                                            python    <br />
client(error / ok e codice di auth)                                                              <- python    <br />

<h4>init partita vs bot</h4>
client(richiede partita vs bot (codice auth, id bot, +dati init game)) ->                           golang (username)  -> python    <br />
client(ok (socket)/ error (posiz navi sbagliata-bot non conosciuto - auth sbagliato))            <- golang (auth code) <- python    <br />
<b>(game)</b> <br />

<h4>init partita vs player</h4>
client1(richiede creazione partita (codice auth, dati init game, game id)) ->                       golang (username)  -> python    <br />
client1(ok (socket)/ errore (griglia sbagliata / auth sbagliato)) <-                                golang (auth code) <- python    <br />
client1 (standby finche non viene ricontattato da golang)    <br />
<b>(game)</b>

<h4>join partita vs player</h4>
client2(richiede join partita esistente (codice auth, game id)) ->                                  golang (username)  -> python    <br />
client2(ok (socket, grid data) / errore (se non esiste il codice / auth sbagliato)) <-              golang (auth code) <- python    <br />
client2(init grid (grid data) e la popola) ->                                                       golang    <br />
client2(ok / errore) <-                                                                             golang    <br />
<b>(game)</b>

<h4>game</h4>
while(!game over){     <br />
    client1(coords da colpire) ->                     golang     <br />
    client1(ok / error) <-                            golang -> client2(hit(coords))     <br />
                                                      golang <- client2(coords da colpire)     <br />
    client1(hit(coords)) <-                           golang -> client2(ok / error)     <br />
}     <br />
                                                      golang ->                                     python(id1, id2, who won)     <br />
                                                      golang <-                                     python(score id1, score id2)     <br />
client1(who won - new score)                       <- golang -> client2(who won - new score)     <br />
client1(ok e chiude)                               -> golang <- client2(ok e chiude)     <br />
<b>close socket</b>     <br />

<h2>Messaggi json</h2>
<h4>json init game</h4>
{     <br />
    "codice_auth": ricevuto da python login     <br />
    "columns:     <br />
    "rows":     <br />
    "game_type": bot / player     <br />
    "code": identificativo bot/ codice accesso a instance game     <br />
    "ships": [     <br />
        {     <br />
        "init_x": 0,     <br />
        "init_y": 0,     <br />
        "ship_type": 2,     //destroyer (2pos): 2, submarine (3pos) 3, cruiser (3pos) 1, battleship(4pos) 4, carrier(5pos) 5     <br />
        "direction": 1      //up 0, right 1, down 2, left 3     <br />
        },     <br />
    ]     <br />
}     <br />

<h4>json hit client</h4>
{     <br />
    x:     <br />
    y:     <br />
}     <br />
<h4>json golang response to hit</h4>
{     <br />
    x:     <br />
    y:     <br />
    is_hit_on_ship:     <br />
    sunk_ship_type:     <br />
    is_game_over:     <br />
}     <br />
