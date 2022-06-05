#pragma once
#include <sstream>
#include <cstring>
using namespace std;

class Osoba{
    char *imie, *nazwisko;
    unsigned rokUrodzenia;
protected:
    int width = 80;
    void fill(const string &, const string &);
    void spacer(const string &);
    void personPrint(const string &);
public:
    Osoba(const char*, const char*, const unsigned);
    ~Osoba() { delete[] imie; delete[] nazwisko; }
    char *getImie() const { return imie; }
    char *getNazwisko() const { return nazwisko; }
    unsigned getRokUrodzenia() const { return rokUrodzenia; }
    int wiek();
    virtual void wypisz();
};