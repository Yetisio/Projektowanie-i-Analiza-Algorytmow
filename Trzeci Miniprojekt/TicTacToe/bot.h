#pragma once
#include <vector>
#include "Plansza.h"
using namespace std;
class BOT : public Plansza {
public:
    BOT(int glebokosc_max) : glebokosc_max(glebokosc_max) {};
    int minimax(Plansza plansza, int gleboksoc, int alfa, int beta, bool maksymalizuj) ; // gracz - maksymalizuj, ai - minimalizuj
    void ruch(Plansza plansza);
    int getterX();
    int getterY();
private:
    int x, y;
    int glebokosc_max;
};