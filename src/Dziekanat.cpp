#include "Dziekanat.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <algorithm>

using namespace std;

// uzywamy make_shared do dynamicznego tworzenia obiektu i zarzadzania nim przez shared_ptr
void Dziekanat::dodajStudenta(const string& imie, const string& nazwisko, int indeks) {
    m_studenci.push_back(make_shared<Student>(imie, nazwisko, indeks));   
}


// usuwa studenta na podstawie numeru indeksu
void Dziekanat::usunStudenta(int indeks) {
    auto it = remove_if(m_studenci.begin(), m_studenci.end(),
        [indeks](const shared_ptr<Student>& s) { return s->getIndex() == indeks; });

    if (it != m_studenci.end()) {
        m_studenci.erase(it, m_studenci.end());
    } else {
        cout << "\nNie znaleziono studenta o indeksie " << indeks << "\n";
    }
}


// ddodaje prowadzacego i przekazuje shared_ptr do wektora aby zarządzać pamięcią dynamiczną
void Dziekanat::dodajProwadzacego(const shared_ptr<Prowadzacy>& prowadzacy) {
    m_prowadzacy.push_back(prowadzacy);
}


// usuwa prowadzącego na podstawie tytułu, imienia i nazwiska
void Dziekanat::usunProwadzacego(const string& tytul, const string& imie, const string& nazwisko) {
    auto it = remove_if(m_prowadzacy.begin(), m_prowadzacy.end(),
        [&tytul, &imie, &nazwisko](const shared_ptr<Prowadzacy>& p) {
            return p->getTytul() == tytul && p->getImie() == imie && p->getNazwisko() == nazwisko;
        });

    if (it != m_prowadzacy.end()) {
        m_prowadzacy.erase(it, m_prowadzacy.end());
    } else {
        cout << "\nNie znaleziono prowadzacego: " << imie << " " << nazwisko << "\n";
    }
}


// Wyświetla liste prowadzących, posortowanych alfabetycznie po nazwisku
void Dziekanat::wyswietlListeProwadzacych() const {
    vector<shared_ptr<Prowadzacy>> sorted = m_prowadzacy;
    sort(sorted.begin(), sorted.end(), [](const shared_ptr<Prowadzacy>& a, const shared_ptr<Prowadzacy>& b) {
        return a->getNazwisko() < b->getNazwisko();
    });

    cout << "\nLista prowadzacych:\n";
    int id = 1;
    for (const auto& prowadzacy : sorted) {
        cout << id << ". " << prowadzacy->getTytul() << " " << prowadzacy->getImie() << " " << prowadzacy->getNazwisko() 
             << " (Pensum: " << prowadzacy->getAktualnePensum() << "h)" << "\n";
        id++;
    }
}


// Wyświetla szczegóły konkretnego prowadzącego na podstawie jego danych osobowych
void Dziekanat::wyswietlSzczegolyProwadzacego(const string& tytul, const string& imie, const string& nazwisko) const {
    auto it = find_if(m_prowadzacy.begin(), m_prowadzacy.end(),
        [&tytul, &imie, &nazwisko](const shared_ptr<Prowadzacy>& p) {
            return p->getTytul() == tytul && p->getImie() == imie && p->getNazwisko() == nazwisko;
        });

    if (it != m_prowadzacy.end()) {
        (*it)->wyswietlInformacje();
    } else {
        cout << "Nie znaleziono prowadzacego: " << tytul << " " << imie << " " << nazwisko << "\n";
    }
}


// Dodaje nowe zajęcia do systemu, potrzeba określić nazwe, typ i maksymalną liczbe miejsc
void Dziekanat::dodajZajecia(const string& nazwa, const string& typ, int max_miejsc) {
    m_zajecia.push_back(make_shared<Zajecia>(nazwa, typ, max_miejsc));
}


