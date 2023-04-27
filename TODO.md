# Obiettivo del gioco 
Percorso breve con un alto punteggio.

**Player**: snake o
**Uscita** (fine del gioco): _

**Punti iniziali**: 1000
**Punti finali**: 1000 + punti delle monete possedute - n. passi eseguiti

## Mosse possibili
N (Nord), S (Sud), E (East), O (Ovest), ogni mossa costa 1 punto

## Ostacoli:
* mura (#): non possono essere attraversate
* monete ($): valgono 10 punti e aumentano di uno la lunghezza dello snake
* imprevisti (!): dimezzano il numero di monete raccolte e la lunghezza dello snake
* trapano (T): inizialmente a 0, una volta raccolto 3 usi disponibili, distrugge le pareti anche i bordi del gioco ma essi non possono essere superati, ogni utilizzo 
decrementa di uno, se a 0 non si può attraversare la parete.

Ogni ostacolo una volta raccolto scompare dal labirinto.

- [ ] Se la testa incontra una parte del corpo, allora viene persa la parte compresa tra la coda e il punto di incontro, e di conseguenza vengono perse le relative monete.
- [ ] Vicoli ciechi: torna indietro e perde tutti i pezzi tranne la testa e pezzo dopo.

## INPUT:

- [X] leggere il numero di colonne (intero M)
- [X] leggere il numero di righe (intero N)
- [X] N operazioni di lettura delle righe del piano di gioco

## OUTPUT:

- [X] scrivere SOLO un'unica linea con le mosse del miglior percorso con solo lettere maiuscole ( es. ESSSSSSSEEEEEEEEEENNNNNNNEEEEESSSSEE )  

# Due modalità: interattiva e AI.

## Modalità interattiva:

- [X] richiesta all'utente qual è la mossa successiva
- [X] aggiornamento e visualizzazione del piano di gioco e del punteggio ad ogni mossa
- [X] verificare che la mossa sia valida (non attraversi i muri)

## Modalità AI:

- [ ] calcolare il percorso migliore
- [ ] visualizzare a schermo il percorso trovato
- [ ] al termine della partita visualizzare la stringa con tutte le mosse eseguite

Strategie a scelta:
- Random: snake si muove in maniera casuale ad ogni passo finché non viene trovata la via di uscita
- Sempre a destra: consente di uscire sempre da qualunque labirinto appoggiando una mano su una parete e proseguire seguendo la parete.
- Libera scelta

- [ ] il programma deve compilare e funzionare correttamente sulle 3 piattaforme (Windows, Linux, Mac)
