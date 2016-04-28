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
    string w;
    cin >> n;

    for (; n > 0; --n) {
        cin >> c;
        cin >> w;
        count[c]++;
    }

    int sum = 0;
    for (int i = 0; i < 100; ++i) {
        sum += count[i];
        cout << sum << " ";
    }

    return 0;
}
