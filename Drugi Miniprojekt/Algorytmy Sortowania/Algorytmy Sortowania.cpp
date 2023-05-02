#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>

#include "introSort.h"
#include "mergeSort.h"
#include "quickSort.h"


using namespace std;
void pressEnter() {
    int c;
    do
        c = getchar();
    while ((c != '\n') && (c != EOF));
}

struct movie {
    string name;  // nazwa filmu
    short rating;      // ocena filmu (0-10)
    bool operator<(movie compared) { return (rating < compared.rating); }
    bool operator>(movie compared) { return (rating > compared.rating); }
};

int main(int argc, char** argv) {
    if (argc > 1 && argv[1] != string("--zapisz")) {
        cout << "\nWywolanie: ./projekt2 [--zapisz limit]\n\n"
            << "Opcje:\n"
            << "--zapisz | limit - maksymalna ilosc danych do zapisu\n\n";
        return 0;
    }

    // pliki
    ifstream dataset;  // baza filmow (wczytywany plik)
    string dataset_name = "dane2.csv";
    ofstream sorted_dataset;  // posortowana baza (zapisywany plik)
    string sorted_dataset_name;

    // parsowanie .csv
    string temp, line;  // pojedynczy wpis w bazie
    char identifier;         // , lub "

    // sortowania
    std::string sorts[3] = { "merge", "quick", "intro" };

    // testy
    unsigned int test = 0;    // numer testu
    unsigned int nlimit = 0;  // limit n dla zapisu na sorted_dataset
    unsigned int ntab[] = { 10000, 100000, 500000, 1000000, 1010292 };
    unsigned int unrated, median;  // ilosc nieocenionych filmow, mediana ocen
    float average;                 // srednia ocen

    if (argc >= 3)
        nlimit = stoi(argv[2]);

    cout << fixed << setprecision(3) << "\x1B[2J\x1B[H";  // precyzja wyswietlania + clear screen

    for (unsigned int n : ntab)  // #include <iterator>
    {
        test++;
        cout << "TEST " << test << "/" << size(ntab) << ": n = " << n << '\n';
        movie* parsed_dataset = new movie[n];

        // wczytywanie pliku
        unrated = 0;
        dataset.open(dataset_name);

        if (!dataset.is_open()) {
            cout << "Nie udalo sie otworzyc pliku " + dataset_name;
            exit(1);
        }

        getline(dataset, line);  // pominiecie headera
        for (unsigned int i = 0; i < n; i++) {
            // format pliku: indeks,nazwa,ocena
            getline(dataset, line);  // dzielenie pliku na linie
            stringstream split(line);
            // wczytywanie indeksu i przecinka
            getline(split, temp, ',');
            // wczytywanie nazwy - pomiedzy " " lub zwykla oddzielona
            // przecinkiem
            stringstream::pos_type pos = split.tellg();
            split >> identifier;
            if (identifier == '"') {
                getline(split, parsed_dataset[i].name, '"');
                split >> identifier;  // ignoruj ,
            }
            else {
                split.seekg(pos);  // wroc
                getline(split, parsed_dataset[i].name, ',');
            }
            // wczytywanie oceny
            if (!(split >> parsed_dataset[i].rating)) {
                unrated++;
                parsed_dataset[i].rating = -1;
            }
            // koniec pliku - zmiana n do liczby wczytanych filmow
            if (dataset.eof()) {
                cout << "Plik zawiera za malo danych - wczytane filmy: " << i << " / " << n << '\n';
                n = i + 1;
            }
        }
        dataset.close();

        // filtrowanie - usuwanie filmow bez ocen
        if (unrated > 0) {
            cout << "> Filmy bez oceny: " << unrated << '\n';
            pressEnter();
            cout << "Filtrowanie danych\n";
        }
        else
            cout << "> Wszystkie filmy sa ocenione.\n";
        movie* filtered_dataset = new movie[n - unrated];
        unsigned int i = 0, j = 0;

        auto duration_start = chrono::high_resolution_clock::now();  // mierzenie czasu filtrowania
        while (j < n)
            if (parsed_dataset[j].rating != -1)
                filtered_dataset[i++] = parsed_dataset[j++];
            else
                j++;
        auto duration_end = chrono::high_resolution_clock::now();  // koniec mierzenia
        auto duration = chrono::duration<double, milli>(duration_end - duration_start).count();

        delete[] parsed_dataset;

        if (unrated > 0)
            cout << "> Po przefiltrowaniu: " << n - unrated << '\n'
            << "> Czas filtrowania:   " << duration << " ms\n";

        pressEnter();

        // struktury do przechowywania wynikow sortowan
        movie** sorting_datasets = new movie * [size(sorts)];
        for (unsigned int i = 0; i < size(sorts); ++i)
            sorting_datasets[i] = new movie[n - unrated];
        for (unsigned int i = 0; i < size(sorts); ++i)
            for (unsigned int j = 0; j < n - unrated; ++j)
                sorting_datasets[i][j] = filtered_dataset[j];
        delete[] filtered_dataset;

        // sortowania
        for (unsigned int i = 0; i < size(sorts); ++i) {
            cout << "Sortowanie ";
            if (sorts[i] == "merge") {
                cout << "przez scalanie (mergesort)\n";
                duration_start = chrono::high_resolution_clock::now();
                mergeSort(sorting_datasets[i], 0, n - unrated - 1);
                duration_end = chrono::high_resolution_clock::now();
            }
            else if (sorts[i] == "quick") {
                cout << "szybkie (quicksort)\n";
                duration_start = chrono::high_resolution_clock::now();
                quickSort(sorting_datasets[i], 0, n - unrated - 1);
                duration_end = chrono::high_resolution_clock::now();
            }
            else if (sorts[i] == "intro") {
                cout << "introspektywne (introsort)\n";
                duration_start = chrono::high_resolution_clock::now();
                hybridIntroSort(sorting_datasets[i], 0, n - unrated - 1);
                duration_end = chrono::high_resolution_clock::now();
            }
            else {
                cout << "nie powiodlo sie - brak interfejsow sortowan.\n";
                break;
            }
            duration = chrono::duration<double, milli>(duration_end - duration_start).count();
            cout << "> Czas sortowania: " << duration << " ms\n";

            // srednia ocen
            average = 0;
            for (unsigned int j = 0; j < n - unrated; ++j)
                average += sorting_datasets[i][j].rating;  // average jako suma
            average /= n - unrated;
            cout << "> Srednia ocen:    " << average << '\n';

            // mediana
            median = 0;
            if ((n - unrated) % 2 != 0)
                median = sorting_datasets[i][(n - unrated) / 2].rating;
            else
                median = (sorting_datasets[i][(n - unrated - 1) / 2].rating + sorting_datasets[i][(n - unrated) / 2].rating) / 2;
            cout << "> Mediana ocen:    " << median << "\n\n";
        }

        // zapisywanie plikow
        if (nlimit > 0 && nlimit >= n) {
            cout << "Zapisywanie plikow wynikowych...\n";
            sorted_dataset_name =
                dataset_name.substr(0, dataset_name.length() - 4) + "_" +
                to_string(n);
            for (unsigned int i = 0; i < size(sorts); ++i) {
                sorted_dataset.open(sorted_dataset_name + "_" + sorts[i] +
                    "sort.csv");
                if (sorted_dataset.is_open()) {
                    sorted_dataset << ",movie,rating\n";  // header
                    for (unsigned int j = 0; j < n - unrated; ++j)
                        sorted_dataset << j << ",\""
                        << sorting_datasets[i][j].name << "\","
                        << sorting_datasets[i][j].rating << '\n';
                    sorted_dataset.close();
                    cout << "[ok] ";
                }
                else
                    cout << "[x] ";
                cout << sorted_dataset_name + "_" + sorts[i] +
                    "sort.csv\n";
                delete[] sorting_datasets[i];
            }
            cout << '\n';
        }

        cout << "KONIEC TESTU " << test << "/" << size(ntab) << '\n';
        pressEnter();
        cout << "\x1B[2J\x1B[H"; // clear screen
        
    }
}