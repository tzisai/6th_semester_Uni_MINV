#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <fstream> 

using namespace std;


vector<int> fill(vector<int>& array, int n) {
    random_device randn;
    mt19937 gen(randn());   
    uniform_int_distribution<> distrib(1, 100);
    for (int i = 0; i < n; i++) array.push_back(distrib(gen));
    return array;
}

vector<int> fill_indices(vector<int> ind, int n) {
    for (int k = 0; k < n; k++) ind.push_back(k);
    return ind;
}

int indice_random(int n) {
    random_device randn;
    mt19937 gen(randn());   
    uniform_int_distribution<> distrib(0, n - 1);
    return distrib(gen);
}

void imprimir_arr(vector<int> printer) {
    for (int val : printer) cout << val << " ";
    cout << endl;
}

void rand_sorting(vector<int> arr1, vector<int> ind, int l, bool silencioso) {
    vector<int> sort_arr(l);
    if (!silencioso) {
        cout << "Vector inicial" << endl;
        imprimir_arr(arr1);
        cout << "Vector indices" << endl;
        imprimir_arr(ind);
    }

    for (int j = 0; j < l; j++) {
        int rand_ind = indice_random(ind.size());
        int aux = ind[rand_ind];
        ind.erase(ind.begin() + rand_ind); // Operación O(n)
        sort_arr[aux] = arr1[j];

        if (!silencioso) {
            cout << "Iteracion " << j + 1 << endl;
            imprimir_arr(sort_arr);
        }
    }
}


double obtener_tiempo(std::function<void()> func) {
    auto inicio = std::chrono::high_resolution_clock::now();
    func(); 
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tiempo = fin - inicio;
    return tiempo.count(); 
}

void ejecutar_prueba(int l, bool silencioso = false) {
    vector<int> array_uno;
    vector<int> array_indices;
    array_uno = fill(array_uno, l);    
    array_indices = fill_indices(array_indices, l);

    rand_sorting(array_uno, array_indices, l, silencioso);
}


void generar_csv(const vector<int>& ns, const vector<double>& tiempos) {
    ofstream archivo("datos_complejidad.csv"); // Crea el archivo en la carpeta actual

    if (archivo.is_open()) {
        archivo << "n,tiempo_ms\n"; // Encabezado
        for (size_t i = 0; i < ns.size(); i++) {
            archivo << ns[i] << "," << tiempos[i] << "\n";
        }
        archivo.close();
        cout << "\n[EXITO] Archivo 'datos_complejidad.csv' generado." << endl;
    } else {
        cerr << "\n[ERROR] No se pudo crear el archivo CSV." << endl;
    }
}

int main() {
    int n = 0;
    char input;
    vector<double> tiempos;
    vector<int> tamanos_n; 

    cout << "- Prueba individual (I)\n- Generar datos para grafica CSV (G)\nEleccion: ";
    cin >> input;

    if (input == 'I' || input == 'i') {
        int l;
        cout << "Ingresa el length del vector: ";
        cin >> l;
        double t = obtener_tiempo([&]() { ejecutar_prueba(l, false); });
        cout << "\n>>> Tiempo total: " << t << " ms" << endl;

    } else if (input == 'G' || input == 'g') {
        cout << "Cuantos puntos de datos quieres para la grafica? ";
        cin >> n;

        for (int i = 1; i <= n; i++) {
            int tamano_actual = i * 200; 
            double t = obtener_tiempo([&]() { ejecutar_prueba(tamano_actual, true); });
            
            tiempos.push_back(t);
            tamanos_n.push_back(tamano_actual);
            
            cout << "Progreso: " << i << "/" << n << " (n=" << tamano_actual << " -> " << t << "ms)" << endl;
        }
        
        generar_csv(tamanos_n, tiempos);
    }

    return 0;
}