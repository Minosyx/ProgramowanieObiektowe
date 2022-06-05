#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Zespolona
{
    float re, im;

public:
    Zespolona(const float re = 0, const float im = 0)
    {
        this->re = re;
        this->im = im;
    }
    Zespolona(const Zespolona &z1)
    {
        this->re = z1.re;
        this->im = z1.im;
    }
    Zespolona &operator=(const Zespolona &z1)
    {
        this->re = z1.re;
        this->im = z1.im;
        return *this;
    }
    Zespolona &operator+=(const Zespolona &z1)
    {
        this->re += z1.re;
        this->im += z1.im;
        return *this;
    }
    Zespolona &operator-=(const Zespolona &z1)
    {
        this->re -= z1.re;
        this->im -= z1.im;
        return *this;
    }
    Zespolona &operator*=(const Zespolona &z1)
    {
        Zespolona z(*this);
        this->re = (z.re * z1.re) - (z.im * z1.im);
        this->im = (z.im * z1.re) + (z.re * z1.im);
        return *this;
    }
    Zespolona &operator/=(const Zespolona &z1)
    {
        Zespolona z(*this);
        float mian = z1.re * z1.re + z1.im * z1.im;
        if (!mian) throw domain_error("Nie można dzielić przez zero!\n");  
        this->re = (z.re * z1.re + z.im * z1.im) / mian;
        this->im = (z.im * z1.re - z.re * z1.im) / mian;
        return *this;
    }
    Zespolona operator+(const Zespolona &z1)
    {
        Zespolona z(*this);
        z += z1;
        return z;
    }
    Zespolona operator+(const int num)
    {
        Zespolona z(*this);
        z.re += num;
        return z;
    }
    Zespolona operator-(const Zespolona &z1)
    {
        Zespolona z(*this);
        z -= z1;
        return z;
    }
    Zespolona operator-(const int num)
    {
        Zespolona z(*this);
        z.re -= num;
        return z;
    }
    Zespolona operator*(const Zespolona &z1)
    {
        Zespolona z(*this);
        z *= z1;
        return z;
    }
    Zespolona operator*(const int num)
    {
        Zespolona z(*this);
        z.re *= num;
        z.im *= num;
        return z;
    }
    Zespolona operator/(const Zespolona &z1)
    {
        Zespolona z(*this);
        z /= z1;
        return z;
    }
    Zespolona operator/(const int num)
    {
        Zespolona z(*this);
        if (!num) throw domain_error("Nie można dzielić przez zero!\n");
        z.re /= num;
        z.im /= num;
        return z;
    }
    bool operator==(const Zespolona &z1)
    {
        return (this->re == z1.re && this->im == z1.im) ? true : false;
    }
    bool operator!=(const Zespolona &z1)
    {
        return (this->re != z1.re || this->im != z1.im) ? true : false;
    }
    bool operator>(const Zespolona &z1)
    {
        if (this->im && z1.im) throw domain_error("Liczby zespolone nie posiadają relacji porządku\n");
        if (this->re > z1.re)
            return true;
        if (this->re <= z1.re)
            return false;
    }
    bool operator<(const Zespolona &z1)
    {
        if (this->im && z1.im) throw domain_error("Liczby zespolone nie posiadają relacji porządku\n");
        if (this->re < z1.re)
            return true;
        if (this->re >= z1.re)
            return false;
    }
    Zespolona &operator++()
    {
        ++(this->re);
        return *this;
    }
    Zespolona operator++(int)
    {
        return Zespolona(re++, im);
    }
    Zespolona &operator--()
    {
        --(this->re);
        return *this;
    }
    Zespolona operator--(int)
    {
        return Zespolona(re--, im);
    }
    explicit operator int();
    explicit operator double();
    friend ostream &operator<<(ostream &, const Zespolona &);
    friend istream &operator>>(istream &, Zespolona &);
};

ostream &operator<<(ostream &os, const Zespolona &z)
{
    os << "Współrzędne zespolone: " << z.re << " + " << z.im << "i" << endl;
    return os;
}
istream &operator>>(istream &is, Zespolona &z)
{
    cout << "Wprowadź współrzędne punktu na płaszczyźnie zespolonej" << endl;
    cout << "Oddziel część rzeczywistą od urojonej spacją!" << endl;
    cout << "z: ";
    is >> z.re >> z.im;
    return is;
}

Zespolona::operator int()
{
    return sqrt(re * re + im * im);
}

Zespolona::operator double()
{
    return sqrt(re * re + im * im);
}

int main()
{
    Zespolona t(4, 5), t1(3, 5), t2(4, 6), t3(4, 4), t4(5, 5);
    Zespolona z(6, 7);
    Zespolona z1(1, 4);
    Zespolona z2(2, 1);
    Zespolona z3 = z;
    Zespolona z4(z);
    Zespolona z5(0, 0);
    Zespolona z6(1, 0);
    Zespolona z7(2, 0);
    Zespolona z8 = z6;
    Zespolona test;
    bool res = true;
    // test operacji arytmetycznych, oraz przypisania z operacjami arytmetycznymi
    // test = z + z1;
    // cout << test;
    // test = z + 2;
    // cout << test;
    // test = z - z2;
    // cout << test;
    // test = z - 1;
    // cout << test;
    // test = z * z1;
    // cout << test;
    // test = z * 3;
    // cout << test;
    // test = z / z2;
    // cout << test;
    // test = z / 2;
    // cout << test;
    // test = z;
    // cout << test;
    // test += z1;
    // cout << test;
    // test -= z2;
    // cout << test;
    // test *= z1;
    // cout << test;
    // test /= z2;
    // cout << test;

    // test wyjątków
    // test = test / 0;
    // test = test / z5;
    // test /= z5;
    // cout << test;

    // test operatorów logicznych
    // cout << "==" << endl;
    // res = z == z3;
    // cout << res << endl;
    // res = z == z2;
    // cout << res << endl << endl;
    // cout << "!=" << endl;
    // res = z != z4;
    // cout << res << endl;
    // res = z != z2;
    // cout << res << endl << endl;

    // cout << ">" << endl;
    // res = t > t1;
    // cout << res << endl;
    // res = t > t2;
    // cout << res << endl;
    // res = t > t3;
    // cout << res << endl;
    // res = t > t4;
    // cout << res << endl << endl;
    // res = z7 > z6;
    // cout << res << endl;

    // cout << "<" << endl;
    // res = t1 < t;
    // cout << res << endl;
    // res = t2 < t;
    // cout << res << endl;
    // res = t3 < t;
    // cout << res << endl;
    // res = t4 < t;
    // cout << res << endl << endl;

    // test inkrementacji i dekrementacji
    // Zespolona tmp = z;
    // test = tmp++;
    // cout << tmp;
    // cout << test;
    // tmp = z;
    // test = ++tmp;
    // cout << tmp;
    // cout << test;
    // tmp = z;
    // test = tmp--;
    // cout << tmp;
    // cout << test;
    // tmp = z;
    // test = --tmp;
    // cout << tmp;
    // cout << test;

    // test strumieni i rzutowania
    // cout << z;
    // cin >> z;
    // cout << z;
    // int x = (int)z;
    // double y = (double)z;
    // cout << x << endl;
    // cout << y << endl;
    return 0;
}