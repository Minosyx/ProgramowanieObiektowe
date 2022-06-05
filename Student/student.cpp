#include <iostream>
#include <list>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

class Student{
    char *imie, *nazwisko;
    unsigned rokUrodzenia;
    list<float> tablicaOcen;

    int width = 80;
    void fill(const string &text, const string &frame);
    void spacer(const string &frame);
public:
    Student(const char* imie, const char* nazwisko, const unsigned rokUrodzenia, list<float> const &tablicaOcen){
        this->imie = new char[strlen(imie) + 1];
        this->nazwisko = new char[strlen(nazwisko) + 1];
        strcpy(this->imie, imie);
        strcpy(this->nazwisko, nazwisko);
        this->rokUrodzenia = rokUrodzenia;
        copy(tablicaOcen.begin(), tablicaOcen.end(), back_inserter(this->tablicaOcen));
    }
    ~Student(){
        delete[] imie;
        delete[] nazwisko;
        tablicaOcen.clear();
    }
    float sredniaOcen(){
        float sum = 0;
        int gradeAmount = 0;
        for(auto const &it : tablicaOcen){
            sum += it;
            gradeAmount++;
        }
        if (gradeAmount == 0)
            return 0;
        return sum/gradeAmount;
    }
    float najlepszaOcena(){
        list<float>::iterator it;
        it = max_element(tablicaOcen.begin(), tablicaOcen.end());
        return *it;
    }
    float najgorszaOcena(){
        list<float>::iterator it;
        it = min_element(tablicaOcen.begin(), tablicaOcen.end());
        return *it;
    }
    void dodajOcene(const float nowaOcena, const int amount = 1){
        int i = 0;
        if (amount <= 0)
            return;
        while(i < amount){
            tablicaOcen.push_back(nowaOcena);
            i++;
        }
    }
    void dodajOcene(list<float> const &tablicaOcen){
        this->tablicaOcen.insert(this->tablicaOcen.end(), tablicaOcen.begin(), tablicaOcen.end());
    }    
    void usunOcene(const float ocena, const int amount = 1){
        int i = 0;
        list<float>::iterator it;
        if (amount <= 0)
            return;
        for(it = tablicaOcen.begin(); it != tablicaOcen.end();){
            if(*it == ocena) {
                tablicaOcen.erase(it++);
                i++;
            }else{
                it++;
            }
            if(i == amount) break;
        }
    }
    int wiek(){
        time_t teraz = time(NULL);
        unsigned aktualnyRok = 1900 + localtime(&teraz)->tm_year;
        return aktualnyRok - rokUrodzenia;
    }
    void wypisz();
};

void Student::wypisz()
{
    cout << setfill('-') << setw(width) << "\n";
    string frame = "|";
    string title = "Student";
    spacer(frame);
    fill(title, frame);
    spacer(frame);
    stringstream sstream;
    sstream << imie << " " << nazwisko;
    string name = sstream.str();
    sstream.str("");
    fill(name, frame);
    sstream << "Rok urodzenia: " << rokUrodzenia;
    string birth = sstream.str();
    spacer(frame);
    fill(birth, frame);
    spacer(frame);
    cout << setfill('-') << setw(width) << "\n";
    cout << endl;
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
        if (i + 3 >= width/2)
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

void Student::spacer(const string &frame){
    cout << frame;
    cout << setfill(' ') << setw(width - 2);
    cout << frame << endl;
}

void Student::fill(const string &text, const string &frame){
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

int main(){
    Student *jankowalski = new Student("Jan", "Kowalski", 1999, {4, 4, 4, 4, 4, 4});
    jankowalski->dodajOcene(4.5, 10);
    jankowalski->usunOcene(4, 4);
    jankowalski->dodajOcene(6);
    jankowalski->dodajOcene({1, 2, 3, 4});
    jankowalski->usunOcene(2, 5);
    jankowalski->wypisz();
    float sr = jankowalski->sredniaOcen();
    float best = jankowalski->najlepszaOcena();
    float worst = jankowalski->najgorszaOcena();
    cout << "Srednia ocen: " << setprecision(3) << sr << endl;
    cout << "Najlepsza ocena: " << best << endl;
    cout << "Najgorsza ocena: " << worst << endl;
    int w = jankowalski->wiek();
    cout << "Wiek: " << w << endl;
    delete jankowalski;
    return 0;
}