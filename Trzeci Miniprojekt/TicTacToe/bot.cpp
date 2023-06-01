#include <vector>
#include "bot.h"
using namespace std;


int BOT::minimax(Plansza& plansza, int glebokosc, int alfa, int beta, bool maksymalizuj)  
{
    if (glebokosc >= limit_glebokosci || plansza.stanGry() != 0) 
    {
        if (plansza.stanGry() == 1)
            return -10;
        else if (plansza.stanGry() == 2)
            return 10;
        else
            return 0;
    }

    if (maksymalizuj) {
        int najlepszaWartosc = -1000;

        for (int i = 0; i < plansza.pobierzRozmiar(); i++) 
        {
            for (int j = 0; j < plansza.pobierzRozmiar(); j++) {
                int wiersz = i + 1;

                int kolumna = j + 1;
                plansza.zmienTure(1);
                plansza.ustaw(wiersz, kolumna);

                int wartoscRuchu = minimax(plansza, glebokosc + 1, alfa, beta, false);

                plansza.usun(wiersz, kolumna);

                najlepszaWartosc = max(najlepszaWartosc, wartoscRuchu);
                alfa = max(alfa, najlepszaWartosc);

                if (alfa >=  beta)
                    return alfa;
            }
            return najlepszaWartosc;
        }
        
    }
    else 
    {
        int najlepszaWartosc = 1000;

        for (int i = 0; i < plansza.pobierzRozmiar(); i++) 
        {
            for (int j = 0; j < plansza.pobierzRozmiar(); j++) 
            {
                int wiersz = i + 1;
                int kolumna = j + 1;
                plansza.zmienTure(0);
                plansza.ustaw(wiersz, kolumna);

                int wartoscRuchu = minimax(plansza, glebokosc + 1, alfa, beta, false);

                plansza.usun(wiersz, kolumna);

                najlepszaWartosc = max(najlepszaWartosc, wartoscRuchu);
                beta = max(beta, najlepszaWartosc);

                if (beta <= alfa)
                    return beta;
            }
            return najlepszaWartosc;
        }
    }
}

void BOT::ruch(Plansza& plansza) 
{
    int najlepszaWartosc = 1000;
    int pom;
    pair<int, int> najlepszyRuch;

    for (int i = 0; i < plansza.pobierzRozmiar(); i++)
    {
        for (int j = 0; j < plansza.pobierzRozmiar(); j++)
        {
            int wiersz = i + 1;
            int kolumna = j + 1;
            plansza.zmienTure(0);
            plansza.ustaw(wiersz, kolumna);

            int wartoscRuchu = minimax(plansza, 0, -1000, 1000, false);

            plansza.usun(wiersz, kolumna);

            if (wartoscRuchu < najlepszaWartosc) 
            {
                najlepszaWartosc = wartoscRuchu;
                najlepszyRuch = make_pair(wiersz, kolumna);
            }
        }

      
    }
}