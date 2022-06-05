#include <iostream>
#include <cmath>
#include <cstring>
#include <sstream>
using namespace std;

class Wielomian
{
    unsigned int stopien;
    float *wspolczynniki;

public:
    Wielomian()
    {
        stopien = 0;
        wspolczynniki = new float[stopien + 1];
        wspolczynniki[0] = 1;
    }
    Wielomian(const unsigned int stopien, const float * wspolczynniki)
    {
        this->stopien = stopien;
        this->wspolczynniki = new float[stopien + 1];
        memcpy(this->wspolczynniki, wspolczynniki, sizeof(float) * (stopien + 1));
    }
    Wielomian &operator=(const Wielomian &w)
    {
        delete[] this->wspolczynniki;
        this->stopien = w.stopien;
        this->wspolczynniki = new float[w.stopien + 1];
        memcpy(this->wspolczynniki, w.wspolczynniki, sizeof(float) * (w.stopien + 1));
        return *this;
    }
    Wielomian(const Wielomian &w)
    {
        wspolczynniki = 0;
        *this = w;
    }
    Wielomian operator+(const Wielomian &w)
    {
        const Wielomian *dluzszy, *krotszy;
        if (stopien > w.stopien)
        {
            dluzszy = this;
            krotszy = &w;
        }
        else
        {
            dluzszy = &w;
            krotszy = this;
        }
        float *sumaWspolczynnikow = new float[dluzszy->stopien + 1];
        for (int i = 0; i <= dluzszy->stopien; i++)
        {
            if (i <= krotszy->stopien)
            {
                sumaWspolczynnikow[i] = krotszy->wspolczynniki[i] + dluzszy->wspolczynniki[i];
            }
            else
            {
                sumaWspolczynnikow[i] = dluzszy->wspolczynniki[i];
            }
        }
        return Wielomian(dluzszy->stopien, sumaWspolczynnikow);
    }
    Wielomian operator-(const Wielomian &w)
    {
        const Wielomian *dluzszy, *krotszy;
        if (stopien > w.stopien)
        {
            dluzszy = this;
            krotszy = &w;
        }
        else
        {
            dluzszy = &w;
            krotszy = this;
        }
        float *roznicaWspolczynnikow = new float[dluzszy->stopien + 1];
        for (int i = 0; i <= dluzszy->stopien; i++)
        {
            if (i <= krotszy->stopien)
            {
                roznicaWspolczynnikow[i] = this->wspolczynniki[i] - w.wspolczynniki[i];
            }
            else
            {
                roznicaWspolczynnikow[i] = (this == dluzszy) ? this->wspolczynniki[i] : -w.wspolczynniki[i];
            }
        }
        return Wielomian(dluzszy->stopien, roznicaWspolczynnikow);
    }
    friend ostream &operator<<(ostream &, const Wielomian &);
    friend istream &operator>>(istream &, Wielomian &);
    float operator()(const float num)
    {
        float sum = 0;
        for (int i = 0; i <= this->stopien; i++)
        {
            sum += this->wspolczynniki[i] * pow(num, i);
        }
        return sum;
    }
    float &operator[](const int num)
    {
        if (num >= 0 && num <= stopien)
            return this->wspolczynniki[num];
    }
    const float operator[](const int num) const
    {
        if (num >= 0 && num <= stopien)
            return this->wspolczynniki[num];
        else
            return 0;
    }
    explicit operator float *()
    {
        float *w = new float[this->stopien + 1];
        memcpy(w, this->wspolczynniki, (stopien + 1) * sizeof(float));
        return w;
    }
    explicit operator string() const
    {
        stringstream sstream;
        for (int i = this->stopien; i >= 0; i--)
        {
            if (i != 0 && this->wspolczynniki[i] > 0)
                sstream << "+" << this->wspolczynniki[i] << "x^" << i;
            else if (i != 0 && this->wspolczynniki[i] < 0)
                sstream << this->wspolczynniki[i] << "x^" << i;
            else if (i == 0 && this->wspolczynniki[i] > 0)
                sstream << "+" << this->wspolczynniki[i];
            else if (i == 0 && this->wspolczynniki[i] < 0)
                sstream << this->wspolczynniki[i];
            else if (i == 0 && this->stopien == 0)
                sstream << this->wspolczynniki[i];
            else
                continue;
        }
        string napis = sstream.str();
        if (napis[0] == '+')
            return napis.substr(1);
        else
            return napis;
    }
    unsigned int getStopien()
    {
        return this->stopien;
    }
    ~Wielomian()
    {
        delete[] wspolczynniki;
    }
};

ostream &operator<<(ostream &os, const Wielomian &w)
{
    string wielomian = string(w);
    os << "Wielomian stopnia " << w.stopien << " o postaci: ";
    os << wielomian << endl;
    return os;
}

istream &operator>>(istream &is, Wielomian &w)
{
    int check = -1;
    while(check < 0){
        cout << "Podaj stopien wielomianu: ";
        is >> check;
    }
    w.stopien = check;
    cout << endl << "Podaj kolejne wspolczynniki:" << endl;
    delete[] w.wspolczynniki;
    w.wspolczynniki = new float[w.stopien + 1];
    for (int i = 0; i <= w.stopien; i++)
    {
        cout << "Podaj x^" << i << ": ";
        is >> w.wspolczynniki[i];
    }
    return is;
}

void wypiszPierwszyWspolczynnik(const Wielomian &w)
{
    cout << w[0] << endl;
}

int main()
{
    float wsp1[4] = {5, 1, 2, 4};
    float wsp[3] = {1, -6, 8};
    Wielomian w(sizeof(wsp) / sizeof(float) - 1, wsp);
    Wielomian w1(sizeof(wsp1) / sizeof(float) - 1, wsp1);
    Wielomian w2;
    Wielomian w3(w);
    Wielomian n;
    Wielomian w4, w5, w6;
    n = w + w1;
    string ws, ws1, ws2, ws3;
    float k;
    k = w(2.7);
    cout << k << endl;
    ws = string(n);
    ws2 = string(w2);
    ws3 = string(w3);
    cout << ws << endl;
    cout << ws2 << endl;
    w2 = w1;
    ws2 = string(w2);
    cout << ws2 << endl;
    cout << ws3 << endl;
    cout << w << endl;
    // cin >> w4;
    // cout << w4 << endl;
    // w5 = w4 + w1;
    // cout << w5 << endl;
    w6 = w - w1;
    cout << w6 << endl;
    w6 = w1 - w;
    cout << w6 << endl;
    float *tab = (float *)w1;
    cout << w << endl;

    int x = 0;
    if (w.getStopien() >= x && x >= 0)
        w[x] = 4;
    cout << w << endl;
    wypiszPierwszyWspolczynnik(w);

    float wsp2[4] = {0, -2, 0, 5};
    Wielomian test(sizeof(wsp2) / sizeof(float) - 1, wsp2);
    cout << test << endl;

    return 0;
}