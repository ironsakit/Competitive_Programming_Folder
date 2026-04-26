#include <algorithm>
#include <iostream>
using namespace std;
#include <vector>

vector<int> subset = {};

void search_subset(int k, int n)
{
    if (k == n)
    {
        cout << "{ ";
        for (auto i : subset) cout << i << " ";
        cout << "}" << endl;
    }else
    {
        search_subset(k + 1, n);  // Scelta 1: Non metto il numero k nel subset
        subset.push_back(k);  // Scelta 2: Metto il numero k nel subset
        search_subset(k + 1, n);
        subset.pop_back();  // Backtracking: tolgo k per il prossimo ramo
    }
}

void search_subset_binary(int k)  // 25 = 11001 --> corrisponde al subset {0, 3, 4} perchè i bit sono accesi nelle posizioni 0 3 4 ovvero 11001 & 00001, 11001 & 01000, 11001 & 10000.
{
    for (int b = 0; b < (1<<k); b++)  // i << k vuol dire 2 alla k
    {
        vector<int>sub;
        for (int i = 0; i < k; i++)
        {
            if (b & (1 << i)) sub.push_back(i);  // Faccio la AND con il numero in binario e 2 alla i in modo tale da capire quale posizione dovo mettere
        }
        cout << "{ ";
        for (auto i : sub) cout << i << " ";
        cout << "}" << endl;
    }
}

vector<int> permutation;

/* Qui il ragionamento è:
 * - prendo i e lo aggiungo nella permutazione
 * - esploro tutto ciò che viene dopo aver scelto i
 * - rilascio i e lo tolgo dalla permutazione
 *
 * Quindi dopo aver esplorato tutti i rami che iniziano con i, devo poter usare i di nuovo in una posizione diversa
 * questo si chiama BACKTRACKING.
 */

void permuations(int n, vector<bool>& chosen)
{
    if (permutation.size() == n)  // Quando ho raggiungo tutte le mie permutazioni le stampo (passo base)
    {
        cout << "{ ";
        for (auto i : permutation) cout << i << " ";
        cout << "}" << endl;
    }else
    {
        for (int i = 0; i < n; i++)
        {
            if (chosen[i]== true) continue;  // se già è presente nella permutazione lo salto
            chosen[i] = true;   // sennò lo segno come preso
            permutation.push_back(i);  // Lo prendo effettivamente
            permuations(n, chosen);  // esploro altre combinazioni
            chosen[i] = false;  // una volta esplorate tutte le combinazioni con i lo levo dagli elementi presi
            permutation.pop_back();  // lo levo quindi effettivamente dalle combinazioni
        }
    }
}

int column[4] = {}, diag1[7] = {}, diag2[7] = {};  // Il numero di diagonale è dato da 2n - 1 ad esempio una scacchiera 4x4 ha 7 diagonali
int n = 4, solutions = 0;

/* il problema ci richiede di trovare il numero di soluzioni in cui possiamo posizionare tutte le N regine nella scacchiera NxN senza che
 * si attacchino a vicenda
 * Come procediamo? Dobbiamo innanzitutto capire che una regina attacca tutto ciò che si trova sulla stessa:
 * - riga
 * - colonna
 * - diagonale (destra e sinistra)
 *
 * Usiamo Backtracking:
 * - Piazziamo le regina una per riga, dall'alto vero il basso
 * - Per ogni riga troviamo tutte le combinazioni possibili
 * - Se la casella è sicura, mettiamo la regina (mettiamo 1)
 * - Se non troviamo nessuna casella valida torniamo indietro
 * - Se arriviamo a mettere tutte le N regine (siamo arrivati all'ultima riga y == n) aumentiamo il numero di soluzioni trovate
 *
 * Come controlliamo delle posizioni occupate?
 * - column[x] controlla se la colonna è già occupata
 * - diag1[x+y] controlla se la diagonale (che sale da sinistra verso destra) è già occupata
 * - diag2[x-y + n-1] controlla la diagonale (che scende da sinistra verso destra)
 */

void search_queens(int y)
{
    if (y == n)
    {
        solutions++;
        return;
    }
    for (int x = 0; x < n; x++)
    {
        if (column[x] || diag1[x+y] || diag2[x-y + n-1]) continue;
        column[x] = diag1[x+y] = diag2[x-y + n-1] = 1;
        search_queens(y+1);
        column[x] = diag1[x+y] = diag2[x-y + n-1] = 0;
    }
}

int main()
{
    cout << "\nSottoinsiemi:\n\nMetodo 1:\n";
    search_subset(0, 3);
    cout << "\nMetodo 2:\n";
    search_subset_binary(3);

    vector<bool> chosen(3, false);
    cout << "\nPermutazioni:\n\nMetodo 1:\n";
    permuations(3, chosen);

    cout << "\nMetodo 2:\n";

    // Invece se voglio tutte le permutazioni usando semplicemente la libreria standard di C++
    vector <int> permutazioni;
    for (int i = 0; i < 3; i++) permutazioni.push_back(i);  // Bisogna partire dalla permutazione in ordine crescente {0, 1, 2,...,n-1}

    do
    {
        cout << "{ ";
        for (auto i : permutazioni) cout << i << " ";
        cout << "}" << endl;
    }while (next_permutation(permutazioni.begin(), permutazioni.end()));

    search_queens(n);
    cout << "\nQuante soluzioni abbiamo se vogliamo " << n << " regine: " << solutions << endl;

    return 0;
}