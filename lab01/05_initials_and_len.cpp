#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string full_name, word, cleaned;
    cout << "ФИО: "; getline(cin, full_name);

    if (full_name.empty()) {
        throw invalid_argument("ФИО не может быть пустым");
    }

    istringstream words(full_name);

    while (words >> word) {
        if (!cleaned.empty()) {
            cleaned += ' ';
        }

        cleaned += word;
    }

    int length = 0;

    for (unsigned char c : cleaned) {
        if ((c & 0xC0) != 0x80) {
            length++;
        }
    }

    cout << "Без лишних пробелов: " << cleaned << '\n';
    cout << "Длина (символов): " << length << '\n';
    return 0;
}