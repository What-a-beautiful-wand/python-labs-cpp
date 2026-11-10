#include <iostream>
#include <vector>
using namespace std;

vector<vector<float>> transpose(const vector<vector<float>>& matrix) {
    if (matrix.empty()) return {};
    int base_len = matrix[0].size();
    for (const auto& row : matrix) {
        if (row.size() != base_len) {
            throw invalid_argument("Это не матрица");
        }
    }
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    vector<vector<float>> transposed(cols, vector<float>(rows));
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    
    return transposed;
}

vector<vector<float>> row_sum(const vector<vector<float>>& matrix) {
    if (matrix.empty()) return {};
    int base_len = matrix[0].size();
    for (const auto& row : matrix) {
        if (row.size() != base_len) {
            throw invalid_argument("Это не матрица");
        }
    }
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    vector<vector<float>> result(rows, vector<float>(cols));
    
    for (size_t i = 0; i < rows; ++i) {
        float sum = 0;
        for (size_t j = 0; j < cols; ++j) {
            sum += matrix[i][j];
            result[i][j] = sum;
        }
    }
    
    return result;
}

vector<vector<float>> col_sum(const vector<vector<float>>& mat) {
    return transpose(row_sum(transpose(mat)));
}

float det(const vector<vector<float>>& matrix) {
    if (matrix.empty()) {
        throw invalid_argument("Пустая матрица");
    }
    int base_len = matrix[0].size();
    for (const auto& row : matrix) {
        if (row.size() != base_len) {
            throw invalid_argument("Это не матрица");
        }
    }
    size_t n = matrix.size();
    if (n != base_len) {
        throw invalid_argument("Матрица не квадратная");
    }

    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        float determinant = 0;
        for (size_t j = 0; j < n; ++j) {
            vector<vector<float>> submatrix(n - 1, vector<float>(n - 1));
            for (size_t i = 1; i < n; ++i) {
                size_t sub_col = 0;
                for (size_t k = 0; k < n; ++k) {
                    if (k == j) continue;
                    submatrix[i - 1][sub_col++] = matrix[i][k];
                }
            }
            determinant += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * det(submatrix);
        }
        return determinant;
    }
}

vector<vector<float>> multiply(const vector<vector<float>>& A, const vector<vector<float>>& B) {
    if (A.empty() || B.empty()) {
        throw invalid_argument("Одна из матриц пуста");
    }
    int base_len_A = A[0].size();
    for (const auto& row : A) {
        if (row.size() != base_len_A) {
            throw invalid_argument("Это не матрица A");
        }
    }
    int base_len_B = B[0].size();
    for (const auto& row : B) {
        if (row.size() != base_len_B) {
            throw invalid_argument("Это не матрица B");
        }
    }
    if (base_len_A != B.size()) {
        throw invalid_argument("Количество столбцов в A должно быть равно количеству строк в B");
    }

    size_t rows_A = A.size();
    size_t cols_A = A[0].size();
    size_t cols_B = B[0].size();
    
    vector<vector<float>> result(rows_A, vector<float>(cols_B, 0));
    
    for (size_t i = 0; i < rows_A; ++i) {
        for (size_t j = 0; j < cols_B; ++j) {
            for (size_t k = 0; k < cols_A; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return result;
}