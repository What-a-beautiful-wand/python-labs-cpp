#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int linear_search(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binary_search(const vector<int>& arr, int target) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

pair<int, int> two_sum_brute(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (static_cast<long long>(arr[i]) + arr[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

pair<int, int> two_sum_fast(const vector<int>& arr, int target) {
    unordered_map<long long, int> seen;
    for (size_t i = 0; i < arr.size(); ++i) {
        long long need = static_cast<long long>(target) - arr[i];
        auto it = seen.find(need);
        if (it != seen.end()) {
            return {it->second, static_cast<int>(i)};
        }
        seen[arr[i]] = static_cast<int>(i);
    }
    return {-1, -1};
}
