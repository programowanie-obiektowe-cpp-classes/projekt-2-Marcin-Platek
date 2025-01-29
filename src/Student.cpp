/* Student.cpp */
#include "Student.hpp"
#include "Zajecia.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// Konstruktor inicjalizujacy obiekt studenta
Student::Student(const string& imie, const string& nazwisko, int indeks)
    : m_imie(imie), m_nazwisko(nazwisko), m_indeks(indeks) {}

// Jednoczesne dodawanie studenta do listy zajec i zapisanie go na zajecia
void Student::zapiszNaZajecia(shared_ptr<Zajecia> zajecia) {
    m_zajecia.push_back(zajecia);
    zajecia->dodajStudenta(shared_from_this());

    // korzystamy z shared_from_this() dzieki czemu student przekazany do zajec bedzie zarzadzany przez shared_ptr, unikamy problemow z pamiecia
}

void Student::wyswietlZapisaneZajecia() const {
    cout << "Student: " << m_imie << " " << m_nazwisko << " (Indeks: " << m_indeks << ")\n";
    cout << "Student(ka) jest zapisany(a) na nastepujace zajecia:\n";
    for (const auto& zajecia : m_zajecia) {
        cout << "- " << zajecia->getNazwa() << " (" << zajecia->getTyp() << ")\n";
    }
}

void Student::wypiszZajecia(const string& nazwa_zajec) {
    auto it = remove_if(m_zajecia.begin(), m_zajecia.end(), 
        [&nazwa_zajec](const shared_ptr<Zajecia>& z) { return z->getNazwa() == nazwa_zajec; });

    // jesli znaleziono zajecia, to usuwamy studenta zarowno z listy zajec w klasie Student, jak i z listy studentow w klasie Zajecia
    if (it != m_zajecia.end()) {
        (*it)->usunStudenta(m_indeks); // Usuwamy studenta z zajęć
        m_zajecia.erase(it, m_zajecia.end());
        cout << "Student " << m_imie << " " << m_nazwisko << " zostal wypisany z zajec: " << nazwa_zajec << "\n";
    } else {
        cout << "Nie znaleziono zajec: " << nazwa_zajec << " dla studenta " << m_imie << " " << m_nazwisko << "\n";
    }
}

// gettery
string Student::getImie() const {
    return m_imie;
}

string Student::getNazwisko() const {
    return m_nazwisko;
}

int Student::getIndex() const {
    return m_indeks;
}
