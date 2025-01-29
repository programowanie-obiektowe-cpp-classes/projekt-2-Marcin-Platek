#ifndef PROWADZACY_HPP
#define PROWADZACY_HPP

#include <string>
#include <vector>
#include <memory>
#include "Zajecia.hpp"

using namespace std;


// Klasa bazowa dla prowadzących zajecia
class Prowadzacy {
protected:
    string m_tytul;
    string m_imie;
    string m_nazwisko;
    int m_max_pensum;  // Maksymalna liczba godzin, jaką może zrealizować
    int m_aktualne_pensum; // aktualnie przydzielona liczba godzin
    vector<shared_ptr<Zajecia>> m_zajecia;  // wektor ze wskaźnikami na zajęcia, które dany prowadzący prowadzi

public:
    //konstruktor klasy bazowej
    Prowadzacy(const string& tytul, const string& imie, const string& nazwisko, int max_pensum);

    //wirtualny destruktor, pozwala na odpowiednie usuwanie obiektow pochodnych
    virtual ~Prowadzacy();

    bool czyMoznaPrzypisacDoZajec(int godziny) const;
    void przypiszDoZajec(shared_ptr<Zajecia> zajecia);
    void wyswietlInformacje() const;
    void wyswietlZajecia() const;

    virtual string typ() const = 0; // Metoda czysto wirtualna (obowiązkowa do implementacji klas dziedziczacych)

    // pobieranie danych
    string getTytul() const;
    string getImie() const;
    string getNazwisko() const;
    int getAktualnePensum() const;
};

// Klasa Profesor
class Profesor : public Prowadzacy {
public:
    Profesor(const string& tytul, const string& imie, const string& nazwisko);
    string typ() const override;
};

// Klasa Doktorant
class Doktorant : public Prowadzacy {
public:
    Doktorant(const string& tytul, const string& imie, const string& nazwisko);
    string typ() const override;
};

// Klasa Adiunkt
class Adiunkt : public Prowadzacy {
public:
    Adiunkt(const string& tytul, const string& imie, const string& nazwisko);
    string typ() const override;
};

// Klasa Asystent
class Asystent : public Prowadzacy {
public:
    Asystent(const string& tytul, const string& imie, const string& nazwisko);
    string typ() const override;
};

#endif // PROWADZACY_HPP