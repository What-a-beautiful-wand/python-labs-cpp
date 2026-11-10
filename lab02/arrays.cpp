#include <iostream>
#include <vector>
#include <stdexcept>
#include <tuple>
#include <utility>
using namespace std;

pair<double, double> min_max(const vector<double>& mat) {
    if (mat.empty()) {
        throw invalid_argument("Пустая матрица");
    }

    double min = mat[0];
    double max = mat[0];

    for (double num : mat) {
        if (num < min) {
            min = num;
        }
        if (num > max) {
            max = num;
        }
    }

    return {min, max};
}

void merge_sort(vector<double>& nums, vector<double>& buffer,
                size_t begin, size_t end) {
    if (end - begin < 2) {
        return;
    }

    size_t middle = begin + (end - begin) / 2;
    merge_sort(nums, buffer, begin, middle);
    merge_sort(nums, buffer, middle, end);

    size_t left = begin;
    size_t right = middle;
    size_t position = begin;

    while (left < middle && right < end) {
        if (nums[left] <= nums[right]) {
            buffer[position++] = nums[left++];
        } else {
            buffer[position++] = nums[right++];
        }
    }

    while (left < middle) {
        buffer[position++] = nums[left++];
    }
    while (right < end) {
        buffer[position++] = nums[right++];
    }

    for (size_t i = begin; i < end; ++i) {
        nums[i] = buffer[i];
    }
}


vector<double> unique_sorted(const vector<double>& mat) {
    vector<double> sorted_mat = mat;
    vector<double> buffer(sorted_mat.size());
    merge_sort(sorted_mat, buffer, 0, sorted_mat.size());

    vector<double> unique_mat;
    for (double num : sorted_mat) {
        if (unique_mat.empty() || num != unique_mat.back()) {
            unique_mat.push_back(num);
        }
    }

    return unique_mat;
}


vector<double> flatten(const vector<vector<double>>& mat) {
    vector<double> result;

    for (const vector<double>& row : mat) {
        for (double num : row) {
            result.push_back(num);
        }
    }

    return result;
}

int main() {
    vector<double> mat = {3, 6, 1, 22, 0 ,-1, 5};
    double min, max;
    try {
        tie(min, max) = min_max(mat);
        cout << "Минимальное значение: " << min << endl;
        cout << "Максимальное значение: " << max << endl;
        cout << "Уникальные значения по возрастанию: ";
        for (double num : unique_sorted(mat)) {
            cout << num << ' ';
        }
        cout << '\n';

        vector<vector<double>> nested_mat = {{1, 2}, {}, {3, 4, 5}};
        cout << "Элементы вложенных векторов: ";
        for (double num : flatten(nested_mat)) {
            cout << num << ' ';
        }
        cout << '\n';
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    return 0;
}
