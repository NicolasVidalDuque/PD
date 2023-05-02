#pragma once
#include <vector>
#include "structures.h"
#include "fstream"

void print_it(string origen, solution& actual, int i) {
	printf("%10s %3d |  z:  %-6.0f    p:  %-4.0f    d:  %-3.0f    s:  %-3.0d \n",
		origen.c_str(),
		i,
		actual.KPI.z,
		actual.KPI.sum_preferencias,
		actual.KPI.cruceduro,
		actual.KPI.crucesuave
	);
}

void print_solution(solution s, string path) {
    ofstream output_file(path);
    for (auto& l : s.vL) {
        output_file << l.id << "-" << l.TS.first << "-" << l.TS.second << "\n";
    }
    output_file.close();
}
void print_faltantes(vector<int> vF, string path) {
    ofstream output_file(path);
    for (size_t i = 0; i < 100; i++) {
        output_file << i << "-" << vF[i] << "\n";
    }
    output_file.close();
}
void clear_file(string path){
    ofstream output_file;
    output_file.open(path, std::ofstream::out | std::ofstream::trunc);
    output_file.close();
}
void print_historico(vector<KPIs> vF, string path) {
    ofstream output_file(path,ios::app);
    if(output_file.is_open()){
        for (size_t i = 0; i < vF.size(); i++) {
            //             iter           z                     preferencias                    duro                        suave
            output_file << i << " " << vF[i].z << " " <<vF[i].sum_preferencias << " " << vF[i].cruceduro << " "<< vF[i].crucesuave<< "\n";
        }
        output_file.close();
    }
}
void print_tipo(vector<int> vF, string path) {
    ofstream output_file(path);
    for (size_t i = 0; i < vF.size(); i++) {
        output_file << i+1 << " "<< vF[i] << "\n";
    }
    output_file.close();
}