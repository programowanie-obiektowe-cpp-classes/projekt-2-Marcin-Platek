#ifndef DZIEKANAT_HPP
#define DZIEKANAT_HPP

#include <vector>
#include <memory>               // Biblioteka zawierająca inteligentne wskaźniki (smart pointer)
#include <algorithm>
#include "Student.hpp"
#include "Prowadzacy.hpp"
#include "Zajecia.hpp"

using namespace std;

class Dziekanat {
private:
    // shared_ptr sluzy do zarzadzania pamiecia dynamiczna i wspoldzielenie obiektow pomiedzy roznymi czesciami programu
    // student jest zapisany na zajecia i student jest przypisany do udzialu w zajeciach, trzeba to jakos polaczyc i do tego wlasnie dobre jest shared_ptr
    // nie trzeba recznie zwalniac pamieci, shared_ptr ja usunie automatycznie gdy usunieta zostanie ostatnia kopia wskaznika

    vector<shared_ptr<Student>> m_studenci;
    vector<shared_ptr<Prowadzacy>> m_prowadzacy;
    vector<shared_ptr<Zajecia>> m_zajecia;

public:
    void dodajStudenta(const string& imie, const string& nazwisko, int indeks);
    void usunStudenta(int indeks);
    void dodajProwadzacego(const shared_ptr<Prowadzacy>& prowadzacy);
    void usunProwadzacego(const string& tytul, const string& imie, const string& nazwisko);
    void dodajZajecia(const string& nazwa, const string& typ, int max_miejsc);
    void przypiszProwadzacegoDoZajec(const string& imie, const string& nazwisko, const string& nazwa_zajec);
    void zapiszStudentaNaZajecia(int indeks, const string& nazwa_zajec);
    void wypiszStudentaZajecia(int indeks, const string& nazwa_zajec);
    void wyswietlZajeciaStudenta(int indeks) const;
    void wyswietlListeZajec() const;
    void wyswietlListeProwadzacych() const;
    void wyszukajStudenta(int indeks) const;
    void wyswietlSzczegolyProwadzacego(const string& tytul, const string& imie, const string& nazwisko) const;
    void wyswietlSzczegolyZajec(int id) const;

    //TinyXML
    void zapiszDaneDoXML(const string& nazwaPliku); 
    void wczytajDaneZXML(const string& nazwaPliku); 
};

#endif // DZIEKANAT_HPP