#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <chrono>

# define TOTAL_LECTURES 100
# define TOTAL_TIMESLOTS 132

using namespace std;

struct instance {
    map<int, set<int>> mConfilctK2LL;
    map<int, set<int>> mConfilctLL;
    map<int, set<int>> mCompatiblesL;
    map<int, set<pair<int, int>>> mConfilctLTS;
    map<int, set<pair<int, int>>> mTipoTS;
    map<pair<int, int>, set<pair<int, int>>> mCategoriaLTS;
    map<pair<int, int>, set<pair<int, int>>> mConfilctTSTS;
    set<int> Fijas;
    set<pair<int, int>> sAllTS; // Pendiente eliminacion
    set<int> sAllL;
    vector<vector<int>> mPreferences;
    map<pair<int, int>, int> mapTS_ID;

    instance() {
        this->generateMapTS_ID();
    }

    void generateMapTS_ID() {
        int sum = 1;
        for (int f = 1; f <= 12; f++) {
            for (int ff = 1; ff <= 11; ff++) {
                this->mapTS_ID.insert({ make_pair(f, ff),sum++ });
            }
        }
    }
};

struct lecture {
    int id;
    pair<int, int> TS; // pair<tipoDia, tipoBloque>
    lecture() : id(-1) {}
    lecture(int a) : id(a) {}
};
struct KPIs {
    vector <int> id_cruces;
    double z;
    double preferencias; //Preferencias
    double sum_preferencias;
    int crucesuave; //K2 - Cruces Suaves
    double cruceduro;
    KPIs() : z(-100000), crucesuave(0), preferencias(-1), cruceduro(0), sum_preferencias(-1){}
};
struct solution {
    KPIs KPI;
    vector<lecture> vL;

};

class Time{
    private:
        chrono::time_point<std::chrono::high_resolution_clock> start;
        chrono::time_point<std::chrono::high_resolution_clock> end;
        chrono::steady_clock::duration elapsed;
        chrono::milliseconds miliSecs;

    public:
        Time(){
        }

        void init(){
            this->start = chrono::high_resolution_clock::now();
        }

        int stop(){
            this->end = chrono::high_resolution_clock::now();
            this->elapsed = this->end - this->start;
            this->miliSecs = chrono::duration_cast<std::chrono::milliseconds>(elapsed);
            return miliSecs.count();
        }

        void printMili(){
            cout << "Print milliseconds: " << this->miliSecs.count() << endl;
        }

        void printTics(){
            cout << "Print tics: "<< this->elapsed.count() << endl;
        }
};
