#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int count[100] = {0};
    int n;
    int c;
    cin >> n;

    for (; n > 0; --n) {
        cin >> c;
        count[c]++;
    }

    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < count[i]; ++j)
            cout << i << " ";

    return 0;
}
