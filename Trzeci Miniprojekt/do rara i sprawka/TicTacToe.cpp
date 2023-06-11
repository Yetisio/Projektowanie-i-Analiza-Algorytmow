#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Plansza.h"
#include "bot.h"

using namespace std;

int main()
{
    int rozmiar=3, do_wygranej=0,glebokosc_m=0;
    char symbol_gracza=0, symbol_bot = 0;
    char odp = 'n';
    int wybor=0;
    Plansza* plansza = nullptr;
    BOT* bot = nullptr;
    while (wybor != 4)
    {
        system("cls");
        cout << " ====  M E N U  =====\n";
        cout << "1. Ustawienia gry\n";
        cout << "2. Nowa gra aby wybrac nalezy przejsc przez punkt pierwszy\n";
        cout << "3. Krotka instrukcja jak grac\n";
        cout << "4. Wyjscie\n";
        cout << endl << "Wpisz numer polecnia z listy menu ---> ";
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            
                cout << "\nPodaj rozmiar planszy ( minimum 3x3 ): ";
                cin >> rozmiar;
                cout << "Podaj ilosc znakow w jednej linii do wygranej: ";
                cin >> do_wygranej;
                cout << "Wybierz znak gracza jakim chcesz grac ( x/o ): ";
                cin >> symbol_gracza;
                if (rozmiar < 3)
                {
                    rozmiar = 3;
                }
                if (do_wygranej < 2)
                {
                    do_wygranej = 2;
                }
                if (do_wygranej > rozmiar)
                {
                    do_wygranej = rozmiar;
                }
                if (symbol_gracza == 'x')
                    symbol_bot = 'o';
                else
                    symbol_bot = 'x';
                cout << "Glebokosc algorytmu: ";
                cin >> glebokosc_m;
                
            
            
            break;
        case 2:
            bot = new BOT(glebokosc_m);
            plansza = new Plansza(rozmiar, do_wygranej, symbol_gracza);
            do
            {
                plansza->resetuj();
                plansza->wyswietl();
                plansza->zmienTure(plansza->losujKtoPierwszy());
                while (plansza->stanGry() == 0 && !plansza->jestPelna()) //do remisu lub wygranej
                {
                    // ruch gracza
                    if (plansza->jestTuraGracza())
                    {
                        int x, y;
                        cout << "Ruch gracza\n";
                        do
                        {
                            // wczytywanie x
                            x = 0;
                            cout << "x > ";
                            cin >> x;
                            if (x < 1 || x > rozmiar)
                                cout << "X wybierz z przedzialu [1," << rozmiar << "]\n";


                            // wczytywanie y
                            y = 0;
                            cout << "y > ";
                            cin >> y;
                            if (y < 1 || y > rozmiar)
                                cout << "Y wybierz z przedzialu [1," << rozmiar << "]\n";


                            // zajete pole
                            if (plansza->jestZajete(x, y))
                            {
                                cout << "Wybrane pole - (" << x << "," << y << ") jest zajete przez ";
                                if (plansza->sprawdz(x, y) == symbol_gracza)
                                    cout << "gracza - " << symbol_gracza;
                                else
                                    cout << "komputer - " << symbol_bot;

                                cout << '\n';
                            }
                        } while (plansza->jestZajete(x, y) || x < 1 || x > rozmiar || y < 1 || y > rozmiar);
                        plansza->ustaw(x, y);
                        plansza->zmienTure(0);
                    }
                    //ruch bota
                    else
                    {
                        cout << "Komputer wykonuje ruch \n";
                        bot->ruch(*plansza);
                        plansza->ustaw(bot->getterX(), bot->getterY());
                        plansza->zmienTure(1);
                    }
                    plansza->wyswietl();

                    // sprawdzenie stanu gry
                    if (plansza->jestPelna() && plansza->stanGry() == 0)
                        cout << "remis!";
                    else if (plansza->stanGry() != 0)
                    {
                        cout << "koniec gry! wygrywa ";
                        if (!plansza->jestTuraGracza())
                            cout << "gracz (" << symbol_gracza << ")";
                        else
                            cout << "komputer (" << symbol_bot << ")";
                    }
                    cout << '\n';
                }
                cout << "Czy chcesz zagrac ponownie na tych samych ustawieniach? (t/n): ";
                cin >> odp;
            } while (odp == 't');
            delete bot;
            delete plansza;
            break;
        case 3:
            cout << "1. Plansza - gra toczy sie na planszy skladajacej sie z siatki N x N, gdzie N jest zalezne od ciebie, w ustawieniach gry\n";
            cout << "2. Symbole - jeden gracz używa symbolu X natomiast drugi O, gdzie to ty wybierasz sobie symbol jakim rozpoczynasz, opcja w ustawieniach gry\n";
            cout << "3. Rozpoczecie gry - to gracze powinni ustalic kto rozpoczyna ruch, tutaj to jest wartość losowa\n";
            cout << "4. Ruch - ruch wykonuje sie naprzemiennie z drugim graczem, swoj ruch wykonuje sie wpisujac wspolrzedne w konsoli\n";
            cout << "5. Cel gry - celem gry jest ułożenie N znaków w jednej linii: poziomo, pionowo czy na ukos, gdzie N jest zalezne od ciebie, w ustawieniach gry\n";
            cout << "6. Wygrana - jesli jeden z graczy ulozy swoje symbole w stylu jak podpunkcie 5 to wygrywa gre\n";
            cout << "7. Remis - jesli na planszy braklo wolnych pol na wykonanie ruchu a zaden z zawodnikow nie wygral to jest to remis\n";
            cout << "8. Powtorzenie - po zakonczeniu gry, gracze moga zdecydowac sie na zagranie ponownie, plansza sie wyczysci i gra rozpocznie sie od nowa\n";
            break;
        case 4:
            break;
        default:
            cout << "Bledna opcja zostala wybrana";
            break;
        }
    }
    return 0;
}
      
  
    
 
    


