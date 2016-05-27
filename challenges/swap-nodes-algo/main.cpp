#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	int index;
	Node(int idx) : left(nullptr), right(nullptr), index(idx) {}
	Node() = default;
	friend ostream& operator<<(ostream& os, const Node& n) { return os << n.index;}
};

template<typename T>
void printTreeInOrder(ostream& os, const T* t) {
	if (t == nullptr)
		return;
	printTreeInOrder(os, t->left);
	os << *t << " ";
	printTreeInOrder(os, t->right);
}

void swapChildren(Node* t, int K, int depth) {
	if (t == nullptr)
		return;
	if (depth % K == 0)
		swap(t->left, t->right);
	swapChildren(t->left, K, depth + 1);
	swapChildren(t->right, K, depth + 1);
}

int main() {
	int N, T;
	cin >> N;
	vector<Node> v(4 * N + 2, Node(-1));
	int idx1, idx2;
	for (int i = 0; i < N; ++i) {
		cin >> idx1 >> idx2;
		v[i].index = i + 1;
		if (idx1 > 0)
			v[i].left = &v[idx1 - 1];
		if (idx2 > 0)
			v[i].right = &v[idx2 - 1];
	}
	cin >> T;
	int K;
	for (; T > 0; --T) {
		cin >> K;
		swapChildren(&v[0], K, 1);
		printTreeInOrder(cout, &v[0]);
		cout << endl;
	}

	return 0;
}
