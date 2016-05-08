#include <vector>
#include <iostream>

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