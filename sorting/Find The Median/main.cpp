#include <bits/stdc++.h>
using namespace std;

void findMedian(vector <int> &arr, int left, int right, int median) {
    if (right <= left) {
        cout << arr[median] << endl;
        return;
    }

    int i = left;
    int j = left;
    int p = arr[right];

    for (; i < right; ++i) {
        if (arr[i] < p) {
            swap(arr[i], arr[j]);
            j++;
        }
    }

    swap(arr[right], arr[j]);

    if (median <= j)
        findMedian(arr, left, j - 1, median);
    if (median > j)
        findMedian(arr, j + 1, right, median);
}

int main() {
    int n;
    cin >> n;

    vector <int> arr(n);
    for (int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    findMedian(arr, 0, n - 1, n / 2);

    return 0;
}