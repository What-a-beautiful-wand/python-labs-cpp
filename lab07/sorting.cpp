#include <iostream>
#include <vector>
using namespace std;

vector<int> bubbleSort(vector<int> arr) {
    size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; i++) {
        bool is_sorted = true;
        for (size_t j = 0; j + 1 < n; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                is_sorted = false;
            }
        }
        if (is_sorted) {
            break;
        }
    }
    return arr;
}

vector<int> insertionSort(vector<int> arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
    return arr;
}

vector<int> selectionSort(vector<int> arr) {
    size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
    return arr;
}
