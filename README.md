<h2>Url a relazione del progetto</h2>
https://docs.google.com/document/d/1x28nWMvptK7OQaTk-UT0Xvis_2igfthmgekdMrAC4Ts/edit#heading=h.kik26115jhhz

<h2>Avvio applicazione</h2>
Da CLI portarsi nella directory del progetto (./apl)
<ul>
<li>Per avviare il server eseguire (necessita di docker): </br>docker compose up</li>
<li>Per avviare un client: </li>
<ol>
<li>Build immagine: docker build -t cs-client ./client</li>
<li>Per ogni client da avviare eseguire: docker run --rm -it --network="host" cs-client</li>
</ol>
</ul>
