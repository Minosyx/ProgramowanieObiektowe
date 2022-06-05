#include <iostream>
using namespace std;

class Punkt{
    float x, y;
public:
    Punkt(float x = 0, float y = 0){
        this->x = x;
        this->y = y;
    }
    void przesun(float a, float b){
        x += a;
        y += b;
    }
    void przesun(Punkt p){
        x = p.x;
        y = p.y;
    }
    void odbij(){
        x = x == 0 ? 0 : -x;
        y = y == 0 ? 0 : -y;
    }
    void wypisz(){
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main(){
    /*
    Punkt p1;
    p1.wypisz();
    p1.przesun(2, 3);
    p1.wypisz();
    p1.przesun(-1, 2);
    p1.wypisz();

    Punkt p2(1, 1);
    p2.wypisz();
    p1.przesun(p2);
    cout << "P1: ";
    p1.wypisz();

    p1.odbij();
    p1.wypisz();

    Punkt p(0, 0);
    p1.przesun(p);
    p1.odbij();
    p1.wypisz();
    p2.wypisz();
    */
}