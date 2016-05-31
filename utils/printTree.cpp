#include <iostream>

using namespace std;

template<typename T>
void printTreePreOrder(ostream& os, const T* t) {
	if (t == nullptr)
		return;
	os << *t << " ";
	printTreePreOrder(os, t->left);
	printTreePreOrder(os, t->right);
}

// Some debugging functions:
template<typename T>
void printTreeInOrder(ostream& os, const T* root) {
	if (root == nullptr)
		return;
	printTreeInOrder(os, root->left);
	os << *root << " ";
	printTreeInOrder(os, root->right);
}