// Do przypisywania prowadzącego do określonych zajęć - można to zrobić w mainie, ale tutaj jest dodatkowe sprawdzenie pensum
void Dziekanat::przypiszProwadzacegoDoZajec(const string& imie, const string& nazwisko, const string& nazwa_zajec) {
    auto prow = find_if(m_prowadzacy.begin(), m_prowadzacy.end(),
        [&imie, &nazwisko](const shared_ptr<Prowadzacy>& p) {
            return p->getImie() == imie && p->getNazwisko() == nazwisko;
        });

    auto zaj = find_if(m_zajecia.begin(), m_zajecia.end(),
        [&nazwa_zajec](const shared_ptr<Zajecia>& z) { return z->getNazwa() == nazwa_zajec; });

    // Tutaj powprowadzamy wyjatki zamiast wyrzucania komunikatu o błędach - nowa implementacja kodu
    if (prow == m_prowadzacy.end()) {
        throw runtime_error("Blad: Nie znaleziono prowadzacego " + imie + " " + nazwisko);
    }

    if (zaj == m_zajecia.end()) {
        throw runtime_error("Blad: Nie znaleziono zajecia " + nazwa_zajec);
    }

    if (!(*prow)->czyMoznaPrzypisacDoZajec((*zaj)->getLiczbaGodzin())) {
        throw runtime_error("Blad: Prowadzacy " + imie + " " + nazwisko + " przekroczyl pensum i nie moze prowadzic zajec " + nazwa_zajec);
    }

    // Stara implementacja kodu
    /*
    if (prow == m_prowadzacy.end()) {
        cout << "\nNie znaleziono prowadzacego: " << imie << " " << nazwisko << "\n";
        return;
    }

    if (zaj == m_zajecia.end()) {
        cout << "\nNie znaleziono zajecia: " << nazwa_zajec << "\n";
        return;
    }

    if (!(*prow)->czyMoznaPrzypisacDoZajec((*zaj)->getLiczbaGodzin())) {
        cout << "\nProwadzacy " << imie << " " << nazwisko
             << " nie moze zostac przypisany do zajec " << nazwa_zajec
             << " z powodu przekroczenia pensum.\n";
        return;
    }
    */

    (*zaj)->przypiszProwadzacego(*prow);
    cout << "\nProwadzacy " << imie << " " << nazwisko << " zostal przypisany do zajec: " << nazwa_zajec << "\n";
}


// Wyświetla liste wszystkich zajec, ktore są w systemie
void Dziekanat::wyswietlListeZajec() const {
    vector<shared_ptr<Zajecia>> sorted = m_zajecia;
    sort(sorted.begin(), sorted.end(), [](const shared_ptr<Zajecia>& a, const shared_ptr<Zajecia>& b) {
        return a->getNazwa() < b->getNazwa();
    });

    cout << "\nLista zajec:\n";
    int id = 1;
    for (const auto& zajecia : sorted) {
        cout << id << ". " << zajecia->getNazwa() << " (" << zajecia->getTyp() << ")\n";
        id++;
    }
}


// do wyswietlania szczegolow konkretnych zajec
void Dziekanat::wyswietlSzczegolyZajec(int id) const {
    vector<shared_ptr<Zajecia>> sorted = m_zajecia;
    sort(sorted.begin(), sorted.end(), [](const shared_ptr<Zajecia>& a, const shared_ptr<Zajecia>& b) {
        return a->getNazwa() < b->getNazwa();
    });

    if (id < 1 || id > sorted.size()) {
        cout << "\nNiepoprawny numer zajec, sprobuj ponownie.\n";
        return;
    }

    auto zajecia = sorted[id - 1];
    zajecia->wyswietlSzczegoly();
}


// Odnajduje studenta w systemie po numerze indeksu
void Dziekanat::wyszukajStudenta(int indeks) const {
    auto it = find_if(m_studenci.begin(), m_studenci.end(), [indeks](const shared_ptr<Student>& s) {
        return s->getIndex() == indeks;
    });

    if (it != m_studenci.end()) {
        cout << "\nZnaleziono studenta: " << (*it)->getImie() << " " << (*it)->getNazwisko() << "\n";
        (*it)->wyswietlZapisaneZajecia();
    } else {
        cout << "\nNie znaleziono studenta o indeksie " << indeks << "\n";
    }
}


