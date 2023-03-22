#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


// Funkcja alokująca pamięć dla tablicy dwuwymiarowej o rozmiarze n x m.
int** alokuj_tablice(int n, int m) 
{
    int** tablica = new int* [n];
    for (int i = 0; i < n; i++) 
    {
        tablica[i] = new int[m];
    }
    return tablica;
}


// Funkcja wypełniająca tablicę losowymi wartościami od 0 do x.
void wypelnij_tablice(int** tablica, int n, int m, int x) 
{
    srand(time(NULL));
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            tablica[i][j] = rand() % (x + 1);
        }
    }
}


// Funkcja wyświetlająca zawartość tablicy.
void wyswietl_tablice(int** tablica, int n, int m) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }
}


// Funkcja znajdująca wartość maksymalną w tablicy.
int znajdz_max(int** tablica, int n, int m) 
{
    int max_wartosc = tablica[0][0];
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (tablica[i][j] > max_wartosc)
            {
                max_wartosc = tablica[i][j];
            }
        }
    }
    return max_wartosc;
}


int main()
{
    int n, m, x;
    int wybor;
    int** tablica;

    cout << "Podaj liczbe wierszy tablicy: ";
    cin >> n;
    cout << "Podaj liczbe kolumn tablicy: ";
    cin >> m;

    tablica = alokuj_tablice(n, m);

    do {
        cout << endl << "MENU" << endl;
        cout << "1. Wypelnij tablice losowymi wartosciami" << endl;
        cout << "2. Wyswietl zawartosc tablicy" << endl;
        cout << "3. Znajdz wartosc maksymalna" << endl;
        cout << "4. Wyjdz z programu" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            cout << "Podaj maksymalna wartosc losowanych liczb: ";
            cin >> x;
            wypelnij_tablice(tablica, n, m, x);
            cout << "Tablica zostala wypelniona losowymi wartosciami." << endl;
            break;
        case 2:
            cout << "Zawartosc tablicy:" << endl;
            wyswietl_tablice(tablica, n, m);
            break;
        case 3:
            cout << "Wartosc maksymalna w tablicy wynosi: " << znajdz_max(tablica, n, m) << endl;
            break;
        case 4:
            cout << "Koniec programu." << endl;
            break;
        default:
            cout << "Niepoprawna opcja." << endl;
            break;
        }
    } while (wybor != 4);

    // Zwolnienie zaalokowanej pamięci.
    for (int i = 0; i < n; i++)
    {
        delete[] tablica[i];
    }
    delete[] tablica;

    return 0;
}