#include "Dziekanat.hpp"
#include "Prowadzacy.hpp"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

void wyswietlMenu() 
{
    cout << "\n ***** MENU *****\n";
    cout << "1. Wyswietl liste wszystkich zajec\n";
    cout << "2. Wyswietl liste wszystkich prowadzacych\n";
    cout << "3. Przypisz prowadzacego do zajec\n";
    cout << "4. Wyszukaj studenta\n";
    cout << "5. Zapisz studenta na zajecia\n";
    cout << "6. Wypisz studenta z zajec\n";
    cout << "7. Wyjscie\n";
    cout << "********************\n";
}

int main() {

    cout << "\n*** WITAJ W PROGRAMIE DZIEKANAT ***\n";
    cout << "\n Usprawnimy Twoja prace dzieki czemu bedziesz miec wiecej czasu na kawusie!\n";

    Dziekanat dziekanat;

    //zastosowanie wyłapywania wyjątków przy wczytywaniu z XML
    try{
        dziekanat.wczytajDaneZXML("dane_projekt_dziekanat.xml");
    }
    catch(const exception& e){
        cerr << "Blad podczas wczytywania danych z pliku XML: "<<e.what()<<endl;
    }


    // Dodawanie przykładowych danych z łapaniem wyjątków
    try {

        dziekanat.dodajStudenta("Jan", "Kowalski", 12345);
        dziekanat.dodajStudenta("Anna", "Nowak", 54321);
        dziekanat.dodajStudenta("Marcin", "Platek", 314750);
        dziekanat.dodajStudenta("Tomek", "Polski", 313420);
    
        dziekanat.dodajProwadzacego(make_shared<Profesor>("Dr ", "Jan", "Nowak"));
        dziekanat.dodajProwadzacego(make_shared<Doktorant>("Mgr ", "Piotr", "Kowal"));
        dziekanat.dodajProwadzacego(make_shared<Profesor>("Prof.", "Janusz", "Piechna"));

        dziekanat.dodajZajecia("Matematyka", "wyklad", 60);
        dziekanat.dodajZajecia("Fizyka", "cwiczenia", 20);
        dziekanat.dodajZajecia("Laby_c++", "laby", 10);
        dziekanat.dodajZajecia("Aerodynamika", "potop", 30);

        dziekanat.przypiszProwadzacegoDoZajec("Jan", "Nowak", "Matematyka");
        dziekanat.przypiszProwadzacegoDoZajec("Piotr", "Kowal", "Fizyka");
        dziekanat.przypiszProwadzacegoDoZajec("Anna", "Lewandowska", "Aerodynamika");
    }    

    //łapanie wyjątków w wprowadzonych (zadanych) danych
    catch(const exception& e){
        cerr <<"Blad: "<<e.what()<<endl;
    }

    int opcja;
    do {
        wyswietlMenu();
        cout << "\nWybierz dzialanie sposrod dostepnych wyzej: ";
        while (!(cin >> opcja)) {
            cout << "Niepoprawna opcja. Wprowadz liczbe: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (opcja) {
            case 1: {
                while (true) {
                    dziekanat.wyswietlListeZajec();
                    int id;
                    cout << "\nWybierz nr zajec, o ktorych chcesz sie dowiedziec wiecej (0, aby wrocic do menu): ";
                    while (!(cin >> id) || id < 0) {
                        cout << "Niepoprawna wartosc. Wprowadz numer zajec: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    if (id == 0) break;
                    dziekanat.wyswietlSzczegolyZajec(id);
                    cout << "\n0. Wroc do menu glownego\n1. Wroc do listy zajec\n";
                    int wybor;
                    while (!(cin >> wybor) || (wybor != 0 && wybor != 1)) {
                        cout << "Niepoprawna opcja. Wprowadz 0 lub 1: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    if (wybor == 0) break;
                }
                break;
            }
            case 2:
                dziekanat.wyswietlListeProwadzacych();
                break;
            
            case 3: {
                string imie, nazwisko, nazwa_zajec;
                cout << "Podaj imie prowadzacego: ";
                cin >> imie;
                cout << "Podaj nazwisko prowadzacego: ";
                cin >> nazwisko;
                cout << "Podaj nazwe zajec: ";
                cin.ignore();
                getline(cin, nazwa_zajec);

                //wyłapywanie wyjątków przy dodawaniu prowadzącego do zajęć:
                try {
                    dziekanat.przypiszProwadzacegoDoZajec(imie, nazwisko, nazwa_zajec);
                }
                catch (const exception& e){
                    cerr <<"Blad: "<<e.what()<<endl;
                }
                break;
            }

            case 4: {
                int indeks;
                cout << "Podaj numer indeksu studenta: ";
                while (!(cin >> indeks)) {
                    cout << "Niepoprawna wartosc. Wprowadz numer indeksu: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                dziekanat.wyszukajStudenta(indeks);
                break;
            }

            case 5: {
                int indeks;
                string nazwaZajec;
                cout << "Podaj numer indeksu studenta: ";
                while (!(cin >> indeks)) {
                    cout << "Niepoprawna wartosc. Wprowadz numer indeksu: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Podaj nazwe zajec: ";
                cin.ignore();
                getline(cin, nazwaZajec);
                cout<<endl;

                //kolejne wyłapywanie przy zapisywaniu studenta na zajecia
                try{
                    dziekanat.zapiszStudentaNaZajecia(indeks, nazwaZajec);
                }
                catch(const exception& e){
                    cerr <<"Blad: "<<e.what()<<endl;
                }
                break;
            }

            case 6: {
                int indeks;
                string nazwaZajec;
                cout << "Podaj numer indeksu studenta: ";
                while (!(cin >> indeks)) {
                    cout << "Niepoprawna wartosc. Wprowadz numer indeksu: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Podaj nazwe zajec: ";
                cin.ignore();
                getline(cin, nazwaZajec);
                cout<<endl;

                //i kolejne wyłapywanie przy zapisywaniu studenta na zajęcia
                try{
                    dziekanat.wypiszStudentaZajecia(indeks, nazwaZajec);
                }
                catch(const exception& e){
                    cerr << "Blad: " << e.what() << endl;
                }
                break;
            }
            case 7: {
                int potwierdzenie;
                cout << "Czy na pewno chcesz zamknac program? (1 - Tak, 0 - Nie): ";
                while (!(cin >> potwierdzenie) || (potwierdzenie != 0 && potwierdzenie != 1)) {
                    cout << "Niepoprawna opcja. Wprowadz 1, aby zamknac lub 0, aby pozostac w programie: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (potwierdzenie == 1) {
                    dziekanat.zapiszDaneDoXML("dane_projekt_dziekanat.xml");
                    cout << "Zamykanie programu...\n";
                } else {
                    opcja = -1;
                }
                break;
            }
        }
    } while (opcja != 7);

    return 0;
}

