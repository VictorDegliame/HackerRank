#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void insertionSort(vector<char>& v, char c) {
	//cout << "Inserting " << c << endl;
	v.push_back(c);
	int i = v.size() - 2;
	for (; i >= 0 && c < v[i]; --i) {
		v[i + 1] = v[i];
	}
	v[i + 1] = c;
}

int main() {
	int nbTests = 0;
	
	cin >> nbTests;
	
	string test = "";
	
	for (int i = 0; i < nbTests; ++i) {
		cin >> test;
		// Init the vector representing the sorted right side of the test string
		vector<char> right;
		right.push_back(test[test.length() - 1]);
		bool isAnswer = false;
		int j = test.length() - 2;
		for (; j >= 0; --j) {
			// Is there any bigger character on the right?
			int k = right.size() - 1;
			//cout << "test[j] = " << test[j] << " right[k] = " << right[k] << endl;
			for (; k >= 0 && test[j] < right[k]; k--);
			// If k has moved, then there was something bigger.
			if (k < (int)(right.size() - 1)) {
				// We want to swap the current char with the smallest greater char on its right.
				//cout << "swapping " << test[j] << " and " << right[k + 1] << endl;
				swap(test[j], right[k + 1]);
				isAnswer = true;
				break;
			}
			insertionSort(right, test[j]);
		}
		if (!isAnswer)
			cout << "no answer";
		else {
			for (int k = 0; k <= j; ++k)
				cout << test[k];
			for (char c : right)
				cout << c;
		}
		cout << endl;
	}
	
	return 0;
}
