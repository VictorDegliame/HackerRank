#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <bitset>
using namespace std;

const int N_MAX = 15;

bitset<N_MAX> makeMove(const bitset<N_MAX>& mask, int idx, bool move) {
	auto res = mask;
	res[idx] = move;
	return res;
}

bool isIncreasing(const bitset<N_MAX>& mask, const vector<int>& v) {
	int prev = -1;
	for (int i = 0; i < v.size(); ++i) {
		// If the number at current index i is still in the vector, test if it forms increasing sequence
		if (mask.test(i)) {
			if (v[i] >= prev) {
				prev = v[i];
			} else {
				return false;
			}
		}
	}
	return true;
}

bool isWinningPosition(const bitset<N_MAX>& mask,
                       unordered_set<bitset<N_MAX>>& winningPosCache) {

	return winningPosCache.count(mask) > 0;
}

bool isLosingPosition(const bitset<N_MAX>& mask, vector<int>& v, unordered_set<bitset<N_MAX>>& winningPosCache) {
	if (isIncreasing(mask, v)) // If it is already increasing, the player who called this function has already won.
		return true;
	if (isWinningPosition(mask, winningPosCache)) // Have we already seen this position in the past (and was it winning)?
		return false;

	// Go through all available moves at this stage of the recursion
	for (int i = 0; i < v.size(); ++i) {
		while (i < v.size() && !mask.test(i)) ++i; // Find the next bit set to true
		if (i >= v.size())
			break;
		auto nextMove = makeMove(mask, i, 0);
		// If the current position is a winning or the next one is losing (for Bob), then Alice wins.
		if (isLosingPosition(nextMove, v, winningPosCache)) {
			// If we are here, it means that we are at a winning position
			// because there is a losing position available on the next move
			// Let's remember it for future recursive calls.
			winningPosCache.insert(mask);
			// We can return right away because we play optimally so we will always chose the winning move "nextMove"
			return false;
		}
	}
	// If we reach this, it means that from here all positions are winning so this one is necessarily losing.
	return true;
}

// This function initializes the recursion
void findWhoWins(vector<int>& v, unordered_set<bitset<N_MAX>>& winningPosCache) {
	bitset<N_MAX> mask(-1); // Init all to 1
	winningPosCache.clear();
	// Player here is Alice
	if (isLosingPosition(mask, v, winningPosCache)) {
		cout << "Bob" << endl;
		return;
	}
	cout << "Alice" << endl;
}

int main() {
	int n, t;
	vector<int> v(N_MAX, -1);
	// Will contain our winning positions for dynamic programming
	unordered_set<bitset<N_MAX>> winningPosCache;

	cin >> t;
	// Go over all test cases.
	for (; t > 0; --t) {
		v.clear();
		cin >> n;
		for (int i = 0; i < n; ++i) {
			int c;
			cin >> c;
			v.push_back(c);
		}
		findWhoWins(v, winningPosCache);
	}

	return 0;
}
