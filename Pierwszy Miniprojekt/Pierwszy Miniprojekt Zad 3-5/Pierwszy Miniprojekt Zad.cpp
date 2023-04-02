#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> palList; // globalna tablica zawierająca znalezione palindromy

int Potega(int x, int p) {
    if (p == 0) {
        return 1;
    }
    else if (p == 1) {
        return x;
    }
    else if (p % 2 == 0) {
        int temp = Potega(x, p / 2);
        return temp * temp;
    }
    else {
        int temp = Potega(x, (p - 1) / 2);
        return temp * temp * x;
    }
}

int Silnia(int x) {
    if (x == 0) {
        return 1;
    }
    else {
        return x * Silnia(x - 1);
    }
}

bool jestPal(string testStr, int start, int end) {
    // Baza rekurencji: łańcuch jest palindromem, gdy pozostała do sprawdzenia jego długość wynosi 0 lub 1
    if (start >= end) {
        return true;
    }
    // Zamiana znaków na małe litery przed porównaniem
    char firstChar = tolower(testStr[start]);
    char lastChar = tolower(testStr[end]);
    // Sprawdzenie, czy pierwszy i ostatni znak są takie same
    if (firstChar != lastChar) {
        return false;
    }
    // Rekurencyjne wywołanie dla łańcucha bez pierwszego i ostatniego znaku
    return jestPal(testStr, start + 1, end - 1);
}

void generujPermutacje(string str, int left, int right) {
    // Baza rekurencji: wygenerowanie jednej permutacji
    if (left == right) {
        if (jestPal(str, 0, str.length() - 1)) {
            palList.push_back(str); // dodanie permutacji do tablicy palindromów
        }
    }
    else {
        // Generowanie permutacji przez zamianę każdego znaku z pozostałymi
        for (int i = left; i <= right; i++) {
            swap(str[left], str[i]);
            generujPermutacje(str, left + 1, right);
            swap(str[left], str[i]);
        }
    }
}

void usunDup() {
    sort(palList.begin(), palList.end()); // posortowanie tablicy
    palList.erase(unique(palList.begin(), palList.end()), palList.end()); // usunięcie duplikatów
}
int main() {
    int x, p;
    string testStr;
    /*
    // Test funkcji Potega
    cout << "Podaj podstawe potegi: ";
    cin >> x;
    cout << "Podaj wykladnik potegi: ";
    cin >> p;
    cout << x << "^" << p << " = " << Potega(x, p) << endl;

    // Test funkcji Silnia
    cout << "Podaj liczbe dla ktorej chcesz policzyc silnie: ";
    cin >> x;
    cout << x << "! = " << Silnia(x) << endl;
    */
    // Test funkcji Palindrom
    cout << "Podaj lancuch znakow: ";
    getline(cin, testStr);

   /*if (jestPal(testStr, 0, testStr.length() - 1)) {
        cout << testStr << " jest palindromem." << endl;
    }
    else {
        cout << testStr << " nie jest palindromem." << endl;
    }*/ 

    generujPermutacje(testStr, 0, testStr.length() - 1);

    cout << "Palindromy znalezione w lancuchu " << testStr << ":" << endl;
    for (auto pal : palList) {
        cout << pal << endl;
    }

    usunDup();

    cout << "Palindromy bez duplikatow:" << endl;
    for (auto pal : palList) {
        cout << pal << endl;
    }
    return 0;
}
