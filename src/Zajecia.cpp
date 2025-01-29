/* Zajecia.cpp */
#include "Zajecia.hpp"
#include "Student.hpp"
#include "Prowadzacy.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// konstruktor inicjalizujacy zajecia
Zajecia::Zajecia(const string& nazwa, const string& typ, int max_miejsc)
    : m_nazwa(nazwa), m_typ(typ), m_max_miejsc(max_miejsc), m_zajete_miejsca(0) {}


// dodawanie do zajec, sprawdzenie wolnych miejsc
void Zajecia::dodajStudenta(shared_ptr<Student> student) {
    if (m_zajete_miejsca < m_max_miejsc) {
        m_studenci.push_back(student);
        m_zajete_miejsca++;
    } else {
        cout << "Brak wolnych miejsc na zajeciach: " << m_nazwa << "\n";
    }
}


//wywalenie z zajec na podstawie indeksu
void Zajecia::usunStudenta(int indeks) {
    auto it = remove_if(m_studenci.begin(), m_studenci.end(), 
        [indeks](const shared_ptr<Student>& s) { return s->getIndex() == indeks; });

    if (it != m_studenci.end()) {
        m_studenci.erase(it, m_studenci.end());
        m_zajete_miejsca--;
        cout << "Student o indeksie " << indeks << " zostal usuniety z zajec: " << m_nazwa << "\n";
    } else {
        cout << "Nie znaleziono studenta o indeksie " << indeks << " na zajeciach " << m_nazwa << "\n";
    }
}


// do zwracania listy studentów zapisanych na zajęcia dynamicznie
vector<shared_ptr<Student>> Zajecia::getListaStudentow() const {
    return m_studenci;
}


//sprawdzenie wolnych miejsc na zajeciach
bool Zajecia::sprawdzWolneMiejsca() const {
    return m_zajete_miejsca < m_max_miejsc;
}


//zwraca maks liczbe miejsc na zajeciach
int Zajecia::getMaxMiejsc() const {
    return m_max_miejsc;
}


//przypisywanie prowadzacego, korzysta z shared_ptr
void Zajecia::przypiszProwadzacego(shared_ptr<Prowadzacy> prowadzacy) {
    if (prowadzacy->czyMoznaPrzypisacDoZajec(getLiczbaGodzin())) {
        m_prowadzacy = prowadzacy;
        prowadzacy->przypiszDoZajec(shared_from_this()); // dziedziczenie po shared_from_this
        cout << "Prowadzacy " << prowadzacy->getTytul() << " " << prowadzacy->getImie()
             << " " << prowadzacy->getNazwisko() << " zostal przypisany do zajec: " << m_nazwa << "\n";
    } else {
        cout << "Prowadzacy " << prowadzacy->getTytul() << " " << prowadzacy->getImie()
             << " " << prowadzacy->getNazwisko() << " nie moze byc przypisany do zajec "
             << m_nazwa << " z powodu przekroczenia pensum.\n";
    }
}


// Do wyswietlania szczegolow zajec - bardziej pod sprawdzanie funkcjonalnosci
void Zajecia::wyswietlSzczegoly() const {
    cout << "\nZajecia: " << m_nazwa << " (" << m_typ << ")\n";
    cout << "Liczba miejsc: " << m_max_miejsc << ", Zajete: " << m_zajete_miejsca << "\n";
    if (m_prowadzacy) {
        cout << "Prowadzacy: " << m_prowadzacy->getNazwisko() << " " << m_prowadzacy->getImie() << "\n";
    } else {
        cout << "Brak przypisanego prowadzacego\n";
    }
    
    cout << "\nLista studentow:\n";
    if (m_studenci.empty()) {
        cout << "- Brak studentow zapisanych na te zajecia.\n";
    } else {
        vector<shared_ptr<Student>> sortedStudents = m_studenci;
        sort(sortedStudents.begin(), sortedStudents.end(), [](const shared_ptr<Student>& a, const shared_ptr<Student>& b) {
            return a->getNazwisko() < b->getNazwisko();
        });
        for (const auto& student : sortedStudents) {
            cout << "- " << student->getNazwisko() << " " << student->getImie() << " (Indeks: " << student->getIndex() << ")\n";
        }
    }
}

string Zajecia::getNazwa() const {
    return m_nazwa;
}

string Zajecia::getTyp() const {
    return m_typ;
}


// tu sobie sam poustalalem ile godzin na jaki typ zajec
int Zajecia::getLiczbaGodzin() const {
    if (m_typ == "wyklad") return 30;
    if (m_typ == "cwiczenia") return 15;
    if (m_typ == "laby") return 10;
    if (m_typ == "potop") return 45;
    return 0; // Domyślnie jeśli typ jest nieznany
}


//uwaga - nie trzeba dbac o destruktory bo vectory i shared_ptr robią za mnie robote