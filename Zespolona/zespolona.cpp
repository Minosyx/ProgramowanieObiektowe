#include <iostream>
#include <cmath>
using namespace std;

class Zespolona{
    float re, im;
public:
    Zespolona(const float &re = 0, const float &im = 0){
        this->re = re;
        this->im = im;
    }
    Zespolona operator+(const Zespolona &z1){
        Zespolona z;
        z.re = this->re + z1.re;
        z.im = this->im + z1.im;
        return z;
    }
    Zespolona operator+(const int &num){
        Zespolona z;
        z.re = this->re + num;
        z.im = this->im;
        return z;
    }
    Zespolona operator-(const Zespolona &z1){
        Zespolona z;
        z.re = this->re - z1.re;
        z.im = this->im - z1.im;
        return z;
    }
    Zespolona operator-(const int &num){
        Zespolona z;
        z.re = this->re - num;
        z.im = this->im;
        return z;
    }
    Zespolona operator*(const Zespolona &z1){
        Zespolona z;
        z.re = (this->re * z1.re) - (this->im * z1.im);
        z.im = (this->im * z1.re) + (this->re * z1.im);
        return z;
    }
    Zespolona operator*(const int &num){
        Zespolona z;
        z.re = this->re * num;
        z.im = this->im * num;
        return z;
    }
    Zespolona operator/(const Zespolona &z1){
        Zespolona z;
        float mian = z1.re * z1.re + z1.im * z1.im;
        z.re = (this->re * z1.re + this->im * z1.im) / mian;
        z.im = (this->im * z1.re - this->re * z1.im) / mian;
        return z;
    }
    Zespolona operator/(const int &num){
        Zespolona z;
        z.re = this->re / num;
        z.im = this->im / num;
        return z;
    }
    Zespolona & operator=(const Zespolona &z1){
        this->re = z1.re;
        this->im = z1.im;
        return *this;
    }
    Zespolona & operator+=(const Zespolona &z1){
        this->re += z1.re;
        this->im += z1.im;
        return *this;
    }
    Zespolona & operator-=(const Zespolona &z1){
        this->re -= z1.re;
        this->im -= z1.im;
        return *this;
    }
    Zespolona & operator*=(const Zespolona &z1){
        Zespolona z;
        z = *this;
        this->re = (z.re * z1.re) - (z.im * z1.im);
        this->im = (z.im * z1.re) + (z.re * z1.im);
        return *this;
    }
    Zespolona & operator/=(const Zespolona &z1){
        Zespolona z;
        z = *this;
        float mian = z1.re * z1.re + z1.im * z1.im;
        this->re = (z.re * z1.re + z.im * z1.im) / mian;
        this->im = (z.im * z1.re - z.re * z1.im) / mian;
        return *this;
    }
    bool operator==(const Zespolona &z1){
        return (this->re == z1.re && this->im == z1.im) ? true : false;
    }
    bool operator!=(const Zespolona &z1){
        return (this->re != z1.re || this->im != z1.im) ? true : false;
    }
    bool operator>(const Zespolona &z1){
        if(this->re > z1.re) return true;
        if(this->re < z1.re) return false;
        if(this->re == z1.re && this->im > z1.im) return true;
        else return false;
    }
    bool operator<(const Zespolona &z1){
        if(this->re < z1.re) return true;
        if(this->re > z1.re) return false;
        if(this->re == z1.re && this->im < z1.im) return true;
        else return false;
    }
    Zespolona operator++(){
        return Zespolona(++re, im);
    }
    Zespolona operator++(int){
        return Zespolona(re++, im);
    }
    Zespolona operator--(){
        return Zespolona(--re, im);
    }
    Zespolona operator--(int){
        return Zespolona(re--, im);
    }
    explicit operator int();
    explicit operator double();
    friend ostream & operator<<(ostream &, const Zespolona &z);
    friend istream & operator>>(istream &, Zespolona &z);
    void wypisz(){
        cout << "z: " << this->re << " " << this->im << endl;
    }
};

ostream & operator<<(ostream &os, const Zespolona &z){
    os << "Współrzędne zespolone: (" << z.re << ", " << z.im << ")" << endl;
    return os;
}
istream & operator>>(istream &is, Zespolona &z){
    cout << "Wprowadź współrzędne punktu na płaszczyźnie zespolonej" << endl;
    is >> z.re >> z.im;
    return is;
}

Zespolona::operator int(){
    return sqrt(re * re + im * im);
}

Zespolona::operator double(){
    return sqrt(re * re + im * im);
}

int main(){
    Zespolona t(4, 5), t1(3, 5), t2(4, 6), t3(4, 4), t4(4, 5);
    Zespolona z(6, 7);
    Zespolona z1(1, 4);
    Zespolona z2(2, 1);
    Zespolona z3 = z;
    Zespolona test;
    bool res;
                          // test operacji arytmetycznych, oraz przypisania z operacjami arytmetycznymi
    test = z + z1;
    test.wypisz();
    test = z + 2;
    test.wypisz();
    test = z - z2;
    test.wypisz();
    test = z - 1;
    test.wypisz();
    test = z * z1;
    test.wypisz();
    test = z * 3;
    test.wypisz();
    test = z / z2;
    test.wypisz();
    test = z / 2;
    test.wypisz();
    test = z;
    test.wypisz();
    test += z1;
    test.wypisz();
    test -= z2;
    test.wypisz();
    test *= z1;
    test.wypisz();
    test /= z2;
    test.wypisz();
    
    /*                      // test operatorów porównania
    cout << "==" << endl;
    res = z == z3;
    cout << res << endl;
    res = z == z2;
    cout << res << endl << endl;
    cout << "!=" << endl;
    res = z == z2;
    cout << res << endl;
    res = z == z3;
    cout << res << endl << endl;

    cout << ">" << endl;
    res = t > t1;
    cout << res << endl;
    res = t > t2;
    cout << res << endl;
    res = t > t3;
    cout << res << endl;
    res = t > t4;
    cout << res << endl << endl;

    cout << "<" << endl;
    res = t1 < t;
    cout << res << endl;
    res = t2 < t;
    cout << res << endl;
    res = t3 < t;
    cout << res << endl;
    res = t4 < t;
    cout << res << endl << endl;
    */
    /*                      // test inkrementacji i dekrementacji
    test = z++;
    z.wypisz();
    test.wypisz();
    test = ++z;
    z.wypisz();
    test.wypisz();
    test = z--;
    z.wypisz();
    test.wypisz();
    test = --z;
    z.wypisz();
    test.wypisz();
    */
                          // test strumieni
    // cout << z;
    // cin >> z;
    // cout << z;
    int x = (int)z;
    double y = (double)z;
    cout << x << endl;
    cout << y << endl;
    return 0;
}