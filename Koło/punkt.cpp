#include <iostream>
#include "punkt.h"
using namespace std;

void Punkt::przesun(float a, float b){
    x += a;
    y += b;
}

void Punkt::przesun(Punkt p){
    x = p.x;
    y = p.y;
}

void Punkt::odbij(){
    x = x == 0 ? 0 : -x;
    y = y == 0 ? 0 : -y;
}

void Punkt::wypisz(){
    cout << "(" << x << ", " << y << ")" << endl;
}

float Punkt::getX(){
    return x;
}

float Punkt::getY(){
    return y;
}