#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "MetodaLancuchowa.hpp"
#include "avltable.h"
#include "cuckoo.h"

using namespace std;
using namespace std::chrono;

int main() {
    const int krok = 10000;
    const int maxN = 80000;
    const int seedy = 8;
    const int powtorzenia = 10;

    for (int n = 10000; n <= maxN; n += krok) {

        double mlIns = 0, mlRem = 0;
        double avlIns = 0, avlRem = 0;
        double cukIns = 0, cukRem = 0;

        for (int s = 1; s <= seedy; s++) {
            mt19937 gen(s);
            uniform_int_distribution<> zakresKluczy(1, n * 5); 
            uniform_int_distribution<> zakresWartosci(1, 1000000); 

            vector<int> klucze(n);
            vector<int> wartosci(n);
            for (int i = 0; i < n; i++) {
                klucze[i] = zakresKluczy(gen);
                wartosci[i] = zakresWartosci(gen);
            }



            auto prepML = [&]() {
                vector<MetodaLancuchowa*> struktury(powtorzenia);
                for (int p = 0; p < powtorzenia; p++) {
                    struktury[p] = new MetodaLancuchowa(n); 
                    for (int i = 0; i < n; i++) {
                        struktury[p]->insert(klucze[i], wartosci[i]);
                    }
                }
                return struktury;
            };

            auto prepAVL = [&]() {
                vector<AVLTable*> struktury(powtorzenia);
                for (int p = 0; p < powtorzenia; p++) {
                    struktury[p] = new AVLTable(n); 
                    for (int i = 0; i < n; i++) {
                        struktury[p]->insert(klucze[i], wartosci[i]);
                    }
                }
                return struktury;
            };

            auto prepCUK = [&]() {
                vector<CuckooHash*> struktury(powtorzenia);
                for (int p = 0; p < powtorzenia; p++) {
                    struktury[p] = new CuckooHash(n * 2); 
                    for (int i = 0; i < n; i++) {
                        struktury[p]->insert(klucze[i]);
                    }
                }
                return struktury;
            };




            int nowyKlucz = zakresKluczy(gen);
            int nowaWartosc = zakresWartosci(gen);
            
            uniform_int_distribution<> indeksKlucza(0, n - 1);
            int istniejacyKlucz = klucze[indeksKlucza(gen)];




            auto kopieML = prepML();
            auto ts = high_resolution_clock::now();
            for (int p = 0; p < powtorzenia; p++) {
                kopieML[p]->insert(nowyKlucz, nowaWartosc);
            }
            auto tz = high_resolution_clock::now();
            mlIns += duration_cast<nanoseconds>(tz - ts).count() / (powtorzenia);
            for (auto c : kopieML) delete c;

            kopieML = prepML();
            ts = high_resolution_clock::now();
            for (int p = 0; p < powtorzenia; p++) {
                kopieML[p]->remove(istniejacyKlucz);
            }
            tz = high_resolution_clock::now();
            mlRem += duration_cast<nanoseconds>(tz - ts).count() / (powtorzenia);
            for (auto c : kopieML) delete c;




            auto kopieAVL = prepAVL();
            ts = high_resolution_clock::now();
            for (int p = 0; p < powtorzenia; p++) {
                kopieAVL[p]->insert(nowyKlucz, nowaWartosc);
            }
            tz = high_resolution_clock::now();
            avlIns += duration_cast<nanoseconds>(tz - ts).count() / (powtorzenia);
            for (auto c : kopieAVL) delete c;

            kopieAVL = prepAVL();
            ts = high_resolution_clock::now();
            for (int p = 0; p < powtorzenia; p++) {
                kopieAVL[p]->remove(istniejacyKlucz);
            }
            tz = high_resolution_clock::now();
            avlRem += duration_cast<nanoseconds>(tz - ts).count() / (powtorzenia);
            for (auto c : kopieAVL) delete c;




            auto kopieCUK = prepCUK();
            ts = high_resolution_clock::now();
            for (int p = 0; p < powtorzenia; p++) {
                kopieCUK[p]->insert(nowyKlucz);
            }
            tz = high_resolution_clock::now();
            cukIns += duration_cast<nanoseconds>(tz - ts).count() / (powtorzenia);
            for (auto c : kopieCUK) delete c;

            kopieCUK = prepCUK();
            ts = high_resolution_clock::now();
            for (int p = 0; p < powtorzenia; p++) {
                kopieCUK[p]->remove(istniejacyKlucz);
            }
            tz = high_resolution_clock::now();
            cukRem += duration_cast<nanoseconds>(tz - ts).count() / (powtorzenia);
            for (auto c : kopieCUK) delete c;
        }

        cout << "DLA N = " << n << ":\n\n";
        
        cout << "Insert:\n";
        cout << "Metoda Lancuchowa: " << mlIns / seedy << " ns\n";
        cout << "AVL Table: " << avlIns / seedy << " ns\n";
        cout << "Cuckoo Hash: " << cukIns / seedy << " ns\n\n";

        cout << "Remove:\n";
        cout << "Metoda Lancuchowa: " << mlRem / seedy << " ns\n";
        cout << "AVL Table: " << avlRem / seedy << " ns\n";
        cout << "Cuckoo Hash: " << cukRem / seedy << " ns\n";
        cout << "\n\n\n";
    }

    return 0;
}