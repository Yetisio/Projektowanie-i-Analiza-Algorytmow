#include <iostream>
#include "Lista.h"
#include "Kolejka.h"

int main() {
    // Testowanie klasy Lista
    Lista<int> lista;
    lista.dodajL(1);
    lista.dodajL(2);
    lista.dodajL(3);
    lista.wypiszL();

    lista.usunL(2);
    lista.wypiszL();

    lista.usunWszystkieL();
    lista.wypiszL();

    // Testowanie klasy Kolejka
    Kolejka<float> kolejka;
    kolejka.dodaj(1.5);
    kolejka.dodaj(2.5);
    kolejka.dodaj(3.5);
    kolejka.wypisz();

    kolejka.usun();
    kolejka.wypisz();

    kolejka.usunWszystkie();
    kolejka.wypisz();

    return 0;
}

