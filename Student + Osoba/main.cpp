#include <iostream>
#include "osoba.cpp"
#include "student.cpp"

int main(){
    Osoba jankowalski("Jan", "Kowalski", 2003);
    Osoba kubanowak("Jakub", "Nowak", 2002);
    Student johnsmith("John", "Smith", 1998, {5, 4, 3, 4});
    Student jackmiller("Jack", "Miller", 2003, {3, 4, 2, 4, 3});

    Osoba *osobyTab[4];
    osobyTab[0] = &jankowalski;
    osobyTab[1] = &kubanowak;
    osobyTab[2] = &johnsmith;
    osobyTab[3] = &jackmiller;

    jackmiller.sredniaOcen();

    johnsmith.dodajOcene(1);
    johnsmith.usunOcene(4, 2);
    johnsmith.dodajOcene({1, 2, 3});

    int size = sizeof(osobyTab) / sizeof(Osoba *);

    for (int i = 0; i < size; i++){
        osobyTab[i]->wypisz();
        cout << endl << endl << endl;
    }

    cout << johnsmith.getImie() << endl
         << johnsmith.getNazwisko() << endl
         << johnsmith.getRokUrodzenia() << endl
         << johnsmith.wiek() << endl;

    cout << endl;

    cout << kubanowak.getImie() << endl
         << kubanowak.getNazwisko() << endl
         << kubanowak.getRokUrodzenia() << endl
         << kubanowak.wiek() << endl;
}
