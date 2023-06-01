#pragma once
#include <vector>
#include "Plansza.h"
using namespace std;
class BOT : public Plansza {
public:
    BOT(int limit_glebokosci) : limit_glebokosci(limit_glebokosci) {};
    int minimax(Plansza& plansza, int glebokosc, int alfa, int beta, bool maksymalizuj) ; // gracz - maksymalizuj, ai - minimalizuj
    void ruch(Plansza& plansza);
    int getterX()
    {
        return x;
    }
    int getterY()
    {
        return y;
    }

private:
    int x, y;
    int limit_glebokosci;  // maksymalna g³êbokoœæ rekursji
};