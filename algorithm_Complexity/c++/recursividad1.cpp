#include <iostream>
using namespace std;

    void recu (int n){

        cout<<n<<endl;
        if(n>=1){
            recu(n-1);
        }
        else{
            return;
        }

        
    }

int main(){



recu(5);


    return 0;
}