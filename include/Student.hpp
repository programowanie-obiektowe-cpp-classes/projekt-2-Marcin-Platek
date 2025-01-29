#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include <memory>
#include "Zajecia.hpp"

using namespace std;

class Student : public enable_shared_from_this<Student> {  // <--- Dodane dziedziczenie (enable shared from this) - bezpieczne tworzenie wskaźników shared_ptr do bieżącego obiektu w metodach tej klasy
private:
    string m_imie;
    string m_nazwisko;
    int m_indeks;
    vector<shared_ptr<Zajecia>> m_zajecia;  // do przechowywania listy zajec, na ktore student jest zapisany

public:
    // Konstruktor inicjalizujacy dane studenta
    Student(const string& imie, const string& nazwisko, int indeks);

    void zapiszNaZajecia(shared_ptr<Zajecia> zajecia);
    void wyswietlZapisaneZajecia() const;
    void wypiszZajecia(const string& nazwa_zajec);

    // gettery
    string getImie() const;
    string getNazwisko() const;
    int getIndex() const;
};

#endif // STUDENT_HPP