#pragma once
#include "osoba.h"
#include <list>

class Student : public Osoba
{
    list<float> tablicaOcen;

public:
    Student(const char *, const char *, const unsigned, const list<float> &);
    ~Student() { tablicaOcen.clear(); }
    float sredniaOcen();
    float najlepszaOcena();
    float najgorszaOcena();
    void dodajOcene(const float, const int = 1);
    void dodajOcene(const list<float> &);
    void usunOcene(const float, const int = 1);
    void wypisz();
};