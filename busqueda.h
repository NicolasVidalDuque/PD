#pragma once
#include "structures.h"
#include <algorithm>
#include <iostream>
#include "print.h"
#include "init.h"

solution poblar_vecindario_introducir_priori(solution& actual, instance& data) {
	solution nueva;
	solution mejor_vecina;
	int a;

	for (int b = 0; b < actual.KPI.id_cruces.size(); b++) {
		a = actual.KPI.id_cruces[b];
		for (auto itr = data.mConfilctLTS[a + 1].begin(); itr != data.mConfilctLTS[a + 1].end(); itr++) {

			nueva = actual;
			nueva.vL[a].TS = *itr;
			decode(nueva, data);
			if (mejor_vecina.KPI.z < nueva.KPI.z)//Evitar que se mueva al mejor_mejor (criterio Tab�)
			{
				mejor_vecina = nueva;
			}

		}

	}
	return mejor_vecina;
}

solution poblar_vecindario_intercambio_priori(solution& actual, instance& data) {
	solution nueva;
	solution mejor_vecina;
	int a;


	for (int b = 0; b < actual.KPI.id_cruces.size(); b++) {
		a = actual.KPI.id_cruces[b];
		for (auto itr = data.mCompatiblesL[a + 1].begin(); itr != data.mCompatiblesL[a + 1].end(); itr++) {
			if (data.mConfilctLTS[a + 1].count(actual.vL[*itr - 1].TS)) { //si el TS del *itr es compatible con el Lecture a que siga

				nueva = actual;
				nueva.vL[a].TS = actual.vL[*itr - 1].TS;
				nueva.vL[*itr - 1].TS = actual.vL[a].TS;
				decode(nueva, data);
				if (mejor_vecina.KPI.z < nueva.KPI.z) {//Evitar que se mueva al mejor_mejor (criterio Tab�)
					mejor_vecina = nueva;
				}
			}
		}


	}
	return mejor_vecina;
}

solution poblar_vecindario_cambioTS(solution& actual, instance& data) {
	solution nueva;
	solution mejor_vecina;
	set <int> tipos = { 1,2,3,4,5 };

	while (tipos.size()!=0){

		//  Que tipo de TS vamos a intercambiar
		uniform_int_distribution<int> dist(0, tipos.size() - 1);
		int aux = dist(gen);

		set<int>::iterator it3 = tipos.begin();
		advance(it3, aux);

		set < pair<int, int>> copy = data.mTipoTS[*it3];
		

		while (copy.size() != 0) {

			// Que TS vamos a escoger para intercambiar
			uniform_int_distribution<int> dist2(0, copy.size() - 1);
			int aux2 = dist2(gen);

			set<pair<int, int>>::iterator it = copy.begin();
			advance(it, aux2);
			

			for (int i = 0; i < data.mTipoTS[*it3].size(); i++){
				//Seleccionamos el segundo TS
				set<pair<int, int>>::iterator it2 = data.mTipoTS[*it3].begin();
				advance(it2, i);
				for (int a = 0; a < TOTAL_LECTURES - 1; a++) {
					if (actual.vL[a].TS == *it) {

						for (auto itr = data.mCompatiblesL[a + 1].begin(); itr != data.mCompatiblesL[a + 1].end(); itr++) {
							if (actual.vL[*itr - 1].TS == *it2) { //si el TS del *itr es compatible con el Lecture a que siga
								if (a<*itr-1){

									nueva = actual;
									nueva.vL[a].TS = *it2;
									nueva.vL[*itr - 1].TS = *it;
									decode(nueva, data);
									if (mejor_vecina.KPI.z < nueva.KPI.z) {//Evitar que se mueva al mejor_mejor (criterio Tab�)
										mejor_vecina = nueva;
									}
								}
							}
						}
					}
				}
			}
			copy.erase(it);
		}
		tipos.erase(it3);
	}
	return mejor_vecina;
}

solution poblar_vecindario_intercambio(solution& actual, instance& data) {
	solution nueva;
	solution mejor_vecina;
	for (int a = 0; a < TOTAL_LECTURES - 1; a++){
		
		for (auto itr = data.mCompatiblesL[a + 1].begin(); itr != data.mCompatiblesL[a + 1].end(); itr++) {
			if (a<*itr-1){

				if (data.mConfilctLTS[a + 1].count(actual.vL[*itr - 1].TS)) { //si el TS del *itr es compatible con el Lecture a que siga
					nueva = actual;
					nueva.vL[a].TS = actual.vL[*itr - 1].TS;
					nueva.vL[*itr - 1].TS = actual.vL[a].TS;
					decode(nueva, data);
					if (mejor_vecina.KPI.z < nueva.KPI.z) {//Evitar que se mueva al mejor_mejor (criterio Tab�)
						mejor_vecina = nueva;
					}
				}
			}
		}

	}
	return mejor_vecina;
}

solution poblar_vecindario_introducir(solution& actual, instance& data) {
	solution nueva;
	solution mejor_vecina;

	for (int a = 0; a < TOTAL_LECTURES; a++)
	{
		for (auto itr = data.mConfilctLTS[a + 1].begin(); itr != data.mConfilctLTS[a + 1].end(); itr++) {

			nueva = actual;
			nueva.vL[a].TS = *itr;
			decode(nueva, data);
			if (mejor_vecina.KPI.z < nueva.KPI.z)//Evitar que se mueva al mejor_mejor (criterio Tab�)
			{
				mejor_vecina = nueva;
			}

		}

	}
	return mejor_vecina;
}

