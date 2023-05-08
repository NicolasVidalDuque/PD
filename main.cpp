#include "Encabezados.h"
#include <chrono>

using namespace std;

int main() {
    
    instance data;
    generate_all(data);
    reading(data);
    solution solFin;
    vector<KPIs> historico;
    string path = "datos\\";
    solution sol_per;

    //Solucion inicial
    solution solIni = makeSolIni(data);
    decode(solIni, data);
    print_it(__FUNCTION__, solIni, 0);
    
    //Busqueda local
    solFin = busqueda(solIni, data,historico);

    int cont = 0;
    while (cont < 4){

        //Perturbacion
        sol_per = main_perturbacion(solFin, data);
        cout << 1 << endl;
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
    

    cout << "fin...\n";
    return 1;
}