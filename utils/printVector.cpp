#include <vector>
#include <iostream>

using namespace std;

template<typename T>
void printVector(vector<T> v) {
	for (const auto& val : v)
		cout << val << " ";
		cout << endl;
}