solution singular(solution& semilla, instance& data, vector<KPIs>& historico, solution (*metodo_poblacion)(solution&, instance&), string &name) {
	solution actual;
	solution mejor_mejor;
	actual = semilla;
	int cont = 0;
	for (int i = 0; i <10000 && cont < 2; i++)
	{
		actual = metodo_poblacion(actual, data);
		historico.push_back(actual.KPI);
		if (actual.KPI.z > mejor_mejor.KPI.z){
			mejor_mejor = actual;
			print_it(name, actual, i);
		}else {
			cout << "No mejoro " << endl;
			print_it(name, actual, i);
			cont++;
		}
	}
	return mejor_mejor;
}

solution dual(solution& semilla, instance& data, vector<KPIs>& historico, solution (*metodo_poblacion_1)(solution&, instance&), solution (*metodo_poblacion_2)(solution&, instance&), string &hibrid) {//exactamente la misma, solo que llama a la otra
	solution actual1;
	solution actual2;
	solution mejor_mejor;
	solution actual;
	actual = semilla;
	int cont = 0;

	for (int i = 0; i <10000 && cont < 2; i++){
		actual1 = metodo_poblacion_1(actual, data);
		actual2 = metodo_poblacion_2(actual, data);
		if (actual1.KPI.z>=actual2.KPI.z){
			actual = actual1;
		} else {
			actual = actual2;
		}
		historico.push_back(actual.KPI);
		if (actual.KPI.z > mejor_mejor.KPI.z){
			mejor_mejor = actual;
			print_it(hibrid,actual,i);
		}else {
			cont++;
			cout << "No mejoro " << endl;
			print_it(hibrid, actual, i);
		}
	}
	return mejor_mejor;
}

bool sorting_solutions(solution &a, solution &b){
	return (a.KPI.z > b.KPI.z);
}

solution triple(solution& semilla, instance& data, vector<KPIs>& historico, solution (*metodo_poblacion_1)(solution&, instance&), solution (*metodo_poblacion_2)(solution&, instance&),solution (*metodo_poblacion_3)(solution&, instance&), string &hibrid) {//exactamente la misma, solo que llama a la otra
	solution actual;
	solution mejor_mejor;
	actual = semilla;
	int cont = 0;

	for (int i = 0; i <10000; i++){
		vector<solution> ranking = {
			metodo_poblacion_1(actual,data),
			metodo_poblacion_2(actual,data),
			metodo_poblacion_3(actual,data)
		};
		
		sort(ranking.begin(), ranking.end(), sorting_solutions);
		actual = ranking[0];

		historico.push_back(actual.KPI);
		if (actual.KPI.z > mejor_mejor.KPI.z){
			mejor_mejor = actual;
			print_it(hibrid,actual,i);
		}else {
			cout << "No mejoro " << endl;
			print_it(hibrid, actual, i);
			break;
		}
	}
	return mejor_mejor;
}


typedef solution (*duales)(solution&, instance&);
void correr_duales(instance& data,vector<KPIs>& historico){
	solution resultado;

	vector<pair<duales, duales>> combinations = {
		// {poblar_vecindario_cambioTS,poblar_vecindario_intercambio},
		// {poblar_vecindario_cambioTS, poblar_vecindario_introducir},
		{poblar_vecindario_intercambio, poblar_vecindario_introducir}
	};

	vector<string> nombres = {
		// "CAMBIO_TS - INTERCAMBIO",
		// "CAMBIO_TS - INTRODUCIR",
		"INTERCAMBIO - INTRODUCIR"
	};

	for(int c = 0; c < combinations.size(); c++){
		string path = "C:\\Users\\pipeh\\OneDrive\\Documentos\\c++\\material\\" + nombres[c] +".txt";
		clear_file(path);
		for(size_t iter = 1; iter <= 10; iter++){
			historico.clear();
			solution origen = makeSolIni(data);
			decode(origen, data);
			cout << "--------------------------------" << iter << "---------------------------------" << endl;
			resultado = dual(
				origen,
				data,
				historico,
				combinations[c].first,
				combinations[c].second,
				nombres[c]
			);
			print_historico(historico, path);
		}
	}

}

solution correr_triple(solution& actual, instance& data, vector<KPIs>& historico){
	solution resultado;
	string path = "C:\\Users\\pipeh\\OneDrive\\Documentos\\c++\\material\\h_tripe.txt";
	string n = "triple";
	clear_file(path);

	historico.clear();

	resultado = triple(
		actual,
		data,
		historico,
		poblar_vecindario_cambioTS,
		poblar_vecindario_intercambio,
		poblar_vecindario_introducir,
		n
	);
	print_historico(historico, path);

	return resultado;
}

solution busqueda(solution& semilla, instance& data,vector<KPIs>& historico) {
	
	cout << "busqueda:actual " << "z: " << semilla.KPI.z << " - pref: "<< semilla.KPI.sum_preferencias << " - duros: " << semilla.KPI.cruceduro << " - suave: " << semilla.KPI.crucesuave << endl;
	return correr_triple(semilla, data, historico);
}