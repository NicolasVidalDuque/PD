#pragma once
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include "reading.h"
#include "structures.h"

# define TOTAL_LECTURES 100
# define TOTAL_TIMESLOTS 132

using namespace std;

random_device rd;
mt19937 gen(rd());

int verificationCrucesSuaves(int id, set<int>& s, instance& data) {
    int cruces = 0;
    for (auto i : s) {
        if (data.mConfilctK2LL[id].count(i)) {
            cruces++;
        }
    }
    return cruces;
}

void crucesSuaves(solution& s, instance& data) {

    bool hay_cruce_TS;
    int crucesuave = 0;
    for (int a = 0; a < TOTAL_LECTURES; a++)
    {
        for (auto itr = data.mConfilctK2LL[a+1].begin(); itr != data.mConfilctK2LL[a+1].end(); itr++) { //
           if (a+1<*itr)
           {
                hay_cruce_TS = data.mConfilctTSTS[s.vL[a].TS].count(s.vL[*itr - 1].TS); // 1: hay conflicto, 0: No conflict
                if (hay_cruce_TS == true) {
                    crucesuave++;
                           
                }
           }
        }
    }
    s.KPI.crucesuave = crucesuave;
}
bool buscar_en_vector(std::vector<int> vector, int b) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == b) {
            return true;
        }
    }
    return false;
}
void crucesDuros(solution& s, instance& data) {

    bool hay_cruce_TS;
    int cruceduro = 0;
    vector <int> cduros;
    bool ya_esta;
    for (int a = 0; a < TOTAL_LECTURES; a++)
    {
        for (auto itr = data.mConfilctLL[a + 1].begin(); itr != data.mConfilctLL[a + 1].end(); itr++) { //
            if (a + 1 < *itr)
            {
                hay_cruce_TS = data.mConfilctTSTS[s.vL[a].TS].count(s.vL[*itr - 1].TS); // 1: hay conflicto, 0: No conflict
                if (hay_cruce_TS == true) {
                    cruceduro++;

                    ya_esta = buscar_en_vector(cduros,a+1);
                    if (ya_esta==false){
                        cduros.push_back(a + 1);
                    }

                    ya_esta = buscar_en_vector(cduros, *itr);

                    if (ya_esta == false) {
                        cduros.push_back(*itr);
                    }
                }
            }
        }
    }
    s.KPI.cruceduro = cruceduro;
    s.KPI.id_cruces = cduros;
}

void decode(solution& s, instance& data) {
    int sum = 0, faltantes = 0;
    pair<int, int> nullPair = make_pair(0, 0);
    lecture l;
    for (int j = 0; j < s.vL.size(); j++) {
        l = s.vL[j];
        int i = l.id;
        sum += data.mPreferences[l.id - 1][data.mapTS_ID[l.TS]];
    }

    s.KPI.sum_preferencias = sum;
    s.KPI.preferencias = double(sum) / double(TOTAL_LECTURES);
    crucesSuaves(s, data);
    crucesDuros(s, data);
    s.KPI.z = (s.KPI.sum_preferencias - s.KPI.crucesuave - 1000 * s.KPI.cruceduro);
}


pair<int, int> generateRandomTS(set<pair<int, int>>& copy) {
    uniform_int_distribution<int> dist(0, copy.size() - 1);
    int aux = dist(gen);

    set<pair<int, int>>::iterator it = copy.begin();
    advance(it, aux);
    pair<int, int> copy2 = *it;
    copy.erase(it);
    return copy2;
}

void generate_all(instance& data) {
    for (int i = 0; i < TOTAL_LECTURES; i++) {
        data.sAllL.insert(i + 1);
    }
}

void divide(map<int, set<int>>& sDiv, instance data, vector<int>& sequence) {
    set<int> s;
    for (int i = 1; i <= data.mConfilctLTS.size(); i++) {
        if (!sDiv.count(data.mConfilctLTS[i].size())) { // No hay un key == size
            sDiv.insert({ data.mConfilctLTS[i].size(),s });
            sequence.push_back(data.mConfilctLTS[i].size());
        }
        sDiv[data.mConfilctLTS[i].size()].insert(i);
    }
    sort(sequence.begin(), sequence.end());
}

solution makeSolIni(instance data) {
    solution s;
    pair<int, int> pRandomTS;
    vector<lecture> vLSol(TOTAL_LECTURES, lecture());
    vector<int> FaltantesK2(TOTAL_LECTURES);


    map<int, set<int>> sDiv;
    set<int> sL;
    vector<int> sequence;

    divide(sDiv, data, sequence);

    for (int key = 0; key < sequence.size(); key++) { //
        sL = sDiv[sequence[key]];
        while (sL.size() != 0) {
            //  Random
            uniform_int_distribution<int> dist(0, sL.size() - 1);
            int aux = dist(gen);

            // Iterator
            set<int>::iterator it = sL.begin();
            advance(it, aux);

            // Crear lecture para pushback
            int auxId = *it;

            set < pair<int, int>> copy = data.mConfilctLTS[auxId];
            bool is_inTSTS = true;
            while (is_inTSTS) { // Mientras clonflict en TS
                //size copy si est{a vac{io 
                if (copy.size() == 0) {

                    pRandomTS = generateRandomTS(data.mConfilctLTS[auxId]);

                    //Aqui se rinde
                    break;
                }
                pRandomTS = generateRandomTS(copy);
                for (auto itr = data.mConfilctLL[auxId].begin(); itr != data.mConfilctLL[auxId].end(); itr++) {
                    is_inTSTS = data.mConfilctTSTS[pRandomTS].count(vLSol[*itr - 1].TS); // 1: hay conflicto, 0: No conflict
                    if (is_inTSTS == true) break;
                }
            }

            vLSol[auxId - 1].TS = pRandomTS;
            vLSol[auxId - 1].id = auxId;
            sL.erase(it);
        }
    }
    s.vL = vLSol;
   
    return s;
}
