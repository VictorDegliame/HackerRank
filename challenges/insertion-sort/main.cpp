#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

long mergeSortCountLeftShifts(vector<int>& v, int left, int right, vector<int>& resultVector) {
    if (left == right) {
        resultVector[0] = v[left];
        return 0;
    }
    const int mid = (left + right) / 2;
    const int sizeLeft = mid - left + 1;
    vector<int> leftVec(sizeLeft);
    long res = mergeSortCountLeftShifts(v, left, mid, leftVec);
    const int sizeRight = right - mid;
    vector<int> rightVec(sizeRight);
    res += mergeSortCountLeftShifts(v, mid + 1, right, rightVec);

    int leftIt = 0;
    int rightIt = 0;
    int resPos = 0;

    while (leftIt < sizeLeft || rightIt < sizeRight) {
        while (leftIt < sizeLeft && (rightIt == sizeRight || leftVec[leftIt] <= rightVec[rightIt])) {
            resultVector[resPos++] = leftVec[leftIt++];
        }
        while (rightIt < sizeRight && (leftIt == sizeLeft || leftVec[leftIt] > rightVec[rightIt])) {
            resultVector[resPos++] = rightVec[rightIt++];
            res += mid - left + 1 - leftIt; // We shift by how many elements are left in the end of the left vector.
        }
    }

    return res;
}

int main() {
    int nbTests;
    cin >> nbTests;

    for (int i = 0; i < nbTests; ++i) {
        int n;
        cin >> n;
        vector<int> v(n, 0);
        for (int j = 0; j < n; ++j)
            cin >> v[j];
        vector<int> ignoredResult(n);
        cout << mergeSortCountLeftShifts(v, 0, n - 1, ignoredResult) << endl;
    }
    return 0;
}

