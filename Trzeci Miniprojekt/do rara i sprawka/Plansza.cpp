#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Plansza.h"
using namespace std;

Plansza::Plansza(int rozmiar, int do_wygranej, char symbol_gracza) : rozmiar(rozmiar), do_wygranej(do_wygranej), symbol_gracza(symbol_gracza), symbol_BOT(symbol_BOT), pola(rozmiar, vector<char>(rozmiar))
{
    if (rozmiar <3)
    {
        rozmiar = 3;
        pola.resize(rozmiar);
    }
    if (do_wygranej <2)
    {
        do_wygranej = 2;
    }
    if (do_wygranej > rozmiar)
    {
        do_wygranej = rozmiar;
    }
    for (int x = 0; x < rozmiar; x++)
        for (int y = 0; y < rozmiar; y++)
            pola[x][y] = 0;
    
    if (symbol_gracza == 'x')
        symbol_BOT = 'o';
    else if (symbol_gracza == 'o')
        symbol_BOT = 'x';
    else {
        symbol_gracza = 'x';
        symbol_BOT = 'o';
    }
    tura = 1;
}
int Plansza::losujKtoPierwszy()
{
    int pierwszy;
    srand(static_cast<unsigned int>(time(nullptr)));
    pierwszy = rand() % 2;
    return pierwszy;
}
void Plansza::wyswietl()
{
    unsigned char pom = 151;
    // oznaczenia kolumn
    cout << string(5, ' ');
    for (int x = 0; x < rozmiar; x++) 
    {
        if (x < 9)
            cout << setw(1) << x + 1 << "   ";
        else
            cout << setw(2) << x + 1 << "  ";
    }
    cout << '\n';
    for (int y = 0; y < rozmiar; y++) 
    {
        // oznaczenia wierszy, linie pionowe i znaki
        cout << setw(2) << y + 1 << "   ";
        for (int x = 0; x < rozmiar; x++) 
        {
            if (pola[x][y] == 0)
                cout << ' ';
            else
                cout << pola[x][y];
            if (x < rozmiar - 1)
                cout << " | ";
        }
        // linie poziome
        if (y < rozmiar - 1) {
            cout << "\n    ";
            for (int i = 0; i < rozmiar - 1; i++)
                cout << string(3, '=')<<'#';
            cout << string(3, '=');
           
        }
        cout << '\n';
    }
    cout << "\n\n";
}



void Plansza::ustaw(int x, int y) 
{
    if (x >= 1 && x <= rozmiar && y >= 1 && y <= rozmiar)
    {
        if (jestTuraGracza())
            pola[x-1][y-1] = symbol_gracza;
        else
            pola[x-1][y-1] = symbol_BOT;
    }
        
}

void Plansza::usun(int x, int y) 
{
        pola[x-1][y-1] = 0;
}

void Plansza::resetuj() 
{
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            pola[i][j] = 0;
        }
    }
    tura = 1;
}

char Plansza::sprawdz(int x, int y) 
{
    if (x >= 1 && x <= rozmiar && y >= 1 && y <= rozmiar)
        return pola[x-1][y-1];
    else
        return 0;
}

bool Plansza::jestZajete(int x, int y) 
{
    
   if (x >= 1 && x <= rozmiar && y >= 1 && y <= rozmiar )
       return pola[x-1][y-1];
  else
       return false;
}

bool Plansza::jestPelna() 
{
    for (int i = 1; i < rozmiar+1; i++) 
    {
        for (int j = 1; j < rozmiar+1; j++) 
        {
            if (jestZajete(i, j))
                continue;
            else
                return false;
        }
    }
    return true;
}



int Plansza::stanGry() 
{
    int licznik_gracza, licznik_bota;
    // Sprawdzanie wygranej w wierszach
    for (int i = 0; i < rozmiar; i++) 
    {
        licznik_bota = licznik_gracza = 1;
            for (int j = 0; j < rozmiar-1; j++)
            {
                if (pola[i][j] == pola[i][j+1])
                {
                    if (pola[i][j] == symbol_gracza)
                        licznik_gracza++;
                    else if (pola[i][j] == symbol_BOT)
                        licznik_bota++;
                    if (licznik_gracza == do_wygranej)
                        return 1;
                    if (licznik_bota == do_wygranej)
                        return -1;
                }
            }
            
     }

    // Sprawdzanie wygranej w kolumnach
    for (int j = 0; j < rozmiar; j++) 
    {
        licznik_bota = licznik_gracza = 1;
        for (int i = 0; i < rozmiar-1; i++) 
        {
                if (pola[i][j] == pola[i + 1][j])
                {
                    if (pola[i][j] == symbol_gracza)
                        licznik_gracza++;
                    else if (pola[i][j] == symbol_BOT)
                        licznik_bota++;
                    if (licznik_gracza == do_wygranej)
                        return 1;
                    if (licznik_bota == do_wygranej)
                        return -1;
                }
            
        }
    }

    // Sprawdzanie wygranej na przek¹tnych
    for (int x = 1; x < rozmiar - do_wygranej + 1; x++) 
    {
        licznik_gracza = licznik_bota = 1;
        for (int y = 0; y < (rozmiar - x - 1); y++) 
        {
            if (pola[y][x + y] == pola[y + 1][x + y + 1])
            {
                if (pola[y][x + y] == symbol_gracza)
                    licznik_gracza++;
                else if (pola[y][x + y] == symbol_BOT)
                    licznik_bota++;
                if (licznik_gracza == do_wygranej)
                    return 1;
                if (licznik_bota == do_wygranej)
                    return -1;
            }
        }
    }
    for (int x = 0; x < rozmiar - do_wygranej + 1; x++) 
    {
        licznik_gracza = licznik_bota = 1;
        for (int y = 0; y < (rozmiar - x - 1); y++) 
        {
            if (pola[x + y][y] == pola[x + y + 1][y + 1]) 
            {
                if (pola[x + y][y] == symbol_gracza)
                    licznik_gracza++;
                else if (pola[x + y][y] == symbol_BOT)
                    licznik_bota++;
                if (licznik_gracza == do_wygranej)
                    return 1;
                if (licznik_bota == do_wygranej)
                    return -1;
            }
        }
    }
    for (int x = 0; x < rozmiar - do_wygranej + 1; x++) 
    {
        licznik_gracza = licznik_bota = 1;
        for (int y = 0; y < (rozmiar - x - 1); y++) 
        {
            if (pola[rozmiar - 1 - y][x + y] == pola[rozmiar - 1 - (y + 1)][x + y + 1]) 
            {
                if (pola[rozmiar - 1 - y][x + y] == symbol_gracza)
                    licznik_gracza++;
                else if (pola[rozmiar - 1 - y][x + y] == symbol_BOT)
                    licznik_bota++;
                if (licznik_gracza == do_wygranej)
                    return 1;
                if (licznik_bota == do_wygranej)
                    return -1;
            }
        }
    }
    for (int x = 1; x < rozmiar - do_wygranej + 1; x++) 
    {
        licznik_gracza = licznik_bota = 1;
        for (int y = 0; y < (rozmiar - x - 1); y++) 
        {
            if (pola[rozmiar - 1 - x - y][y] == pola[rozmiar - x - y - 2][y + 1]) 
            {
                if (pola[rozmiar - 1 - x - y][y] == symbol_gracza)
                    licznik_gracza++;
                else if (pola[rozmiar - 1 - x - y][y] == symbol_BOT)
                    licznik_bota++;
                if (licznik_gracza == do_wygranej)
                    return 1;
                if (licznik_bota == do_wygranej)
                    return -1;
            }
        }
    }    
    return 0;
}
