#include <iostream>
#include <list>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;

class Student
{
    char *imie, *nazwisko;
    unsigned rokUrodzenia;
    list<float> tablicaOcen;

public:
    Student(const char *const &imie, const char * const &nazwisko, const unsigned rokUrodzenia, list<float> const &tablicaOcen)
    {
        this->imie = new char[strlen(imie) + 1];
        this->nazwisko = new char[strlen(nazwisko) + 1];
        strcpy(this->imie, imie);
        strcpy(this->nazwisko, nazwisko);
        this->rokUrodzenia = rokUrodzenia;
        //copy(tablicaOcen.begin(), tablicaOcen.end(), back_inserter(this->tablicaOcen));
        copy(tablicaOcen.begin(), tablicaOcen.end(), this->tablicaOcen.begin());
    }
    ~Student()
    {
        delete[] imie, nazwisko;
        tablicaOcen.clear();
    }
    float sredniaOcen()
    {
        //list<float>::iterator it;
        float sum = 0;
        float gradeAmount = 0;
        /*
        for(it = tablicaOcen.begin(); it != tablicaOcen.end(); ++it){
            sum += *it;
            gradeAmount++;
        }
        */
        for (auto const &it : tablicaOcen)
        {
            sum += it;
            gradeAmount++;
        }
        if (gradeAmount == 0)
            return 0;
        return sum / gradeAmount;
    }
    float najlepszaOcena()
    {
        list<float>::iterator it;
        it = max_element(tablicaOcen.begin(), tablicaOcen.end());
        return *it;
    }
    float najgorszaOcena()
    {
        list<float>::iterator it;
        it = min_element(tablicaOcen.begin(), tablicaOcen.end());
        return *it;
    }
    void dodajOcene(float nowaOcena, int amount = 1)
    {
        int i = 0;
        while (i < amount)
        {
            tablicaOcen.push_back(nowaOcena);
            i++;
        }
    }
    void dodajOcene(list<float> const &tablicaOcen)
    {
        this->tablicaOcen.insert(this->tablicaOcen.end(), tablicaOcen.begin(), tablicaOcen.end());
    }
    void usunOcene(float ocena, int amount = 1)
    {
        int i = 0;
        list<float>::iterator it;
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
    int wiek()
    {
        time_t teraz = time(NULL);
        unsigned aktualnyRok = 1900 + localtime(&teraz)->tm_year;
        return aktualnyRok - rokUrodzenia;
    }
    void wypisz()
    {
        cout << "Student" << endl
             << imie << " " << nazwisko << endl;
        cout << "Rok urodzenia: " << rokUrodzenia << endl;
        cout << "Oceny: " << endl;
        for (auto const &it : tablicaOcen)
        {
            cout << it << ", ";
        }
        cout << endl;
    }
};

int main()
{
    Student *jankowalski = new Student("Jan", "Kowalski", 1999, {1, 2, 3, 4, 5, 6});
    jankowalski->dodajOcene(4, 5);
    jankowalski->usunOcene(4, 2);
    jankowalski->dodajOcene(7);
    jankowalski->dodajOcene({1, 2, 3, 4});
    jankowalski->wypisz();
    float sr = jankowalski->sredniaOcen();
    float best = jankowalski->najlepszaOcena();
    float worst = jankowalski->najgorszaOcena();
    cout << "Średnia ocen: " << sr << endl;
    cout << "Najlepsza ocena: " << best << endl;
    cout << "Najgorsza ocena: " << worst << endl;
    int w = jankowalski->wiek();
    cout << "Wiek: " << w << endl;
    delete jankowalski;
    return 0;
}