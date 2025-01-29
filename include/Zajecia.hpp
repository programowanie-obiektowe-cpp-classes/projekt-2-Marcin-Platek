#ifndef ZAJECIA_HPP
#define ZAJECIA_HPP

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Student;
class Prowadzacy;

// Dziedziczenie po enable_shared_from_this<Zajecia> pozwala mi wygenerowac shared_ptr z wnetrza klasy
// Gdyby nie to, to przy przypisywaniu prowadzącego do zajęć trzeba byłoby tworzyć nowe instancje
class Zajecia : public enable_shared_from_this<Zajecia> 
{ 
private:
    string m_nazwa;
    string m_typ;
    int m_max_miejsc;
    int m_zajete_miejsca;
    vector<shared_ptr<Student>> m_studenci;
    shared_ptr<Prowadzacy> m_prowadzacy;

public:
    Zajecia(const string& nazwa, const string& typ, int max_miejsc);

    void dodajStudenta(shared_ptr<Student> student);
    void usunStudenta(int indeks);
    bool sprawdzWolneMiejsca() const;
    void przypiszProwadzacego(shared_ptr<Prowadzacy> m_prowadzacy);
    void wyswietlSzczegoly() const;
    
    string getNazwa() const;
    string getTyp() const;
    int getLiczbaGodzin() const;
    int getMaxMiejsc() const;
    vector<shared_ptr<Student>> getListaStudentow() const;
    shared_ptr<Prowadzacy> getProwadzacy() const { return m_prowadzacy; }
};

#endif // ZAJECIA_HPP