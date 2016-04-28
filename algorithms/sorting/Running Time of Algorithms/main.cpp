#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

void insertionSort(vector <int>  ar) {
    int nbShifts = 0;
    int startIndex = 1;
    int i = startIndex;
    int cur = ar[startIndex];
    while (true) {
        if (i > 0 && ar[i - 1] > cur) {
            ar[i] = ar[i - 1];
            nbShifts++;
            i--;
            continue;
        }
        ar[i] = cur;

        startIndex++;
        if (startIndex >= ar.size())
            break;

        i = startIndex;
        cur = ar[startIndex];
    }
    cout << nbShifts;
}

int main(void) {
    vector <int>  _ar;
    int _ar_size;
    cin >> _ar_size;
    for(int _ar_i=0; _ar_i<_ar_size; _ar_i++) {
        int _ar_tmp;
        cin >> _ar_tmp;
        _ar.push_back(_ar_tmp); 
    }

    insertionSort(_ar);
    return 0;
}