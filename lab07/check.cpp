#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "sorting.cpp"
using namespace std;

vector<int> generateRandomArray(mt19937& generator) {
    uniform_int_distribution<int> length(0, 50);
    uniform_int_distribution<int> value(-100, 100);
    vector<int> arr(length(generator));
    for (int& element : arr) {
        element = value(generator);
    }
    return arr;
}

void printArray(const vector<int>& arr) {
    cout << '[';
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << arr[i];
    }
    cout << "]\n";
}

bool chekSortingFunction(vector<int> arr, vector<int> (*sortingFunction)(vector<int>)) {
    vector<int> sortedArr = sortingFunction(arr);
    vector<int> expectedArr = arr;
    sort(expectedArr.begin(), expectedArr.end());
    if (sortedArr != expectedArr) {
        cout << "Исходный массив: ";
        printArray(arr);
        cout << "Ожидалось: ";
        printArray(expectedArr);
        cout << "Получено: ";
        printArray(sortedArr);
        return false;
    }
    return true;
}

int main() {
    mt19937 generator(42);
    int checks = 0;
    const char* names[] = {"bubbleSort", "insertionSort", "selectionSort"};
    vector<int> (*functions[])(vector<int>) = {
        bubbleSort, insertionSort, selectionSort
    };

    vector<vector<int>> arrays = {{}, {5}, {2, 2, 1}};
    for (int trial = 0; trial < 100; ++trial) {
        arrays.push_back(generateRandomArray(generator));
    }

    for (const vector<int>& arr : arrays) {
        for (int i = 0; i < 3; ++i) {
            if (!chekSortingFunction(arr, functions[i])) {
                cout << "Ошибка в " << names[i] << '\n';
                return 1;
            }
            ++checks;
        }
    }
    cout << "OK: " << checks << " проверок\n";
    return 0;
}
