#include <iostream>
#include <list>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "student.h"
using namespace std;

Student::Student(const char *imie, const char *nazwisko, const unsigned rokUrodzenia, const list<float> &tablicaOcen) : Osoba(imie, nazwisko, rokUrodzenia){
    copy(tablicaOcen.begin(), tablicaOcen.end(), back_inserter(this->tablicaOcen));
}

float Student::sredniaOcen(){
    float sum = 0;
    int gradeAmount = 0;
    for (auto const &it : tablicaOcen)
    {
        sum += it;
        gradeAmount++;
    }
    if (gradeAmount == 0)
        return 0;
    return sum / gradeAmount;
}

float Student::najlepszaOcena(){
    list<float>::iterator it;
    it = max_element(tablicaOcen.begin(), tablicaOcen.end());
    return *it;
}

float Student::najgorszaOcena(){
    list<float>::iterator it;
    it = min_element(tablicaOcen.begin(), tablicaOcen.end());
    return *it;
}

void Student::dodajOcene(const float nowaOcena, const int amount)
{
    int i = 0;
    if (amount <= 0)
        return;
    while (i < amount)
    {
        tablicaOcen.push_back(nowaOcena);
        i++;
    }
}

void Student::dodajOcene(const list<float> &tablicaOcen){
    this->tablicaOcen.insert(this->tablicaOcen.end(), tablicaOcen.begin(), tablicaOcen.end());
}

void Student::usunOcene(const float ocena, const int amount){
    int i = 0;
    list<float>::iterator it;
    if (amount <= 0)
        return;
    for(it = tablicaOcen.begin(); it != tablicaOcen.end();){
        if(*it == ocena){
            tablicaOcen.erase(it++);
            i++;
        }else{
            it++;
        }
        if(i == amount) break;
    }  
}

void Student::wypisz(){
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