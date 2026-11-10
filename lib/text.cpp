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
    return result;
}

int main() {
    string text = "Привет, Ёжик!";
    string normalizedText = normalize(text);
    cout << "Original: " << text << endl;
    cout << "Normalized: " << normalizedText << endl;
    return 0;
}