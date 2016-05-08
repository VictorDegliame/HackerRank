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

int main(void) {

	int n;
	cin >> n;
	vector<int> v(n, 0);
	cin >> v[0];

	int i = 1;
	for (; i < n; ++i) {
		cin >> v[i];
		if (v[i - 1] > v[i]) {
			// We have reached a point were the vector is not sorted anymore
			i++;
			break;
		}
	}

	int breakingPoint = i - 2;
	int backToNormalPoint = -1;
	// Look for a potential sequence we can reverse
	for (; i < n && backToNormalPoint < 0; ++i) {
		cin >> v[i];
		if (v[i - 1] < v[i]) {
			// We have reached a point were the sequence is not decreasing anymore)
			backToNormalPoint = i;
		}
	}

	if (backToNormalPoint < 0) backToNormalPoint = i - 1;
	int swapPoint = -1;
	bool swapPossible = false;

	// If there is a lone misplaced integer, then we must try to swap it.
	// This means that we need to make sure that a reverse order of size 2 is not possible
	if ((backToNormalPoint - breakingPoint) == 2 && breakingPoint + 2 < n && v[breakingPoint] > v[breakingPoint + 2]) {
		// The length of the reversed sequence is 1 so we can only swap the breaking point number
		// Look for that number with which we might be able to swap.
		for (; i < n; ++i) {
			cin >> v[i];
			if (v[i - 1] > v[i]) {
				// We have reached the potential point to swap
				++i;
				break;
			}
		}
		swapPoint = i - 1;
		cin >> v[i];
		++i;
		// Can we swap?
		swapPossible = !(breakingPoint > 0 && v[breakingPoint - 1] > v[swapPoint]) && v[swapPoint] <= v[breakingPoint + 1] &&
						v[swapPoint - 1] <= v[breakingPoint] && !(swapPoint < n - 1 && v[breakingPoint] > v[swapPoint + 1]);
		if (!swapPossible) {
			// Then nothing is possible
			cout << "no" << endl;
			return 0;
		}
		else {
			swap(v[breakingPoint], v[swapPoint]);
		}
	}

	// Now we know if we have a reversing sequence or a possible swap. Check that the remaining vector is sorted.
	for (; i < n; ++i) {
		cin >> v[i];
		if (v[i - 1] > v[i]) {
			// Array is still not sorted
			++i;
			break;
		}
	}
	int add = (backToNormalPoint - breakingPoint) == 1 ? 1 : 0;

	if (!swapPossible && (backToNormalPoint - breakingPoint) <= 2) {
		swapPoint = backToNormalPoint - 1 + add;
		swapPossible = !(breakingPoint > 0 && v[breakingPoint - 1] > v[swapPoint]) && v[swapPoint] <= v[breakingPoint + 1] &&
						v[swapPoint - 1] <= v[breakingPoint] && !(swapPoint < n - 1 && v[breakingPoint] > v[swapPoint + 1]);
	}

	if (i >= n && swapPossible) {
		cout << "yes" << endl;
		cout << "swap " << breakingPoint + 1 << " " << (swapPossible ? swapPoint + 1: backToNormalPoint + add) << endl;
	}
	// else if we have encountered another misplaced value (i < n) or
	// the array is not sorted after reversing the sequence
	else if (i < n || (!swapPossible && (v[breakingPoint] > v[backToNormalPoint] || (breakingPoint > 0 && v[breakingPoint - 1] > v[backToNormalPoint - 1])))) {
		cout << "no" << endl;
	}
	else {
		cout << "yes" << endl;
		cout << "reverse " << breakingPoint + 1 << " " << backToNormalPoint << endl;
	}

	return 0;
}