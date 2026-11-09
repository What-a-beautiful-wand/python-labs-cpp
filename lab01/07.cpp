#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string encrypted;
    cout << "in: "; cin >>  encrypted;
    int n = static_cast<int>(encrypted.size());
    int start = -1;

    for (int i = 0; i < n; i++) {
        if (encrypted[i] >= 'A' && encrypted[i] <= 'Z') {
            start = i;
            break;
        }
    }

    if (start == -1) {
        cerr << "Не найдена заглавная буква\n";
        return 1;
    }

    for (int i = start + 1; i < n - 1; i++) {
        if (encrypted[i] >= '0' && encrypted[i] <= '9') {
            int second = i + 1;
            int step = second - start;

            string result;

            for (int j = start; j < n; j += step) {
                result += encrypted[j];

                if (encrypted[j] == '.') {
                    cout << result << '\n';
                    return 0;
                }
            }
        }
    }
    return 0;
}