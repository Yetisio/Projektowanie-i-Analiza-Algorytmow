#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>

#include "introSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "introSort.cpp"
#include "mergeSort.cpp"
#include "quickSort.cpp"


using namespace std;


struct movie {
    string name;  // nazwa filmu
    short rating;      // ocena filmu (0-10)
    bool operator<(movie compared) { return (rating < compared.rating); }
    bool operator>(movie compared) { return (rating > compared.rating); }
};

int main(int argc, char** argv) {
   
    // pliki
    ifstream dataset;  
    string dataset_name = "dane2.csv";

    // parsowanie .csv
    string temp, line;  // jeden rekord
    char identifier;    // , lub "

    // sortowania
    string sorts[3] = { "merge", "quick", "intro" };

    // testy
    unsigned int test = 0;    // numer testu
    unsigned int ntab[] = { 10000, 100000, 500000, 1000000, 1010293};
    unsigned int unrated, median;  // ilosc nieocenionych filmow, mediana ocen
    float average;                 // srednia ocen

    
    

    for (unsigned int n : ntab)  
    {
        test++;
        cout << "Proba nr " << test << "/" << size(ntab) << ": n = " << n << '\n';
        movie* parsed_dataset = new movie[n];

        // wczytywanie pliku
        unrated = 0;
        dataset.open(dataset_name);

        if (!dataset.is_open()) {
            cout << "Problem z plikiem " + dataset_name;
            exit(1);
        }

        getline(dataset, line);  // pominiecie headera
        for (unsigned int i = 0; i < n; i++) {
            // format pliku: indeks,nazwa,ocena
            getline(dataset, line);  // dzielenie pliku na linie
            stringstream split(line);
            // wczytywanie indeksu i przecinka
            getline(split, temp, ',');
            // wczytywanie nazwy - pomiedzy " " lub zwykla oddzielona przecinkiem
            stringstream::pos_type pos = split.tellg();
            split >> identifier;
            if (identifier == '"') {
                getline(split, parsed_dataset[i].name, '"');
                split >> identifier;  // nie bierz pod uwage 
            }
            else {
                split.seekg(pos);  // powrot
                getline(split, parsed_dataset[i].name, ',');
            }
            // wczytywanie oceny
            if (!(split >> parsed_dataset[i].rating)) {
                unrated++;
                parsed_dataset[i].rating = -1;
            }
            // koniec pliku - zmiana n do liczby wczytanych filmow
            if (dataset.eof()) {
                cout << "Za malo danych w podanym pliku - wczytane dane filomowe: " << i << " / " << n << '\n';
                n = i + 1;
            }
        }
        dataset.close();

        // filtrowanie - usuwanie filmow bez ocen
        if (unrated > 0) {
            cout << " \n Filmy nie posiadajce oceny: " << unrated << '\n';
            
            cout << "\nFiltracja danych z pliku\n";
        }
        else
            cout << "  \nWszystkie rekordy pliku posiadaja ocene filmu\n";
        movie* filter_dataset = new movie[n - unrated];
        unsigned int i = 0, j = 0;

        auto duration_start = chrono::high_resolution_clock::now();  // mierzenie czasu filtrowania
        while (j < n)
            if (parsed_dataset[j].rating != -1)
                filter_dataset[i++] = parsed_dataset[j++];
            else
                j++;
        auto duration_end = chrono::high_resolution_clock::now();  // koniec mierzenia
        auto duration = chrono::duration<double, milli>(duration_end - duration_start).count();

        delete[] parsed_dataset;

        if (unrated > 0)
            cout << "  Rekordow po filtracji: " << n - unrated << '\n'
            << "  Czas filtracji wzgledem oceny:   " << duration << " ms\n";

      

        // struktury do przechowywania wynikow sortowan
        movie** sort_dataset = new movie * [size(sorts)];
        for (unsigned int i = 0; i < size(sorts); ++i)
            sort_dataset[i] = new movie[n - unrated];
        for (unsigned int i = 0; i < size(sorts); ++i)
            for (unsigned int j = 0; j < n - unrated; ++j)
                sort_dataset[i][j] = filter_dataset[j];
        delete[] filter_dataset;

        // sortowania
        for (unsigned int i = 0; i < size(sorts); ++i) {
            cout << "\nSortowanie ";
            if (sorts[i] == "merge") {
                cout << "- mergesort\n";
                duration_start = chrono::high_resolution_clock::now();
                mergeSort(sort_dataset[i], 0, n - unrated - 1);
                duration_end = chrono::high_resolution_clock::now();
            }
            else if (sorts[i] == "quick") {
                cout << "- quicksort\n";
                duration_start = chrono::high_resolution_clock::now();
                quickSort(sort_dataset[i], 0, n - unrated - 1);
                duration_end = chrono::high_resolution_clock::now();
            }
            else if (sorts[i] == "intro") {
                cout << "- introsort\n";
                duration_start = chrono::high_resolution_clock::now();
                hybridIntroSort(sort_dataset[i], 0, n - unrated - 1);
                duration_end = chrono::high_resolution_clock::now();
            }
            else {
                cout << "Wskazane bledne sortowanie\n";
                break;
            }
            duration = chrono::duration<double, milli>(duration_end - duration_start).count();
            cout << "  Czas sortowania: " << duration << " ms\n";

            // srednia ocen
            average = 0;
            for (unsigned int j = 0; j < n - unrated; ++j)
                average += sort_dataset[i][j].rating;  // average jako suma
            average /= n - unrated;
            cout << "  Srednia ocen filmow :    " << average << '\n';

            // mediana
            median = 0;
            if ((n - unrated) % 2 != 0)
                median = sort_dataset[i][(n - unrated) / 2].rating;
            else
                median = (sort_dataset[i][(n - unrated - 1) / 2].rating + sort_dataset[i][(n - unrated) / 2].rating) / 2;
            cout << "  Mediana ocen filmow :    " << median << "\n";
        }

        

        cout << "\nKoniec proby " << test << "/" << size(ntab) << '\n';
        
        
    }
}