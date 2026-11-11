#include <iostream>
#include <cctype>
#include <string>
using namespace std;

string normalize(const string& text, bool casefold = true, bool yo2e = true) {
    string result = text;
    if (casefold) {
        for (char& c : result) {
            unsigned char byte = static_cast<unsigned char>(c);
            if (byte < 128) {
                c = static_cast<char>(tolower(byte));
            }
        }
        const string uppercase = u8"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        const string lowercase = u8"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
        for (size_t index = 0; index < uppercase.size(); index += 2) {
            const string letter = uppercase.substr(index, 2);
            size_t position = 0;
            while ((position = result.find(letter, position)) != string::npos) {
                result.replace(position, 2, lowercase.substr(index, 2));
                position += 2;
            }
        }
    }
    if (yo2e) {
        for (const string letter : {u8"ё", u8"Ё"}) {
            size_t position = 0;
            while ((position = result.find(letter, position)) != string::npos) {
                const string replacement = (letter == u8"ё") ? u8"е" : u8"Е";
                result.replace(position, letter.size(), replacement);
                position += replacement.size();
            }
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
