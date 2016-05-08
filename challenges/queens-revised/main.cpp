#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 9;

template<typename T>
void printVector(ostream& os, const vector<T>& vec) noexcept {
	// os << "[";
	if (vec.size() != 0) {
		for (auto it = begin(vec); it != end(vec) - 1; ++it) {
			os << *it + 1 << " ";
		}
		os << vec.back() + 1;
	}
	// os << "]" << endl;
	os << endl;
}

void printBoard(vector<int>& queens) {

	cout << N << endl;
	printVector(cout, queens);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (queens[j] == i)
				cerr << "X ";
			else
				cerr << "- ";
		}
		cerr << endl;
	}
	cerr << "...................................." << endl;
}

void placeQueens(int pos, vector<int>& queens) {
	// cerr << "Evaluating queen " << pos + 1 << endl;
	// Try to place the queen on every vertical line until you find the right one
	for (int i = 0; i < N; ++i) {
		// cerr << "For queen at X = " << pos << endl;
		// Would that queen be well placed? Look if we don't break any rule with previously placed queens.
		bool placementOk = true;
		// For all queens placed behind me:
		int offsetX = 1;
		for (int j = pos - 1; j >= 0 && placementOk; --j, ++offsetX) {
			int diffFirst2Queens = i - queens[j];
			// check that we are not on the same line (only need to check pairs of 2 queens)
			if (queens[j] == i || abs(diffFirst2Queens) == offsetX) {
				// cerr << "Can't place queen at position " << pos << " " << i << endl;
				placementOk = false;
				break;
			}
			// Check that there is not a third queen on the same line!
			for (int jumpSize = 1; placementOk && jumpSize <= (pos - j); jumpSize++) {
				int offsetY = diffFirst2Queens;
				//  && (N - abs(offsetY)) >= 0
				for (int k = j - jumpSize; k >= 0; k -= jumpSize, offsetY += diffFirst2Queens) {
					// cerr << "I am trying to place queen (" << pos << ", " << i << "), examining queens " << j << " and " << k << endl;
					// cerr << "(" << pos + 1 << ", " << i + 1 << "), " <<
					//      "(" << j + 1 << ", " << queens[j] + 1 << "), " <<
					//      "(" << k + 1 << ", " << queens[k] + 1 << ")" << endl;
					// cerr << "OffsetX is: " << offsetX << " OffsetY is: " << offsetY << endl;
					int diffLast2Queens = queens[j] - queens[k];
					// cerr << "diffLast2Queens is: " << diffLast2Queens << endl;
					if (diffLast2Queens == offsetY) {
						// cerr << "(" << pos + 1 << ", " << i + 1 << ") and " <<
						//      "(" << j + 1 << ", " << queens[j] + 1 << ") and " <<
						//      "(" << k + 1 << ", " << queens[k] + 1 << ") are on the same line" << endl;
						placementOk = false;
						break;
					}
				}
			}
		}
		if (placementOk) {
			// cerr << "Placing a queen at pos " << pos << " " << i << endl;
			queens[pos] = i;
			if (pos + 1 == N) {
				printBoard(queens);
				exit(0);
			} else {
				placeQueens(pos + 1, queens);
			}
		}
	}
}

int main() {
	vector<int> queens(N, -1);

	cerr << "...................................." << endl;

	placeQueens(0, queens);

	return 0;
}
