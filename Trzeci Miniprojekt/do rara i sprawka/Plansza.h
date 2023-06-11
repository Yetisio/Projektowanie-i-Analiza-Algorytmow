#pragma once
#include <vector>
using namespace std;
class Plansza {
public:
    Plansza() {};
    Plansza(int rozmiar, int do_wygranej, char gracz);
    int pobierzRozmiar() const
    {
        return rozmiar; 
    }
    void zmienTure(bool gracz) 
    { 
        gracz ? tura = 1 : tura = 0; 
    }
    int losujKtoPierwszy();
    void wyswietl();                               // wyœwietlanie planszy
    void ustaw(int x, int y);                            // ustawianie pola na planszy
    void usun(int x, int y);                             // usuwanie pola z planszy
    void resetuj();                                      // resetowanie planszy
    char sprawdz(int x, int y);                    // sprawdzanie znaku na polu
    bool jestZajete(int x, int y);                 // sprawdzanie czy pole jest zajête
    bool jestPelna();                              // sprawdzanie czy plansza jest pe³na
    bool jestTuraGracza()const                      // sprawdzanie czy jest tura gracza
    {
        return tura;
    }                         
    int stanGry();                                 // sprawdzanie stanu gry

private:
    int rozmiar;                                          // rozmiar planszy (kwadratowej)
    int do_wygranej;                                      // iloœæ znaków w rzêdzie do wygranej
    bool tura;                                            // tura, 1 - gracz, 0 - AI
    char symbol_gracza, symbol_BOT;                        // X/O
   vector<vector<char>> pola;                             // pola (X lub O)
};