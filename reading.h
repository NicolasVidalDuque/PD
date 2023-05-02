#pragma once
#include <string>
#include <sstream>
#include "structures.h"

using namespace std;


void read_Lecture_Lecture(map<int, set<int>>& data, string path) {
    ifstream input_file(path);
    string line;

    while (getline(input_file, line)) {
        stringstream line_stream(line);
        int key, value;
        set<int> row;
        line_stream >> key;
        while (line_stream >> value) {
            row.insert(value);
        }
        data[key] = row;
    }
    input_file.close();
}
void read_Lecture_TimeSlot(map<int, set<pair<int, int>>>& data, string path) {
    ifstream infile(path);
    string line;
    int key;
    string pair_str;
    int first, second;
    char separator;

    while (getline(infile, line)) {
        stringstream ss(line);
        ss >> key;
        while (ss >> first >> separator >> second) {
            data[key].insert(make_pair(first, second));
        }
    }
    infile.close();
}
void read_Fijas(set<int> &Fijas, string path) {
    ifstream infile(path);
    string line;
    int id;

    while (getline(infile, line)) {
        stringstream ss(line);
        ss >> id;
        Fijas.insert(id);
    }
    infile.close();
}
void read_TimeSlot_TimeSlot(map<pair<int, int>, set<pair<int, int>>>& data, string path) {
    ifstream infile(path);
    string line;
    string pair_str;
    int ffirst, ssecond, first, second;
    char sseparator, separator;

    while (getline(infile, line)) {
        stringstream ss(line);
        ss >> ffirst >> sseparator >> ssecond;
        while (ss >> first >> separator >> second) {
            data[make_pair(ffirst, ssecond)].insert(make_pair(first, second));
        }
    }
    infile.close();
}
void read_CategoriaTS(map<pair<int, int>, set<pair<int, int>>>& data, string path) {
    ifstream infile(path);
    string line;
    string pair_str;
    int ffirst, ssecond, first, second;
    char sseparator, separator;

    while (getline(infile, line)) {
        stringstream ss(line);
        ss >> ffirst >> sseparator >> ssecond;
        while (ss >> first >> separator >> second) {
            data[make_pair(ffirst, ssecond)].insert(make_pair(first, second));
        }
    }
    infile.close();
}
void read_Preferences(vector<vector<int>>& p, string path) {
    ifstream infile(path);
    string line;
    int n;
    vector<int> v;
    while (getline(infile, line)) {
        stringstream ss(line);
        while (ss >> n) {
            v.push_back(n);
        }
        p.push_back(v);
        v.clear();
    }

    infile.close();
}
void reading(instance& data) {
    string path = "datos\\";

    string pathFijas = path + "Fijas.txt";
    string pathConflictK2LL = path + "K2_LECTUREvsLECTURE.txt";
    string pathConflictLL = path + "LECTUREvsLECTURE.txt";
    string pathCompatiblesL = path + "mCompatiblesL.txt";
    string pathConflictLTS = path + "LECTUREvsTS.txt";
    string pathConflictTSTS = path + "TSvsTS.txt";
    string pathPreferences = path + "MATRIZ_PREFERENCIAS.txt";
    string pathCategoriaTS = path + "MCategoriaTS.txt";
    string pathMTipoTS = path + "MTipoTS.txt";

    read_Fijas(data.Fijas,pathFijas);
    read_Lecture_Lecture(data.mConfilctK2LL, pathConflictK2LL);
    read_Lecture_Lecture(data.mConfilctLL, pathConflictLL);
    read_Lecture_Lecture(data.mCompatiblesL, pathCompatiblesL);
    read_Lecture_TimeSlot(data.mConfilctLTS, pathConflictLTS);
    read_Lecture_TimeSlot(data.mTipoTS, pathMTipoTS);
    read_TimeSlot_TimeSlot(data.mConfilctTSTS, pathConflictTSTS);
    read_Preferences(data.mPreferences, pathPreferences);
    read_CategoriaTS(data.mCategoriaLTS, pathCategoriaTS);
}
vector<lecture> loadSolution(string path) {
    vector<lecture> sol;
    ifstream input_file(path);
    string line;
    int id, ts1, ts2;
    char s1, s2;

    while (getline(input_file, line)) {
        stringstream ss(line);
        ss >> id >> s1 >> ts1 >> s2 >> ts2;
        lecture l(id);
        l.TS = make_pair(ts1, ts2);
        sol.push_back(l);
    }
    input_file.close();
    return sol;
}
