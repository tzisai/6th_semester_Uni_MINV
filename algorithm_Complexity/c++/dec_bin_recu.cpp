#include <bits/stdc++.h>
using namespace std;

// Decimal to binary conversion
// using recursion
int decToBin(int d)
{
    if (d == 0) 
        return 0; 
    else
        return (d % 2 + 10 * decToBin(d / 2));
}

// Driver code 
int main()
{
    int d = 10;
    cout << decToBin(d);
    return 0;
}