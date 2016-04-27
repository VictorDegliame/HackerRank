#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    vector<string> vecStrings[100];
    int n;
    int c;
    string w;
    cin >> n;
    int totalNum = n;

    for (; n > 0; --n) {
        cin >> c;
        cin >> w;
        if (n > totalNum / 2)
            w = "-";
        vecStrings[c].emplace_back(w);
    }

    for (int i = 0; i < 100; ++i) {
        for (const auto& s : vecStrings[i])
            cout << s << " ";
    }

    return 0;
}
