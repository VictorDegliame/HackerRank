#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> cache(k, 0);
	
	for (int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		c %= k;
		cache[c]++;
	}

	int res = cache[0];
	for (int i = 1; i < k; ++i) {
		res += max(cache[i], cache[k - i]);
		// Erase this pair so that we don't count it another time later in the loop when future i equals current (k - i)
		cache[i] = 0;
		cache[k - i] = 0;
	}
	cout << res << endl;
	
	return 0;
}
