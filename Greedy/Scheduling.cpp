#include <bits/stdc++.h>
using namespace std;

/* Utilizzare Greedy algorithm per lo scheduling è una ottima soluzione (con i giusti accorgimenti)
 *
 * L'obiettivo è ottenere il maggior numero di eventi che non si sovrappongono (non conta quali ma quanti quindi ci possono essere diverse combinazioni)
 * Come si risolve?
 *
 * L'algoritmo Greedy sceglie a ogni passo l'evento che finisce prima tra quelli disponibili
 *
 * Implementazione:
 * 1. Salva ogni evento come {fine, inizio} così il sort ordinerà in ordine crescente secondo la "fine"
 * 2. Scorri gli eventi ordinati e seleziona il prossimo solo se inizia dopo la fine dell'ultimo preso
 *
 * O(n log n) per il sort e O(n) per la selezione
 */

int main()
{
    int n;  // prendo il numero di eventi in input
    cin>>n;

    vector<pair<int,int>> eventi(n); // {fine, inizio}

    for (int i = 0; i < n; i++)  // Prendo il tempo di inizio e fine di ogni evento
    {
        int in, fi;
        cin>>in>>fi;
        eventi[i] = {fi,in};  // Salvo prima la fine e poi l'inizio
    }

    sort(eventi.begin(),eventi.end());  // Ordino secondo la fine in modo tale da avere prima quello che finisce prima

    int count_eventi = 0, fine_precedente = 0;  // quanto finisce l'ultimo che ho scelto

    for (auto [fine, inizio] : eventi)
    {
        if (inizio >= fine_precedente)  // Controllo se non sono sovrapposti
        {
            count_eventi++;
            fine_precedente = fine;  // Mi salvo il tempo di fine dell'ultimo evento
        }
    }

    cout<<count_eventi<<endl;

    return 0;
}

/*
4

1 3

2 5

3 9

6 8

output: 2
*/