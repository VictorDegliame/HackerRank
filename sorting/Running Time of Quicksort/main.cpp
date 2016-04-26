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

int quickSort(vector <int> &ar, int left, int right) {
    if (right <= left)
        return 0;

    int nbSwaps = 0;
    int i = left;
    int j = left;
    int p = ar[right];

    for (; i < right; ++i) {
        if (ar[i] < p) {
            //cout << "Swapping " << ar[i] << " and " << ar[j] << endl;
            swap(ar[i], ar[j]);
            nbSwaps++;
            j++;
        }
    }
    //cout << "End Swapping " << ar[right] << " and " << ar[j] << endl;
    nbSwaps++;
    swap(ar[right], ar[j]);
    return nbSwaps + quickSort(ar, left, j - 1) + quickSort(ar, j + 1, right);
}

int insertionSort(vector <int>  ar) {
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
    return nbShifts;
}

int main(void) {
    vector <int>  _ar;
    int _ar_size;
    cin >> _ar_size;
    for (int _ar_i = 0; _ar_i < _ar_size; _ar_i++) {
        int _ar_tmp;
        cin >> _ar_tmp;
        _ar.push_back(_ar_tmp);
    }

    cout << (insertionSort(_ar) - quickSort(_ar, 0, _ar.size() - 1)) << endl;
    return 0;
}