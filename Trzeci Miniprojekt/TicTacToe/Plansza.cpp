#include <vector>
#include <iostream>
#include <iomanip>
#include "Plansza.h"
using namespace std;

Plansza::Plansza(int rozmiar, int do_wygranej, char symbol_gracza) : rozmiar(rozmiar), do_wygranej(do_wygranej), symbol_gracza(symbol_gracza), symbol_BOT(symbol_BOT), pola(rozmiar, vector<char>(rozmiar))
{
    if (rozmiar <= 2)
    {
        rozmiar = 3;
        pola.resize(rozmiar);
    }
    if (do_wygranej <= 1)
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

void Plansza::wyswietl() 
{
    for (int i = 0; i < rozmiar; i++) 
    {
        for (int j = 0; j < rozmiar; j++) 
        {
            cout << pola[i][j];
            if (j < rozmiar - 1)
                cout << " | ";
        }
        cout << endl;
        if (i < rozmiar - 1) {
            for (int k = 0; k < rozmiar * 4 - 2; k++)
                cout << "-";
            cout << endl;
        }
    }
}


void Plansza::ustaw(int x, int y) 
{
    if (x >= 0 && x < rozmiar && y >= 0 && y < rozmiar)
    {
        if (jestTuraGracza())
            pola[x][y] = symbol_gracza;
        else
            pola[x][y] = symbol_BOT;
    }
        
}

void Plansza::usun(int x, int y) 
{
        pola[x][y] = 0;
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
    if (x >= 0 && x < rozmiar && y >= 0 && y < rozmiar)
        return pola[x][y];
    else
        return 0;
}

bool Plansza::jestZajete(int x, int y) 
{
    if (x >= 0 && x < rozmiar && y >= 0 && y < rozmiar )
        return true;
    else
        return false;
}

bool Plansza::jestPelna() 
{
    for (int i = 0; i < rozmiar; i++) 
    {
        for (int j = 0; j < rozmiar; j++) 
        {
            if (pola[i][j] == 0)
                return false;
        }
    }
    return true;
}

bool Plansza::jestTuraGracza()  
{
    return tura;
}

int Plansza::stanGry() 
{
    int licznik_gracza, licznik_bota;
    // Sprawdzanie wygranej w wierszach
    for (int i = 0; i < rozmiar; i++) 
    {
        licznik_bota = licznik_gracza = 1;
            char symbol = pola[i][0];
            if (symbol == 0)
                continue;
            for (int j = 0; j < rozmiar; j++)
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
        char symbol = pola[0][j];
        if (symbol == 0)
            continue;
        for (int i = 0; i < rozmiar; i++) 
        {
            if (pola[i][j] == symbol_gracza)
            
                licznik_gracza++;
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
    /*char symbol = pola[0][0];
    if (symbol != ' ') 
    {
        bool wygrana = true;
        for (int i = 1; i < rozmiar; i++)
        {
            if (pola[i][i] != symbol) 
            {
                wygrana = false;
                break;
            }
        }
        if (wygrana)
            return symbol == symbol_gracza ? 1 : 2;
    }

    symbol = pola[0][rozmiar - 1];
    if (symbol != ' ') 
    {
        bool wygrana = true;
        for (int i = 1; i < rozmiar; i++)
        {
            if (pola[i][rozmiar - 1 - i] != symbol)
            {
                wygrana = false;
                break;
            }
        }
        if (wygrana)
            return symbol == symbol_gracza ? 1 : 2;
    }
    */
    // Sprawdzanie remisu
    if (jestPelna())
        return 0;

    // Gra w trakcie
    return -1;
}
