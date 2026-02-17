#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <fstream> 

using namespace std;


void fill_vector(vector<int>& array, int n) {
    random_device randn;
    mt19937 gen(randn());   
    uniform_int_distribution<> distrib(1, 100);
    for (int i = 0; i < n; i++) array.push_back(distrib(gen));
}

void buscar_coincidencias(int n, bool silencioso) {
    vector<int> vect1;
    vector<int> vect2;

    fill_vector(vect1, n);
    fill_vector(vect2, n);

    int coincidencias = 0;

    for(int i = 0; i < vect1.size(); i++) {
        for(int k = 0; k < vect2.size(); k++) {
            if(vect1[i] == vect2[k]) {
                coincidencias++;
            }
        }
    }

    if (!silencioso) {
        cout << "Se encontraron " << coincidencias << " coincidencias." << endl;
    }
}

double obtener_tiempo(function<void()> func) {
    auto inicio = chrono::high_resolution_clock::now();
    func(); 
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo = fin - inicio;
    return tiempo.count(); 
}


void guardar_csv(const vector<int>& ns, const vector<double>& tiempos) {
    ofstream archivo("coincidencias_n2.csv");
    if (archivo.is_open()) {
        archivo << "n,tiempo_ms\n";
        for (size_t i = 0; i < ns.size(); i++) {
            archivo << ns[i] << "," << tiempos[i] << "\n";
        }
        archivo.close();
        cout << "\n[OK] Datos guardados en 'coincidencias_n2.csv'" << endl;
    }
}

int main() {
    char opcion;
    cout << "--- ANALISIS DE COINCIDENCIAS ---\n";
    cout << "I - Prueba Individual\n";
    cout << "G - Generar CSV para Grafica\n";
    cout << "Seleccion: ";
    cin >> opcion;

    if (opcion == 'I' || opcion == 'i') {
        int n;
        cout << "Longitud del vector: "; cin >> n;
      

        double t = obtener_tiempo([&]() { buscar_coincidencias(n, false); });
        
        cout << "Tiempo de ejecucion: " << t << " ms" << endl;

    } else if (opcion == 'G' || opcion == 'g') {
        int iteraciones;
        cout << "Cuantos puntos de datos?: "; cin >> iteraciones;
        
        vector<int> ns;
        vector<double> tiempos;

        for (int i = 1; i <= iteraciones; i++) {
            int n_actual = i * 100; 
            
            
            double t = obtener_tiempo([&]() { buscar_coincidencias(n_actual, true); });
            
            ns.push_back(n_actual);
            tiempos.push_back(t);
            cout << "n=" << n_actual << " completado." << endl;
        }
        guardar_csv(ns, tiempos);
    }

    return 0;
}