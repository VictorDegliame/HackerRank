#include <iostream>
#include <string>
#include <cassert>
#include <unordered_set>
#include <ctime>
#include <vector>
#include <algorithm>
#include <thread>
#include <climits>

using namespace std;

class Solver {
  public:
	Solver(int n) : N(n) {
		startTime = clock();
		buffer.reserve(N);
		generateCoefs();
		solve();
	}

	void solve(int maxn = -1) {
		assert(maxn < NMAX && "maxn shall not be greater than anticipated");

		if (maxn < 0)
			maxn = N;

		initializeBoard();

		search();
		printSolution();
	}

  private:
	int gcd(int a, int b) {
		if (b != 0)
			return gcd(b, a % b);

		return a;
	}

	void printCoefs() {
		for (int i = 1; i < NMAX; ++i) {
			for (int j = 1; j < 2 * NMAX; ++j) {
				if (j == NMAX)
					continue;
				cout << coefs[i][j] << " ";
			}
			cout << endl;
		}
	}

	float getCoef(int dy, int dx) {
		if (dy < 0) {
			dx = -dx;
			dy = -dy;
		}
		return coefs[dy][NMAX + dx];
	}

	void generateCoefs() {
		const int &N = NMAX;
		for (int dx = 1; dx < N; ++dx) {
			for (int dy = 1; dy < N; ++dy) {
				int commonDiv = gcd(dx, dy);
				if (commonDiv == 1) {
					coefs[dy][N + dx] = 1.0 * dy / dx;
					coefs[dy][N - dx] = -1.0 * dy / dx;
				} else {
					int dx2 = dx / commonDiv;
					int dy2 = dy / commonDiv;
					coefs[dy][N + dx] = coefs[dy2][N + dx2];
					coefs[dy][N - dx] = coefs[dy2][N - dx2];
				}
			}
		}
	}

	// Initialize the board with random numbers
	void initializeBoard() {
		for (int r = 0; r < N; ++r)
			board[r] = rand() % N;
	}

	void printSolution() {
		cout << "===========================================================" << endl;
		cout << "calculated in " << (float)(clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
		cout << "echo " << N << endl << "echo ";
		for (int i = 0; i < N; ++i)
			cout << board[i] + 1 << " ";
		cout << endl;
		/*for (int i=0; i<N; ++i)
		    cout <<board[i] << ", ";
		cout <<endl;*/
		/*
		for (int r=0; r<N; ++r) {
		    for (int c=0; c<board[r]; ++c) {
		        cout <<" ";
		    }
		    cout << "#" <<endl;
		}*/
		cout << "===========================================================" << endl;
	}

	int fieldCost(int row, int col, bool halfboard = false) {
		int maxrow = halfboard ? row : N;
		int maxazimuths = halfboard ? row : N - 1;
		int cost = 0;
		int ur = row + col;
		int ul = row - col;
		unordered_set<float> azimuths;
		for (int k = 0; k < maxrow; ++k) {
			if (k == row)
				continue;
			int qur = k + board[k];
			int qul = k - board[k];
			if (qur == ur || qul == ul || board[k] == col)
				cost += 1;
			int dy = row - k;
			int dx = col - board[k];
			azimuths.insert(getCoef(dy, dx));
		}
		cost += (maxazimuths - azimuths.size());
		return cost;
	}

	// Find a random row with a cost greater than 0 (meaning their column is wrong)
	int findNonzerocostRow() {
		vector<int>* badrows = &buffer;
		badrows->clear();
		for (int r = 0; r < N; ++r) {
			if (fieldCost(r, board[r]) > 0) {
				badrows->push_back(r);
			}
		}
		if (badrows->empty())
			return -1;
		// Get one bad row at random
		int row = (*badrows)[rand() % badrows->size()];
		// cout << "fixing row " << row
		//      << ", bad rows num=" << badrows->size() << endl;
		return row;
	}

	// Find the row with the greater cost
	int findMaxcostRow() {
		vector<int>* maxrows = &buffer;
		maxrows->clear();
		int maxcost = 0;
		for (int r = 0; r < N; ++r) {
			int cost = fieldCost(r, board[r]);
			if (cost > maxcost) {
				maxrows->clear();
				maxcost = cost;
			}
			if (cost == maxcost) {
				maxrows->push_back(r);
			}
		}
		if (maxcost == 0)
			return -1;
		// Get one bad row at random
		int row = (*maxrows)[rand() % maxrows->size()];
		// cout << "fixing row " << row
		//      << " with cost " << maxcost
		//      << endl;
		return row;
	}

	// Goes over all columns of a specific row and sets its column to the one with the minimum cost.
	void improveRow(int row) {
		vector<int>* mincols = &buffer;
		mincols->clear();
		// mincost is initialized with the current row score.
		int mincost = fieldCost(row, board[row]);
		// For each possible column
		for (int c = 0; c < N; ++c) {
			// Skip the column it is already on
			if (c == board[row])
				continue;
			int cost = fieldCost(row, c);
			if (cost < mincost) {
				mincols->clear();
				mincost = cost;
			}
			if (cost == mincost) {
				mincols->push_back(c);
			}
		}
		if (!mincols->empty())
			board[row] = (*mincols)[rand() % mincols->size()];
	}

	void search() {
		int iteration = 0;
		while (true) {
			++iteration;
			// Every 10 iterations, just pick one bad row to randomize a bit
			int row = iteration % 10 != 0 ? findMaxcostRow() : findNonzerocostRow();
			if (row < 0) {
				cout << "Found after " << iteration << " iterations" << endl;
				return;
			}
			if (rand() % ITER_UNTIL_RANDOM == 0) {
				// to break out of local minimum, randomize a row once in a while
				// cout << "randomizing row " << row << endl;
				board[row] = rand() % N;
			} else {
				improveRow(row);
			}
		}
	}

  private:
	static const int NMAX = 999;
	static const int ITER_UNTIL_RANDOM = 50;

	int N;
	float coefs[NMAX][2 * NMAX];
	int board[NMAX];
	time_t startTime;


	// This vector will have size N and will be reused everytime we need a vector of that size for computations.
	vector<int> buffer;
};

int main(int argc, char** argv) {
	srand(time(0));

	int n = 25;

	if (argc == 2)
		n = stoi(argv[1]);

	Solver s(n);
	return 0;
}