#include <vector>
#include <map>
#include <iostream>

using namespace std;

// This is only usable with the printVector function in printVector.cpp
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