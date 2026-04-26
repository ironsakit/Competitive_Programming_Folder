#include <iostream>
using namespace std;

int n = 7, chiamate = 0;
int num_soluzioni = 0;
int griglia[7][7] = {};  // 0 = libera 1 = visitata

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};  // d = 0 (x+0, y-1) sinistra, d = 1 (x+0, y+1) destra, d = 2 (x-1, y+0) su, d = 3 (x+1, y+0) giù

void search(int x, int y, int passi)
{
    chiamate++;
    // Caso base
    if (x == n-1 && y == n-1)  // siamo arrivati in basso a destra
    {
        if (passi == n*n) num_soluzioni++;
        return;
    }
    if (x == n-1 && y == n-1 && passi < (n*n)-1) return;
    
    bool can_go_up    = (x > 0   && griglia[x-1][y] == 0);
    bool can_go_down  = (x < n-1 && griglia[x+1][y] == 0);
    bool can_go_left  = (y > 0   && griglia[x][y-1] == 0);
    bool can_go_right = (y < n-1 && griglia[x][y+1] == 0);

    // Se la strada Su e Giù è bloccata (da un muro o da celle visitate)
    // ma Sinistra e Destra sono libere, abbiamo tagliato la griglia
    if (!can_go_up && !can_go_down && can_go_left && can_go_right) return;

    // Stessa cosa in orizzontale
    if (!can_go_left && !can_go_right && can_go_up && can_go_down) return;

    for (int d = 0; d < 4; d++)  // Proviamo tutte e 4 le direzioni
    {
        int new_x = x + dx[d];
        int new_y = y + dy[d];
        if (new_x >= 0 && new_x < n &&  // dentro la griglia ?
            new_y >= 0 && new_y < n &&  // dentro la griglia ?
            griglia[new_x][new_y] == 0) // Cella libera
        {
            griglia[new_x][new_y] = 1;  // Segno la cella come visitata
            search(new_x, new_y, passi+1);  // Vado alla prossima cella, esploro quello che ho dopo
            griglia[new_x][new_y] = 0; // torno indietro come se non li avessi mai visitati (backtracking)
        }
    }
}

int main()
{
    griglia[0][0] = 1;  // La partenza è già visitata
    griglia[0][1] = 1;  // visto che è una griglia simmetrica se forzo ad andare a destra basta che poi moltiplico tutto per 2
    search(0, 1, 2);  // iniziamo con 2 passi (forzando di andare a destra)
    cout << num_soluzioni*2 << endl;  // ci mette circa 0.2 secondi (molitplicando per 2 le soluzioni)
    cout << chiamate << endl;

    return 0;
}
