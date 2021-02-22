#include <iostream>

using namespace std;

template<typename T>
int binarySearch(T arr[], int n, T tar) {
    int l = 0, r = n -1, mid;

    // arr[l , r]
    while (l <= r) {

        mid = l + (r - l) / 2;

        if (arr[mid] == tar) {
            return mid;
        }

        if (arr[mid] < tar) {
            l = mid + 1;        // arr[mid+1, r]
        } else {
            r = mid - 1;        // arr[l, mid-1]
        }
    }
    return -1;
}



int main() {
    int arr[] = {1, 2, 4, 8, 10, 34, 53};

    cout << binarySearch(arr, 7, 4) << endl;
    return 0;
}
