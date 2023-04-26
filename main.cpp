#include "init.h"
#include "reading.h"
#include "structures.h"
#include "busqueda.h"
#include "print.h"
#include "Perturbacion.h"

using namespace std;

int main() {
    instance data;
    generate_all(data);
    reading(data);
    solution solFin;
    solution mejor_iter;
    mejor_iter.KPI.z = -1000000;
    vector<KPIs> historico;
    vector<KPIs> mejor_historico;
    vector<int> v_tipo (3,0);
    string path = "resultados\\resultado_triple.txt";
    solution Sol;
    solution Triple;
    int a = 0;

    bool mejora = true;

    // //Solucion inicial
    // solution solIni = makeSolIni(data);
    // decode(solIni, data);

    // //Busqueda
    // solIni = busqueda(solIni, data,historico);
    // print_solution(solIni, path);
        
    Triple.vL = loadSolution(path);
    decode(Triple, data);
    cout << "Triple " << "z: " << Triple.KPI.z << " - pref: " << Triple.KPI.sum_preferencias << " - duros: " << Triple.KPI.cruceduro << " - suave: " << Triple.KPI.crucesuave << endl;

    while (a++ < 5)
    {
        
        //Perturbacion
        
        Sol = main_perturbacion(Triple, data);

        // if (Sol.KPI.z <= Triple.KPI.z){
        //     mejora = false;
        // }else {
        //     cout << "Main:Mejoro " << "z: " << Sol.KPI.z << " - pref: " << Sol.KPI.sum_preferencias << " - duros: " << Sol.KPI.cruceduro << " - suave: " << Sol.KPI.crucesuave << endl;
        //     Triple = Sol;
        // }
        


    }

    //     // print_solution(solFin, path + "SolucionFinal.txt");
    //     // print_historico(mejor_historico, path + "HistoricoFinal.txt");
    //     // print_tipo(v_tipo, path + "TipoFinal.txt");
    

    cout << "fin...\n";
    return 1;
}