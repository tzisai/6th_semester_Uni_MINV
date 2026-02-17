#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <fstream> 

using namespace std;

/*
Martin Isai Nunez Villeda
Ingenieria en Computacion Inteligente
Random Sorting (Swapping version)
*/


vector<int> fill(vector<int>& array, int n) {
    random_device randn;
    mt19937 gen(randn());   
    uniform_int_distribution<> distrib(1, 100);
    for (int i = 0; i < n; i++) {
        array.push_back(distrib(gen));
    }
    return array;
}

int indice_random(int n, int j) {
    if (n <= 1) return 0; 
    random_device randn;
    mt19937 gen(randn());
    uniform_int_distribution<> distrib(0, n - 1);
    int rnd;
    do {
        rnd = distrib(gen);
    } while (rnd == j);
    return rnd;
}

void imprimir_arr(const vector<int>& printer) {
    for (int val : printer) cout << val << " ";
    cout << endl;
}


void sortote(vector<int>& arr, bool silencioso) {
    int aux1, rnd;
    for (int i = 0; i < arr.size(); i++) {
        rnd = indice_random(arr.size(), i);
        aux1 = arr[i];
        arr[i] = arr[rnd];
        arr[rnd] = aux1;
        
        if (!silencioso) {
            cout << "intercambio " << i << ": ";
            imprimir_arr(arr);
        }
    }
}


double obtener_tiempo(function<void()> func) {
    auto inicio = chrono::high_resolution_clock::now();
    func(); 
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo = fin - inicio;
    return tiempo.count(); 
}

void ejecutar_prueba(int l, bool silencioso) {
    vector<int> arr;
    fill(arr, l);
    sortote(arr, silencioso);
}

void guardar_csv(const vector<int>& ns, const vector<double>& tiempos) {
    ofstream archivo("tiempos_swapping.csv");
    if (archivo.is_open()) {
        archivo << "n,tiempo_ms\n";
        for (size_t i = 0; i < ns.size(); i++) {
            archivo << ns[i] << "," << tiempos[i] << "\n";
        }
        archivo.close();
        cout << "\n[OK] Datos guardados en 'tiempos_swapping.csv'" << endl;
    } else {
        cerr << "[Error] No se pudo crear el archivo CSV" << endl;
    }
}


int main() {
    char opcion;
    cout << "MENU DE COMPLEJIDAD\n";
    cout << "I - Prueba Individual (con impresiones)\n";
    cout << "G - Generar N iteraciones para CSV\n";
    cout << "Seleccion: ";
    cin >> opcion;

    if (opcion == 'I' || opcion == 'i') {
        int l;
        cout << "Tamaño del vector: "; cin >> l;
        double t = obtener_tiempo([&]() { ejecutar_prueba(l, false); });
        cout << "\nTiempo total: " << t << " ms" << endl;

    } else if (opcion == 'G' || opcion == 'g') {
        int iteraciones;
        cout << "Cuantos puntos de datos para la grafica?: "; cin >> iteraciones;
        
        vector<int> ns;
        vector<double> tiempos;

        for (int i = 1; i <= iteraciones; i++) {
            int n_actual = i * 100; 
            double t = obtener_tiempo([&]() { ejecutar_prueba(n_actual, true); });
            
            ns.push_back(n_actual);
            tiempos.push_back(t);
            cout << "Procesando n=" << n_actual << " (" << i << "/" << iteraciones << ")" << endl;
        }
        guardar_csv(ns, tiempos);
    }

    return 0;
}