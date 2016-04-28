#include <bits/stdc++.h>
using namespace std;

template<typename T>
void printVector(vector<T> v) {
    for (const auto& val : v)
        cout << val << " ";
    cout << endl;
}

void quickSort(vector <int> &ar, int left, int right) {
    if (right <= left)
        return;

    int i = left;
    int j = left;
    int p = ar[right];

    for (; i < right; ++i) {
        if (ar[i] < p) {
            //cout << "Swapping " << ar[i] << " and " << ar[j] << endl;
            swap(ar[i], ar[j]);
            j++;
        }
    }
    //cout << "End Swapping " << ar[right] << " and " << ar[j] << endl;

    swap(ar[right], ar[j]);
    quickSort(ar, left, j - 1);
    quickSort(ar, j + 1, right);
}

int main() {
    int n;
    cin >> n;

    if (n < 2)
        return 0;

    vector <int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    int minDiff = abs(arr[0] - arr[1]);
    vector<int> res = {arr[0], arr[1]};

    for (int i = 2; i < n - 1; ++i) {
        int diff = abs(arr[i] - arr[i + 1]);
        if (diff < minDiff) {
            res.clear();
            minDiff = diff;
        }

        if (diff == minDiff) {
            res.push_back(arr[i]);
            res.push_back(arr[i + 1]);
        }
    }

    printVector(res);

    return 0;
}