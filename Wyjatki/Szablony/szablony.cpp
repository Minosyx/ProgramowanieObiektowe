#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node<T> *prev;
};

template <class T>
class List : public Node<T>
{
    Node<T> *head;
    Node<T> *tail;

public:
    List() : head(nullptr), tail(nullptr) {}
    void addStart(T);
    void addEnd(T);
    void remStart();
    void remEnd();
    void remAll();
    void remEl(T, int = 1);
    void show();
    bool emptyCheck();
    ~List() { remAll(); };
};

template <class T>
void List<T>::addStart(T val)
{
    Node<T> *element;
    try
    {
        element = new Node<T>;
        element->data = val;
        element->prev = nullptr;
        element->next = head;
        if (!tail)
            tail = element;
        if (head)
            head->prev = element;
        head = element;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

template <class T>
void List<T>::addEnd(T val)
{
    Node<T> *element;
    try
    {
        element = new Node<T>;
        element->data = val;
        element->next = nullptr;
        element->prev = tail;
        if (tail)
            tail->next = element;
        if (!head)
            head = element;
        tail = element;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

template <class T>
void List<T>::remStart()
{
    Node<T> *p;
    try
    {
        p = head;
        if (head == tail)
            tail = nullptr;
        if (!head)
            throw length_error("Lista jest pusta!");
        head = head->next;
        if (head)
            head->prev = nullptr;
        delete p;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

template <class T>
void List<T>::remEnd()
{
    Node<T> *p;
    try
    {
        p = tail;
        if (head == tail)
            head = nullptr;
        if (!tail)
            throw length_error("Lista jest pusta!");
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        delete p;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

template <class T>
void List<T>::remAll()
{
    while (head)
        remStart();
}

template <class T>
void List<T>::remEl(T val, int amount)
{
    Node<T> **it = nullptr;
    Node<T> *p = nullptr;
    try
    {
        if (!head && !tail)
            throw length_error("Lista jest pusta!");
        it = &head;
        int counter = 0;
        while(*it && amount > counter){
            while (*it && (*it)->data != val)
            {
                it = &(*it)->next;
            }
            if (!(*it))
                return;
            p = *it;
            if ((*it)->next && (*it)->prev)
                (*it)->next->prev = (*it)->prev;
            else if ((*it)->next)
                (*it)->next->prev = nullptr;
            if ((*it)->next)
                *it = (*it)->next;
            else
                *it = 0;
            if (p == head)
                head = head->next;
            if (p == tail)
                tail = tail->prev;
            delete p;
            counter++;
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

template <class T>
bool List<T>::emptyCheck()
{
    if (!head && !tail)
        return true;
    else
        return false;
}

template <class T>
void List<T>::show()
{
    Node<T> *it;
    try
    {
        if (!head)
            throw length_error("Lista jest pusta!");
        it = head;
        while (it)
        {
            cout << it->data << " => ";
            it = it->next;
        }
        cout << "|" << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}

int main()
{
    List<string> lista;

    // cout << lista.emptyCheck() << endl;
    // lista.show();
    // lista.addStart("Jacek");
    // lista.addEnd("Marta");
    // lista.addEnd("Michał");
    // lista.addStart("Daria");
    // lista.show();
    // cout << lista.emptyCheck() << endl;
    // lista.remStart();
    // lista.show();
    // lista.remEnd();
    // lista.show();
    // lista.remAll();
    // lista.show();
    // lista.addEnd("Michał");
    // lista.addStart("Jacek");
    // lista.addEnd("Marta");
    // lista.show();
    // lista.remEl("Michał");
    // lista.remEl("Marta");
    // lista.remEl("Jacek");
    // lista.show();
    // lista.addStart("Mikołaj");
    // lista.show();
    // lista.remAll();

    // lista.addStart("Jacek");
    // lista.addEnd("Marta");
    // lista.addEnd("Michał");
    // lista.addStart("Daria");
    // lista.addStart("Michał");
    // lista.show();
    // lista.remEl("Michał", 2);
    // lista.show();

    // List<double> lista;
    // lista.addStart(5.3);
    // lista.addEnd(6.7);
    // lista.addStart(4.2);
    // lista.addStart(4.2);
    // lista.remEl(4.2, 2);
    // lista.show();

    // List<int> lista;

    // // lista.addStart(5);
    // // lista.addEnd(6);
    // // lista.addStart(7);
    // // lista.addEnd(8);
    // // lista.addStart(5);
    // // lista.remEl(5, 2);
    // // lista.show();

    // lista.addStart(5);
    // lista.addStart(5);
    // lista.addStart(6);
    // lista.addStart(5);
    // lista.addStart(5);
    // lista.addStart(6);
    // lista.addStart(5);
    // lista.addStart(5);
    // lista.addStart(6);
    // lista.addEnd(6);
    // lista.show();
    // lista.remEl(5, 5);
    // lista.show();
}