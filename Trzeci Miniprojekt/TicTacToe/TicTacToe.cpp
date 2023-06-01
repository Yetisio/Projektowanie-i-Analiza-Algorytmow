#include <iostream>
#include <vector>
#include <string>
#include "Plansza.h"
#include "bot.h"

using namespace std;

int main()
{
    int rozmiar, do_wygranej, glebokosc;
    char symbol_gracza = 'x', symbol_bot = 'o';

    cout << "Podaj rozmiar planszy: ";
    cin >> rozmiar;
    cout << "Podaj iloscc znakow w rzedzie do wygranej: ";
    cin >> do_wygranej;
    cout << "glebokosc rekursji AI: ";
    cin >> glebokosc;
    Plansza plansza(rozmiar, do_wygranej, symbol_gracza);
    BOT bot(glebokosc);
    char odp = 'n';
    // gra
    do
    {
        plansza.resetuj();
        plansza.wyswietl();


        while (plansza.stanGry() == 0 || !plansza.jestPelna())
        {  // dopoki wygrana lub remis
            // ruch gracza
            if (plansza.jestTuraGracza())
            {
                int x, y;
                cout << "twoj ruch!\n";
                do
                {
                    // wczytywanie x
                    do
                    {
                        x = 0;
                        cout << "x > ";
                        cin >> x;
                        if (x < 1 || x > rozmiar)
                            cout << "# x wybierz z przedzialu [1," << rozmiar << "]\n";
                    } while (x < 1 || x > rozmiar);

                    // wczytywanie y
                    do
                    {
                        y = 0;
                        cout << "y > ";
                        cin >> y;
                        cin.clear();
                        if (y < 1 || y > rozmiar)
                            cout << "# y wybierz z przedzialu [1," << rozmiar << "]\n";
                    } while (y < 1 || y > rozmiar);

                    // zajete pole
                    if (plansza.jestZajete(x, y))
                    {
                        cout << "pole (" << x << "," << y << ") jest zajete przez ";
                        if (plansza.sprawdz(x, y) == symbol_gracza)
                            cout << "gracza (" << symbol_gracza << ")";
                        else
                            cout << "komputer (" << symbol_bot << ")";

                        cout << '\n';
                    }
                } while (plansza.jestZajete(x, y) || x < 1 || x > rozmiar || y < 1 || y > rozmiar);
                plansza.ustaw(x, y);
                plansza.zmienTure(0);
            }
            // ruch ai
            else
            {
                cout << "komputer wykonuje ruch... ";
                bot.ruch(plansza);
                plansza.ustaw(bot.getterX(), bot.getterY());
                plansza.zmienTure(1);
            }

            plansza.wyswietl();

            // sprawdzenie stanu gry
            if (plansza.jestPelna() && plansza.stanGry() == 0)
                cout << "remis!";
            else if (plansza.stanGry() != 0)
            {
                cout << "koniec gry! wygrywa ";
                if (!plansza.jestTuraGracza())
                    cout << "gracz (" << symbol_gracza << ")";
                else
                    cout << "komputer (" << symbol_bot << ")";
            }
            cout << '\n';
        }
            cout << "Czy chcesz zagrac ponownie? (t/n): ";
            cin >> odp;
    }while (odp == 't');
}
      
  
    
 
    