// Zapisuje studenta na zajecia, sprawdza czy są wolne miejsca i czy student juz nie jest zapisany na te zajecia
void Dziekanat::zapiszStudentaNaZajecia(int indeks, const string& nazwa_zajec) {
    auto student = find_if(m_studenci.begin(), m_studenci.end(),
        [indeks](const shared_ptr<Student>& s) { return s->getIndex() == indeks; });

    if (student != m_studenci.end()) {
        auto zajecia = find_if(m_zajecia.begin(), m_zajecia.end(),
            [&nazwa_zajec](const shared_ptr<Zajecia>& z) { return z->getNazwa() == nazwa_zajec; });

        if (zajecia != m_zajecia.end() && (*zajecia)->sprawdzWolneMiejsca()) {
            
            // Sprawdzenie, czy student już jest zapisany na te zajęcia
            vector<shared_ptr<Student>> zapisaniStudenci = (*zajecia)->getListaStudentow();
            auto alreadyEnrolled = find_if(zapisaniStudenci.begin(), zapisaniStudenci.end(),
                [&student](const shared_ptr<Student>& s) { return s == *student; });

            if (alreadyEnrolled == zapisaniStudenci.end()) { 
                (*zajecia)->dodajStudenta(*student);
                cout << "\nStudent zostal poprawnie zapisany na zajecia\n";
            } else {
                cout << "\nStudent jest juz zapisany na te zajecia.\n";
            }

        } else {
            cout << "\nBrak wolnych miejsc lub zajecia nie istnieja.\n";
        }
    } else {
        cout << "\nNie znaleziono studenta.\n";
    }
}


// wypisuje studenta z zajec
void Dziekanat::wypiszStudentaZajecia(int indeks, const string& nazwa_zajec) {
    auto student = find_if(m_studenci.begin(), m_studenci.end(),
        [indeks](const shared_ptr<Student>& s) { return s->getIndex() == indeks; });

    if (student != m_studenci.end()) {
        auto zajecia = find_if(m_zajecia.begin(), m_zajecia.end(),
            [&nazwa_zajec](const shared_ptr<Zajecia>& z) { return z->getNazwa() == nazwa_zajec; });

        if (zajecia != m_zajecia.end()) {
            (*student)->wypiszZajecia(nazwa_zajec);
            (*zajecia)->usunStudenta(indeks);
            cout << "\nStudent zostal wypisany z zajec.\n";
        } else {
            cout << "\nNie znaleziono podanych zajec.\n";
        }
    } else {
        cout << "\nNie znaleziono studenta o indeksie " << indeks << "\n";
    }
}

// zastosowanie XMLa


