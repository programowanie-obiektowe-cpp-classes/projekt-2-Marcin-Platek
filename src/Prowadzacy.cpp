/* Prowadzacy.cpp */
#include "Prowadzacy.hpp"
#include "Zajecia.hpp"
#include <iostream>

using namespace std;

// konstruktor klasy - inicjalizacja pól obietku
Prowadzacy::Prowadzacy(const string& tytul, const string& imie, const string& nazwisko, int max_pensum)
    : m_tytul(tytul), m_imie(imie), m_nazwisko(nazwisko), m_max_pensum(max_pensum), m_aktualne_pensum(0) {}


// destruktor wirtualny - do usuwania obiektow dziedziczacych
Prowadzacy::~Prowadzacy() {}

bool Prowadzacy::czyMoznaPrzypisacDoZajec(int godziny) const {
    return (m_aktualne_pensum + godziny) <= m_max_pensum;
}


// przypisuje do zajęć, jeśli nie przekroczy pensum
void Prowadzacy::przypiszDoZajec(shared_ptr<Zajecia> zajecia) {
    int godziny = zajecia->getLiczbaGodzin();
    if (czyMoznaPrzypisacDoZajec(godziny)) {
        m_aktualne_pensum += godziny;
        m_zajecia.push_back(zajecia);
        cout << "Prowadzacy " << m_imie << " " << m_nazwisko << " zostal przypisany do zajec: " 
             << zajecia->getNazwa() << "\n";
    } else {
        cout << "Nie mozna przypisac prowadzacego " << m_imie << " " << m_nazwisko 
             << " - przekroczone pensum (" << m_aktualne_pensum << "/" << m_max_pensum << " godzin)\n";
    }
}


// wyświetla info o danym prowadzącym
void Prowadzacy::wyswietlInformacje() const {
    cout << "Prowadzacy: " << m_tytul << " " << m_imie << " " << m_nazwisko << "\n"
         << "Typ: " << typ() << "\n"
         << "Pensum: " << m_aktualne_pensum << "/" << m_max_pensum << " godzin\n";
}


// wyświetla liste zajęć prowadzonych przez danego prowadzącego
void Prowadzacy::wyswietlZajecia() const {
    cout << "Zajecia prowadzone przez " << m_tytul << " " << m_imie << " " << m_nazwisko << ":\n";
    if (m_zajecia.empty()) {
        cout << "- Brak przypisanych zajec\n";
    } else {
        for (const auto& zajecia : m_zajecia) {
            cout << "- " << zajecia->getNazwa() << " (" << zajecia->getTyp() << ")\n";
        }
    }
}


// gettery

string Prowadzacy::getTytul() const {
    return m_tytul;
}

string Prowadzacy::getImie() const {
    return m_imie;
}

string Prowadzacy::getNazwisko() const {
    return m_nazwisko;
}

int Prowadzacy::getAktualnePensum() const {
    return m_aktualne_pensum;
}

// Implementacja klasy Profesor
Profesor::Profesor(const string& tytul, const string& imie, const string& nazwisko)
    : Prowadzacy(tytul, imie, nazwisko, 180) {}

string Profesor::typ() const {
    return "Profesor";
}

// Implementacja klasy Doktorant
Doktorant::Doktorant(const string& tytul, const string& imie, const string& nazwisko)
    : Prowadzacy(tytul, imie, nazwisko, 90) {}

string Doktorant::typ() const {
    return "Doktorant";
}

// Implementacja klasy Adiunkt
Adiunkt::Adiunkt(const string& tytul, const string& imie, const string& nazwisko)
    : Prowadzacy(tytul, imie, nazwisko, 210) {}

string Adiunkt::typ() const {
    return "Adiunkt";
}

// Implementacja klasy Asystent
Asystent::Asystent(const string& tytul, const string& imie, const string& nazwisko)
    : Prowadzacy(tytul, imie, nazwisko, 210) {}

string Asystent::typ() const {
    return "Asystent";
}