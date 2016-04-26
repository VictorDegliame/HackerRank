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
    printVector(ar);
    quickSort(ar, left, j - 1);
    quickSort(ar, j + 1, right);
}

int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    return 0;
}