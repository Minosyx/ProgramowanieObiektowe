#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "osoba.h"
using namespace std;

Osoba::Osoba(const char *imie, const char *nazwisko, const unsigned rokUrodzenia){
    this->imie = new char[strlen(imie) + 1];
    this->nazwisko = new char[strlen(nazwisko) + 1];
    strcpy(this->imie, imie);
    strcpy(this->nazwisko, nazwisko);
    this->rokUrodzenia = rokUrodzenia;
}

int Osoba::wiek(){
    time_t teraz = time(NULL);
    unsigned aktualnyRok = 1900 + localtime(&teraz)->tm_year;
    return aktualnyRok - rokUrodzenia;
}

void Osoba::spacer(const string &frame){
    cout << frame;
    cout << setfill(' ') << setw(width - 2);
    cout << frame << endl;
}

void Osoba::fill(const string &text, const string &frame){
    int dl = text.length();
    char znak[2] = " ";
    cout << frame;
    for (int i = 0; i < (int)(width - dl - 3) / 2; i++){
        cout << znak;
    }
    cout << text;
    for (int i = 0; i < (int)(width - dl - 3) / 2; i++){
        cout << znak;
    }
    if (dl % 2 == 0)
        cout << znak;
    cout << frame << endl;
}

void Osoba::personPrint(const string &title){
    cout << setfill('-') << setw(width) << "\n";
    string frame = "|";
    spacer(frame);
    fill(title, frame);
    spacer(frame);
    stringstream sstream;
    sstream << getImie() << " " << getNazwisko();
    string name = sstream.str();
    sstream.str("");
    fill(name, frame);
    sstream << "Rok urodzenia: " << getRokUrodzenia();
    string birth = sstream.str();
    spacer(frame);
    fill(birth, frame);
    spacer(frame);
    cout << setfill('-') << setw(width) << "\n";
    cout << endl;
}

void Osoba::wypisz(){
    personPrint("Osoba");
}