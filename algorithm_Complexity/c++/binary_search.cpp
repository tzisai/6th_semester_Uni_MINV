#include <iostream>
#include <vector>
#include <random>
using namespace std;

void fill_vector(vector<int>& array, int n) {
    random_device randn;
    mt19937 gen(randn());   
    uniform_int_distribution<> distrib(1, 100);
    for (int i = 0; i < n; i++) array.push_back(distrib(gen));
}



int Binary_search(vector<int> arraysote,int buscar ){

    if(arraysote.size()%2==0){
        
    }




return encontrado;
}

int main(){



    return 0;
}