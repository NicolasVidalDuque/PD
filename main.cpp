#include "Encabezados.h"


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
    string path = "datos\\";
    solution Sol;
    solution sol_per;
    int cont = 1;

    bool mejora = true;

        //Solucion inicial
        cout << "Inicial" << endl;
        solution solIni = makeSolIni(data);
        decode(solIni, data);
        cout << "Inicial " << endl;
        cout << "z: " << solIni.KPI.z << " - pref: " << solIni.KPI.sum_preferencias << " - duros: " << solIni.KPI.cruceduro << " - suave: " << solIni.KPI.crucesuave << endl;

        
        //Busqueda local
        solFin = busqueda(solIni, data,historico);
        decode(solFin, data);

       
        while (mejora){

            cout << "" << endl;
            cout << "Perturbacion " << cont << endl;
            cout << "" << endl;

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
                cout <<"z: " << solFin.KPI.z << " - pref: " << solFin.KPI.sum_preferencias << " - duros: " << solFin.KPI.cruceduro << " - suave: " << solFin.KPI.crucesuave << endl;
            }else{
                cont++;
                if (cont>3){
                    mejora = false;
                }
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