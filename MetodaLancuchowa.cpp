#include "MetodaLancuchowa.hpp"

Node::Node(int klucz, int wartosc) : klucz(klucz), wartosc(wartosc), next(nullptr){}

MetodaLancuchowa::MetodaLancuchowa(int r){
    rozmiar = r;
    tablica = new Node*[rozmiar];
    for(int i = 0; i < rozmiar; i++){
        tablica[i] = nullptr;
    }
}

MetodaLancuchowa::~MetodaLancuchowa(){
    for(int i = 0; i < rozmiar; i++){
        Node* curr = tablica[i];
        while(curr != nullptr){
            Node* prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    delete[] tablica;
}

int MetodaLancuchowa::funkcjaMieszajaca(int klucz){
    int kubelek = klucz % rozmiar;
    if(kubelek < 0){
        kubelek += rozmiar;
    }
    return kubelek;
}

void MetodaLancuchowa::insert(int klucz, int wartosc){
    int index = funkcjaMieszajaca(klucz);

    Node* curr = tablica[index];
    while(curr != nullptr){
        if(curr->klucz == klucz){
            curr->wartosc = wartosc;
            return;
        }
        curr = curr->next;
    }
    Node* newNode = new Node(klucz, wartosc);
    newNode->next = tablica[index];
    tablica[index] = newNode;
}

void MetodaLancuchowa::remove(int klucz){
    int index = funkcjaMieszajaca(klucz);

    Node* curr = tablica[index];
    Node* prev = nullptr;

    while(curr != nullptr && curr->klucz != klucz){
        prev = curr;
        curr = curr->next;
    }

    if(curr == nullptr){
        return;
    }

    if(prev == nullptr){
        tablica[index] = curr->next;
    }else{
        prev->next = curr->next;
    }
    delete curr;
}