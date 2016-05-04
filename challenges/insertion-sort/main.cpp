#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

// Some debugging functions:
template<typename T>
void printVector(ostream& os, const vector<T>& vec) noexcept {
    os << "[";
    if (vec.size() != 0) {
        for (auto it = begin(vec); it != end(vec) - 1; ++it) {
            os << *it << ", ";
        }
        os << vec.back();
    }
    os << "]" << endl;
}

template <typename T1, typename T2>
void printMap(ostream& os, const map<T1, vector<T2>>& map) noexcept {
    os << "{" << endl;
    for (auto it = begin(map); it != end(map); ++it) {
        os << it->first << " -> ";
        printVector(os, it->second);
        if (next(it) != end(map))
            os << ", ";
        os << endl;
    }
    os << "}" << endl;
}

template <typename T1, typename T2>
void printMap(ostream& os, const map<T1, T2> map) noexcept {
    os << "{" << endl;
    for (auto it = begin(map); it != end(map); ++it) {
        os << it->first << " -> " << it->second;
        if (next(it) != end(map))
            os << ", ";
        os << endl;
    }
    os << "}" << endl;
}

int main() {
    int nbTests;
    cin >> nbTests;
    map<int, int> orderedMap;

    for (int i = 0; i < nbTests; ++i) {
        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            int c;
            cin >> c;
            int howManyAreBigger = 0;
            if (orderedMap.count(c) == 0) {
                // insert new key value pair
                orderedMap.insert(make_pair(c, 0));
            }
            orderedMap[c]++;
        }

        //printMap(cout, orderedMap);
        orderedMap.clear();
    }
    return 0;
}

