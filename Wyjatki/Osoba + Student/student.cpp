#include <iostream>
#include <list>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "student.h"
using namespace std;

Student::Student(const char *imie, const char *nazwisko, const unsigned rokUrodzenia, const list<float> &tablicaOcen) try : Osoba(imie, nazwisko, rokUrodzenia)
{
    time_t teraz = time(NULL);
    unsigned check = 1900 + localtime(&teraz)->tm_year - 18;
    if (rokUrodzenia > check)
        throw invalid_argument("Niewłaściwy rok urodzenia (osoba za młoda na bycie studentem)!");
    copy(tablicaOcen.begin(), tablicaOcen.end(), back_inserter(this->tablicaOcen));
}
catch (exception &e){
    cerr << e.what() << endl;
}

float Student::sredniaOcen()
{
    float sum = 0;
    int gradeAmount = 0;
    try
    {
        for (auto const &it : tablicaOcen)
        {
            sum += it;
            gradeAmount++;
        }
        if (gradeAmount == 0)
            throw domain_error("Brak ocen!");
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    return sum / gradeAmount;
}

float Student::najlepszaOcena()
{
    list<float>::iterator it;
    it = max_element(tablicaOcen.begin(), tablicaOcen.end());
    return *it;
}

float Student::najgorszaOcena()
{
    list<float>::iterator it;
    it = min_element(tablicaOcen.begin(), tablicaOcen.end());
    return *it;
}

void Student::dodajOcene(const float nowaOcena, const int amount)
{
    int i = 0;
    if (amount <= 0)
        return;
    try
    {
        while (i < amount)
        {
            if (nowaOcena < 2 || nowaOcena > 5)
                throw out_of_range("Ocena wychodzi poza zakres!");
            tablicaOcen.push_back(nowaOcena);
            i++;
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

void Student::dodajOcene(const list<float> &tablicaOcen)
{
    int check = 0;
    for (auto const &it : tablicaOcen)
    {
        if (it < 2 || it > 5)
        {
            check = 1;
            continue;
        }
        this->tablicaOcen.push_back(it);
    }
    try
    {
        if (check)
            throw out_of_range("Jedna lub więcej ocen nie mieściły się w przedziale!");
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

void Student::usunOcene(const float ocena, const int amount)
{
    int i = 0;
    list<float>::iterator it;
    if (amount <= 0 || ocena < 2 || ocena > 5)
        return;
    for (it = tablicaOcen.begin(); it != tablicaOcen.end();)
    {
        if (*it == ocena)
        {
            tablicaOcen.erase(it++);
            i++;
        }
        else
        {
            it++;
        }
        if (i == amount)
            break;
    }
}

void Student::wypisz()
{
    personPrint("Student");
    string frame;
    string title;
    stringstream sstream;
    cout << setfill('*') << setw(width) << "\n";
    frame = "*";
    title = "Karta ocen";
    spacer(frame);
    fill(title, frame);
    spacer(frame);
    sstream.str("");
    string oceny;
    int i = 0;
    for (auto const &it : tablicaOcen)
    {
        sstream << it << ", ";
        i += 3;
        if (i + 3 >= width / 2)
        {
            oceny = sstream.str();
            fill(oceny, frame);
            sstream.str("");
            i = 0;
        }
    }
    oceny = sstream.str();
    fill(oceny, frame);
    spacer(frame);
    cout << setfill('*') << setw(width) << "\n";
}