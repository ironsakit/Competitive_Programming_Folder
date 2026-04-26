#include <iostream>
using namespace std;

int n = 7, chiamate = 0;
int num_soluzioni = 0;
int griglia[7][7] = {};  // 0 = libera 1 = visitata

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};  // d = 0 (x+0, y-1) sinistra, d = 1 (x+0, y+1) destra, d = 2 (x-1, y+0) su, d = 3 (x+1, y+0) giù

int conta_celle_raggiungibili(int x, int y)  // Questa funzione conta tutte le celle libere connesse tra di loro
{
    // Casi base:
    if (x < 0 || x >= n || y < 0 || y >= n) return 0;  // Se sono fuori dalla griglia ritorno 0 non contano
    if (griglia[x][y] != 0) return 0;  // Se è una cella visitata ritorno 0

    griglia[x][y] = 2;   // La segno come "vista" dalla funzione

    int tot = 1;
    for (int d = 0; d < 4; d++)  // provo tutte le direzioni
    {
        tot += conta_celle_raggiungibili(x + dx[d], y + dy[d]);
    }
    return tot;
}

void search(int x, int y, int passi)
{
    chiamate++;
    // Caso base
    if (x == n-1 && y == n-1)  // siamo arrivati in basso a destra
    {
        if (passi == n*n) num_soluzioni++;
        return;
    }
    for (int d = 0; d < 4; d++)  // Proviamo tutte e 4 le direzioni
    {
        int new_x = x + dx[d];
        int new_y = y + dy[d];
        if (new_x >= 0 && new_x < n &&  // dentro la griglia ?
            new_y >= 0 && new_y < n &&  // dentro la griglia ?
            griglia[new_x][new_y] == 0) // Cella libera
        {
            if (new_x == n-1 && new_y == n-1 && passi < (n*n)-1) continue;
            griglia[new_x][new_y] = 1;  // Segno la cella come visitata

            int celle_libere = n*n - passi - 1; // -1 perchè la prima in alto a sinistra è sempre presa
            bool spezzata = false;

            // Cerco la prima cella libera
            for (int i = 0; i < n && !spezzata; i++)
            {
                for (int j = 0; j < n && !spezzata; j++)
                {
                    if (griglia[i][j] == 0)  // trovata
                    {
                        int reggiungibili = conta_celle_raggiungibili(i, j);
                        // Rimetto la griglia a posto
                        for (int k = 0; k < n; k++)
                            for (int l = 0; l < n; l++)
                                if (griglia[k][l] == 2) griglia[k][l] = 0;
                        if (reggiungibili < celle_libere) spezzata = true;  // se le cella raggiungibili sono meno di quelle totali allora sono spezzate (non posso arrivare alla fine attraversando tutta la griglia)
                    }
                }
            }
            if (!spezzata) search(new_x, new_y, passi+1);  // Vado alla prossima cella, esploro quello che ho dopo
            griglia[new_x][new_y] = 0; // torno indietro come se non li avessi mai visitati (backtracking)
        }
    }
}

int main()
{
    griglia[0][0] = 1;  // La partenza è già visitata
    search(0, 0, 1);  // iniziamo con 1 passo
    cout << num_soluzioni << endl;  // ci mette circa 38 secondi
    cout << chiamate << endl;

    return 0;
}
