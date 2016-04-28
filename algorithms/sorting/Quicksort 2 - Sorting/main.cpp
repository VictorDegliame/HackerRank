#include <bits/stdc++.h>
using namespace std;

template<typename T>
void printVector(vector<T> v) {
	for (const auto& val : v)
		cout << val << " ";
    cout << endl;
}

void quickSort(vector <int> &ar) {
    if (ar.size() <= 1)
        return;
    int p = ar[0];
    vector<int> left;
    vector<int> equal;
    vector<int> right;
    for (const auto& v : ar) {
        if (v < p)
            left.push_back(v);
        else if (v == p)
            equal.push_back(v);
        else
            right.push_back(v);
    }
    quickSort(left);
    quickSort(right);
    ar.clear();
    ar.insert(ar.end(), left.begin(), left.end());
    ar.insert(ar.end(), equal.begin(), equal.end());
    ar.insert(ar.end(), right.begin(), right.end());
    printVector(ar);
}

int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);

    return 0;
}
