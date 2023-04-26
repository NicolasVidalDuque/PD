#pragma once
#include "Encabezados.h"
#include <random>

using namespace std;

solution Perturbacion(solution& actual, instance& data, int i) {//1L aleatorio
    solution nueva;
    for (int a = 0; a < i; a++){

        uniform_int_distribution<int> dist1(0, TOTAL_LECTURES - 1);
        int aux1 = dist1(gen);

        uniform_int_distribution<int> dist(0, data.mConfilctLTS[aux1 + 1].size() - 1);
        int aux2 = dist(gen);

        set<pair<int, int>>::iterator it = data.mConfilctLTS[aux1 + 1].begin();
        advance(it, aux2);

        nueva = actual;
        nueva.vL[aux1].TS = *it;
    }
    decode(nueva, data);
    return nueva;
}

solution Perturbacion2(solution& actual, instance& data, int i) {// Intercambiar 2 L aleatorios
    solution nueva;
    for (int a = 0; a < i; a++) {
        //Primer Lecture
        uniform_int_distribution<int> dist1(0, TOTAL_LECTURES - 1);
        int aux1 = dist1(gen);//sale posicion

        //Segundo Lecture
        uniform_int_distribution<int> dist(0, data.mCompatiblesL[aux1 + 1].size() - 1);
        int aux2 = dist(gen);

        set<int>::iterator it = data.mCompatiblesL[aux1 + 1].begin();
        advance(it, aux2);//sale un id

        nueva = actual;
        nueva.vL[aux1].TS = actual.vL[*it - 1].TS;
        nueva.vL[*it - 1].TS = actual.vL[aux1].TS;
    }
    decode(nueva, data);
    return nueva;
}

void main_perturbacion(solution& actual, instance& data, string &archivo, int prueba) {
    solution copia = actual;
    vector<KPIs> historico;
    solution mejor;

    for (int i = 1; i < 11; i++)
    {
        copia = Perturbacion2(copia, data,i);
        copia = Perturbacion(copia, data, i);

        triple(
            copia,
            data,
            historico,
            poblar_vecindario_cambioTS,
            poblar_vecindario_intercambio,
            poblar_vecindario_introducir,
            archivo, prueba, i
        );
    }

}