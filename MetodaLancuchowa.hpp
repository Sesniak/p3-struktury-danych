#pragma once

struct Node{
    int klucz;
    int wartosc;
    Node* next;

    Node(int klucz, int wartosc);
};

class MetodaLancuchowa{
    private:
    Node** tablica;
    int rozmiar;

    int funkcjaMieszajaca(int klucz);

    public:
    MetodaLancuchowa(int r);
    ~MetodaLancuchowa();

    void insert(int klucz, int wartosc);
    void remove(int klucz);
};