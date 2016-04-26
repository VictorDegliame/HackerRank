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

template<typename T>
void printVector(vector<T> v) {
	for (const auto& val : v)
		cout << val << " ";
}

void partition(vector <int>  ar) {
    int p = ar[0];
    vector<int> equal;
    vector<int> right;
    for (const auto& v : ar) {
        if (v < p)
            cout << v << " ";
        else if (v == p)
            equal.push_back(v);
        else
            right.push_back(v);
    }
    printVector(equal);
    printVector(right);
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

   partition(_ar);
   
   return 0;
}
