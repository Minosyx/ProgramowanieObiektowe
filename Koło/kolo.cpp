#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "punkt.cpp"
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Kolo{
    Punkt srodek;
    float promien;
    void fill(int width, int dl);
public:
    Kolo(Punkt srodek = Punkt(0, 0), float promien = 1){
        if(promien <= 0){
            cout << "Podano niedozwolona dlugosc promienia!" << endl << "Nastapi ustawienie wartosci domyslnej!" << endl;
            this->promien = 1;
        }
        else{
            this->promien = promien;
        }
        this->srodek = srodek;
    }

    float srednica(){
        return promien * 2;
    }

    float obwod(){
        return 2 * M_PI * promien;
    }

    float pole(){
        return M_PI * pow(promien, 2);
    }

    void zmienPromien(float nowyPromien){
        if(nowyPromien <= 0){
            cout << "Podano niedozwolona dlugosc promienia!" << endl << "Zmiana promienia zostala odrzucona!" << endl;
        }
        else{
            promien = nowyPromien;
        }
    }

    void przesun(float a, float b){
        srodek.przesun(a, b);
    }

    void przesunAlt(float a, float b){
        float x, y;
        x = srodek.getX() + a;
        y = srodek.getY() + b;
        Punkt srodek(x, y);
        this->srodek = srodek;
    }

    void przesun(Punkt p){
        srodek.przesun(p);
    }

    void przesunAlt(Punkt p){
        Punkt srodek(p.getX(), p.getY());
        this->srodek = srodek;
    }

    void wypisz();
};

void Kolo::fill(int width, int dl){
    for (int i = 0; i < (int)(width - dl - 3) / 2; i++)
    {
        cout << " ";
    }
}

void Kolo::wypisz(){
    int width = 80;
    stringstream sstream;
    sstream << "Srodek : (" << srodek.getX() << ", " << srodek.getY() << ")";
    string srodek = sstream.str();
    sstream.str("");
    sstream << "Promien : " << promien;
    string promien = sstream.str();
    cout << setfill('*') << setw(width) << "\n";
    cout << "*";
    fill(width, srodek.length());
    cout << srodek;
    fill(width, srodek.length());
    if (srodek.length() % 2 == 0)
        cout << " ";
    cout << "*\n*";
    fill(width, promien.length());
    cout << promien;
    fill(width, promien.length());
    if (promien.length() % 2 == 0)
        cout << " ";
    cout << "*\n";
    cout << setfill('*') << setw(width) << "\n";
}

int main(){
    Punkt p(-3, 14);
    Kolo k1({2, 8}, 6);
    Kolo k2;

    k1.przesun(-12, 2);
    k1.wypisz();
    k1.zmienPromien(5);
    // k1.przesunAlt(12, 2);
    k1.przesun(p);
    // k1.przesunAlt(p);
    k1.wypisz();
    k2.wypisz();
    float srednica = k1.srednica();
    float obwod = k1.obwod();
    float pole = k1.pole();
    cout << srednica << endl << obwod << endl << pole << endl;
}