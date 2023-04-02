#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 100;

// Funkcja zapisująca tablicę do pliku tekstowego
void saveToFileText(int arr[], int size) {
    ofstream file("array.txt");
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            file << arr[i] << " ";
        }
        file.close();
        cout << "Tablica zostala zapisana do pliku tekstowego.\n";
    }
    else {
        cout << "Nie udalo sie otworzyc pliku.\n";
    }
}

// Funkcja wczytująca tablicę z pliku tekstowego
void readFromFileText(int arr[], int& size) {
    ifstream file("array.txt");
    if (file.is_open()) {
        size = 0;
        while (!file.eof() && size < MAX_SIZE) {
            file >> arr[size];
            size++;
        }
        file.close();
        cout << "Tablica zostala wczytana z pliku tekstowego.\n";
    }
    else {
        cout << "Nie udalo sie otworzyc pliku.\n";
    }
}

// Funkcja zapisująca tablicę do pliku binarnego
void saveToFileBinary(int arr[], int size) {
    ofstream file("array.bin", ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(arr), size * sizeof(int));
        file.close();
        cout << "Tablica zostala zapisana do pliku binarnego.\n";
    }
    else {
        cout << "Nie udalo sie otworzyc pliku.\n";
    }
}

// Funkcja wczytująca tablicę z pliku binarnego
void readFromFileBinary(int arr[], int& size) {
    ifstream file("array.bin", ios::binary);
    if (file.is_open()) {
        file.seekg(0, ios::end);
        int fileSize = file.tellg();
        size = fileSize / sizeof(int);
        file.seekg(0, ios::beg);
        file.read(reinterpret_cast<char*>(arr), fileSize);
        file.close();
        cout << "Tablica zostala wczytana z pliku binarnego.\n";
    }
    else {
        cout << "Nie udalo sie otworzyc pliku.\n";
    }
}

// Funkcja wypisująca zawartość tablicy na ekran
void printArray(int arr[], int size) {
    cout << "Tablica: [ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]\n";
}

int main() {
    int choice, size = 0;
    int arr[MAX_SIZE];

    do {
        cout << "\nMENU\n";
        cout << "1. Zapisz tablice do pliku tekstowego.\n";
        cout << "2. Wczytaj tablice z pliku tekstowego.\n";
        cout << "3. Zapisz tablice do pliku binarnego.\n";
        cout << "4. Wczytaj tablice z pliku binarnego.\n";
        //cout << "5. Wypisz zawartosc tablicy.\n";
        cout << "5. Wyjdz z programu.\n";
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
        case 1:
            saveToFileText(arr, size);
            break;
        case 2:
            readFromFileText(arr, size);
            break;
        case 3:
            saveToFileBinary(arr, size);
            break;
        case 4:
            readFromFileBinary(arr, size);
            break;
       // case 5:
           // printArray(arr, size);
           // break;
        case 5:
            cout << "Koniec programu.\n";
            break;
        default:
            cout << "Niepoprawna opcja.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}