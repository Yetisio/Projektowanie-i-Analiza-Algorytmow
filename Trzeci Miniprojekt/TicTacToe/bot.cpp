#include <vector>
#include <algorithm>
#include <limits>
#include "bot.h"
using namespace std;
int BOT::minimax(Plansza plansza, int glebokosc,int alfa, int beta, bool maksymalizuj)
{
    int aktualnyStanGry = plansza.stanGry();

    if (aktualnyStanGry != 0 || plansza.jestPelna() || glebokosc == 0)
        return aktualnyStanGry;
    if (maksymalizuj) 
    {
        int najlepszaWartosc = INT_MIN;

        for (int i = 1; i < plansza.pobierzRozmiar()+1; i++) 
        {
            for (int j = 1; j < plansza.pobierzRozmiar()+1; j++)
            {
                if (!plansza.jestZajete(i, j))
                {
                    plansza.zmienTure(1);
                    plansza.ustaw(i, j);
                    najlepszaWartosc=max(najlepszaWartosc, minimax(plansza, glebokosc-1, alfa, beta, false));
                    plansza.usun(i, j);
                    alfa = max(alfa, najlepszaWartosc);
                    if (alfa >= beta)
                        return alfa;
                }
            }
        }
        return najlepszaWartosc;
    }
    else 
    {
        int najlepszaWartosc = INT_MAX;

        for (int i = 1; i < plansza.pobierzRozmiar()+1; i++) 
        {
            for (int j = 1; j < plansza.pobierzRozmiar()+1; j++)
            {
                if (!plansza.jestZajete(i, j))
                {
                    plansza.zmienTure(0);
                    plansza.ustaw(i, j);
                    najlepszaWartosc = min(najlepszaWartosc,minimax(plansza, glebokosc-1, alfa, beta, true));
                    plansza.usun(i, j);
                    beta = min(beta, najlepszaWartosc);
                    if (beta <= alfa)
                        return beta;
                }
            }        
        }
        return najlepszaWartosc;
    }
}

void BOT::ruch(Plansza plansza) 
{
   
    int najlepszaWartosc = INT_MAX;
    for (int i = 1; i < plansza.pobierzRozmiar()+1; i++)
    {
        for (int j = 1; j < plansza.pobierzRozmiar()+1; j++)
        {
            if (!plansza.jestZajete(i, j))
            {
                plansza.zmienTure(0);
                plansza.ustaw(i, j);
                int wartoscRuchu = minimax(plansza,glebokosc_max, INT_MIN, INT_MAX, true);
                plansza.usun(i, j);
                if (wartoscRuchu < najlepszaWartosc)
                {
                    x = i;
                    y = j;
                    najlepszaWartosc = wartoscRuchu;

                }
            }
        }
    }
}
int BOT::getterX()
{
    return x;
}
int BOT::getterY()
{
    return y;
}
