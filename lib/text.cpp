#include <iostream>
#include <string>
using namespace std;

string normalize(const string& text, bool casefold = true, bool yo2e = true) {
    string result = text;
    if (casefold) {
        for (char& c : result) {
            c = tolower(c);
        }
    }
    if (yo2e) {
        size_t pos = result.find('ё');
        while (pos != string::npos) {
            result[pos] = 'е';
            pos = result.find('ё', pos + 1);
        }
    }
    return result;
}

int main() {
    string text = "Привет, Ёжик!";
    string normalizedText = normalize(text);
    cout << "Original: " << text << endl;
    cout << "Normalized: " << normalizedText << endl;
    return 0;
}