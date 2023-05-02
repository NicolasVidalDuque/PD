#include "Encabezados.h"


using namespace std;

int main() {
    instance data;
    generate_all(data);
    reading(data);
    solution solFin;
    vector<KPIs> historico;
    string path = "datos\\";
    solution sol_per;
    int cont = 1;


    //Solucion inicial
    solution solIni = makeSolIni(data);
    decode(solIni, data);
    cout << "Inicial " << endl;
    print_it(__FUNCTION__, solIni, 1);
    
    //Busqueda local
    solFin = busqueda(solIni, data,historico);
    decode(solFin, data);

    
    while (cont < 4){

        //Perturbacion
        sol_per = main_perturbacion(solFin, data);
        decode(sol_per, data);

        //Busqueda local post perturbacion
        sol_per = busqueda(sol_per, data, historico);
        decode(sol_per, data);

        if (sol_per.KPI.z>solFin.KPI.z){
            solFin = sol_per;
            cout << "" << endl;
            cout << "Nueva mejor " << endl;
            print_it(__FUNCTION__, solFin, cont);
        }else{
            cont++;
        }

    }
    /*
    if (Sol.KPI.z <= Triple.KPI.z){
        mejora = false;
    }else {
        cout << "Main:Mejoro " << "z: " << Sol.KPI.z << " - pref: " << Sol.KPI.sum_preferencias << " - duros: " << Sol.KPI.cruceduro << " - suave: " << Sol.KPI.crucesuave << endl;
        Triple = Sol;
    }
    */




        //print_solution(solFin, path + "SolucionTrip1.txt");
        //print_historico(mejor_historico, path + "HistoricoFinal.txt");
    // print_tipo(v_tipo, path + "TipoFinal.txt");
    

    cout << "fin...\n";
    return 1;
}