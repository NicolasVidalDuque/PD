#pragma once
#include "Encabezados.h"


solution Perturbacion(solution& actual, instance& data, int i) {//1L aleatorio
    solution nueva;
    int c = 0;
    for (int a = 0; a < i; a++){

        uniform_int_distribution<int> dist1(0, TOTAL_LECTURES - 1);
        int aux1 = dist1(gen);

        uniform_int_distribution<int> dist(0, data.mConfilctLTS[aux1 + 1].size() - 1);
        int aux2 = dist(gen);

        set<pair<int, int>>::iterator it = data.mConfilctLTS[aux1 + 1].begin();
        advance(it, aux2);

        nueva = actual;
        nueva.vL[aux1].TS = *it;
        c++;
    }
    cout << c << endl;
    decode(nueva, data);
    return nueva;
}

solution Perturbacion2(solution& actual, instance& data, int i) {// Intercambiar 2 L aleatorios
    solution nueva;
    int c = 0;
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
        c++;
    }
    cout << c << endl;
    decode(nueva, data);
    return nueva;
}

solution main_perturbacion(solution& actual, instance& data) {

    solution copia;
    vector<KPIs> historico;
    copia = actual;
    solution mejor;
    mejor.KPI.z = -100000;

    
        copia = Perturbacion2(copia, data,6);
        copia = Perturbacion(copia, data, 6);

        
 
    return copia;
}