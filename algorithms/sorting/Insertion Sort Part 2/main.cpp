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

void printVector(vector<int> vec){
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;
}

void insertionSort(vector <int>  ar) {
    int startIndex = 1;
    int i = startIndex;
    int cur = ar[startIndex];
    while (true) {
        if (i > 0 && ar[i - 1] > cur) {
            ar[i] = ar[i - 1];
            i--;
            continue;
        }
        ar[i] = cur;
        printVector(ar);

        startIndex++;
        if (startIndex >= ar.size())
            return;

        i = startIndex;
        cur = ar[startIndex];
    }
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
