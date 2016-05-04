#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long factorialWithBoundaries(long high, long low) {
    if (high <= low) return 1;
    long res = high--;
    while (high > low) res *= high--;
    
    return res;
}

int main() {
    int nbTests;
    int n;
    cin >> nbTests;
    for (int i = 0; i < nbTests; ++i) {
        cin >> n;
        vector<int> v(n, 0);
        for (int j = 0; j < n; ++j) {
            cin >> v[j];
        }
        
        sort(v.begin(), v.end());
        
        long nbDuplicates = 1;
        long res = 0;
        int prev = v[0];
        for (int j = 1; j < n; ++j) {
            if (prev == v[j]) {
                nbDuplicates++;
            }
            else {
                if (nbDuplicates > 1)
                    res += factorialWithBoundaries(nbDuplicates, nbDuplicates - 2);
                nbDuplicates = 1;
            }
            prev = v[j];
        }
        if (nbDuplicates > 1)
            res += factorialWithBoundaries(nbDuplicates, nbDuplicates - 2);
        
        cout << res << endl;
    }
    return 0;
}