void Dziekanat::zapiszDaneDoXML(const string& nazwaPliku) {
    tinyxml2::XMLDocument doc;
    
    // Tworzymy główny element XML
    tinyxml2::XMLElement* root = doc.NewElement("Dziekanat");
    doc.InsertFirstChild(root);

    // Sekcja: Studenci
    tinyxml2::XMLElement* studenciElem = doc.NewElement("Studenci");
    root->InsertEndChild(studenciElem);
    
    for (const auto& student : m_studenci) {
        tinyxml2::XMLElement* studentElem = doc.NewElement("Student");
        studentElem->SetAttribute("Imie", student->getImie().c_str());
        studentElem->SetAttribute("Nazwisko", student->getNazwisko().c_str());
        studentElem->SetAttribute("Indeks", student->getIndex());
        studenciElem->InsertEndChild(studentElem);
    }

    // Sekcja: Prowadzący
    tinyxml2::XMLElement* prowadzacyElem = doc.NewElement("Prowadzacy");
    root->InsertEndChild(prowadzacyElem);
    
    for (const auto& prow : m_prowadzacy) {
        tinyxml2::XMLElement* prowElem = doc.NewElement("Prowadzacy");
        prowElem->SetAttribute("Imie", prow->getImie().c_str());
        prowElem->SetAttribute("Nazwisko", prow->getNazwisko().c_str());
        prowElem->SetAttribute("Tytul", prow->getTytul().c_str());
        prowElem->SetAttribute("Pensum", prow->getAktualnePensum());
        prowadzacyElem->InsertEndChild(prowElem);
    }

    // Sekcja: Zajęcia
    tinyxml2::XMLElement* zajeciaElem = doc.NewElement("Zajecia");
    root->InsertEndChild(zajeciaElem);
    
    for (const auto& zajecie : m_zajecia) {
        tinyxml2::XMLElement* zajElem = doc.NewElement("Zajecie");
        zajElem->SetAttribute("Nazwa", zajecie->getNazwa().c_str());
        zajElem->SetAttribute("Typ", zajecie->getTyp().c_str());
        zajElem->SetAttribute("MaxMiejsc", zajecie->getMaxMiejsc());
        zajeciaElem->InsertEndChild(zajElem);
    }

    // Zapis do pliku
    doc.SaveFile(nazwaPliku.c_str());
    cout << "Dane zapisano do pliku XML: " << nazwaPliku << endl;
}


void Dziekanat::wczytajDaneZXML(const string& nazwaPliku) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(nazwaPliku.c_str()) != tinyxml2::XML_SUCCESS) {
        cout << "Blad wczytywania pliku XML: " << nazwaPliku << endl;
        return;
    }

    // Pobranie głównego elementu XML (root)
    tinyxml2::XMLElement* root = doc.FirstChildElement("Dziekanat");
    if (!root) {
        cout << "Nie znaleziono elementu 'Dziekanat' w pliku XML." << endl;
        return;
    }

    // Wczytanie prowadzących
    tinyxml2::XMLElement* prowElem = root->FirstChildElement("Prowadzacy");
    if (prowElem) {
        tinyxml2::XMLElement* prowadzacyElem = prowElem->FirstChildElement("Prowadzacy");
        while (prowadzacyElem) {
            string imie = prowadzacyElem->Attribute("Imie");
            string nazwisko = prowadzacyElem->Attribute("Nazwisko");
            string tytul = prowadzacyElem->Attribute("Tytul");

            shared_ptr<Prowadzacy> prowadzacy;
            
            // Logika wykrywania typu prowadzącego
            if (tytul == "Prof.") {
                prowadzacy = make_shared<Profesor>(tytul, imie, nazwisko);
            } else if (tytul == "Dr") {
                prowadzacy = make_shared<Adiunkt>(tytul, imie, nazwisko);
            } else if (tytul == "Mgr") {
                prowadzacy = make_shared<Doktorant>(tytul, imie, nazwisko);
            } else {
                prowadzacy = make_shared<Asystent>(tytul, imie, nazwisko);  // Domyślnie Asystent
            }

            dodajProwadzacego(prowadzacy);
            prowadzacyElem = prowadzacyElem->NextSiblingElement("Prowadzacy");
        }
    }

    // Wczytanie zajęć
    tinyxml2::XMLElement* zajElem = root->FirstChildElement("Zajecia");
    if (zajElem) {
        tinyxml2::XMLElement* zajecieElem = zajElem->FirstChildElement("Zajecie");
        while (zajecieElem) {
            string nazwa = zajecieElem->Attribute("Nazwa");
            string typ = zajecieElem->Attribute("Typ");
            int maxMiejsc;
            zajecieElem->QueryIntAttribute("MaxMiejsc", &maxMiejsc);

            dodajZajecia(nazwa, typ, maxMiejsc);
            zajecieElem = zajecieElem->NextSiblingElement("Zajecie");
        }
    }

    cout << "Dane wczytano z pliku XML: " << nazwaPliku << endl;
}

//uwaga - nie trzeba dbac o destruktory bo vectory i shared_ptr robią za mnie robote
