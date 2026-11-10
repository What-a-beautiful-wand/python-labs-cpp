#include <cmath>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

using StudentRecord = tuple<string, string, double>;

vector<string> utf8_letters(const string& text) {
    vector<string> letters;
    for (size_t i = 0; i < text.size();) {
        unsigned char first = static_cast<unsigned char>(text[i]);
        size_t length = 0;
        if (first <= 0x7F) length = 1;
        else if (first >= 0xC2 && first <= 0xDF) length = 2;
        else if (first >= 0xE0 && first <= 0xEF) length = 3;
        else if (first >= 0xF0 && first <= 0xF4) length = 4;

        if (length == 0 || length > text.size() - i) {
            throw invalid_argument("ФИО должно быть строкой UTF-8");
        }
        for (size_t j = 1; j < length; ++j) {
            unsigned char byte = static_cast<unsigned char>(text[i + j]);
            if ((byte & 0xC0) != 0x80) {
                throw invalid_argument("ФИО должно быть строкой UTF-8");
            }
        }
        if (length >= 3) {
            unsigned char second = static_cast<unsigned char>(text[i + 1]);
            if ((first == 0xE0 && second < 0xA0)
                || (first == 0xED && second >= 0xA0)
                || (first == 0xF0 && second < 0x90)
                || (first == 0xF4 && second >= 0x90)) {
                throw invalid_argument("ФИО должно быть строкой UTF-8");
            }
        }
        letters.push_back(text.substr(i, length));
        i += length;
    }
    return letters;
}

const string lowercase_letters = "abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const string uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

string uppercase_letter(const string& letter) {
    size_t position = lowercase_letters.find(letter);
    return position == string::npos ? letter
                                   : uppercase_letters.substr(position, letter.size());
}

string lowercase_letter(const string& letter) {
    size_t position = uppercase_letters.find(letter);
    return position == string::npos ? letter
                                   : lowercase_letters.substr(position, letter.size());
}

string normalize_spaces(const string& text) {
    istringstream words(text);
    string word;
    string result;

    while (words >> word) {
        if (!result.empty()) {
            result += ' ';
        }
        result += word;
    }
    return result;
}

// Форматирует запись (ФИО, группа, GPA).
// invalid_argument: ФИО не содержит 2–3 слов, группа пуста,
// GPA не является конечным числом от 0 до 5 либо ФИО содержит неверный UTF-8.
// Типы полей проверяются компилятором через StudentRecord.
string format_record(const StudentRecord& rec) {
    const auto& [fio, group, gpa] = rec;

    if (!isfinite(gpa) || gpa < 0.0 || gpa > 5.0) {
        throw invalid_argument("GPA должен быть числом от 0 до 5");
    }

    string cleaned_group = normalize_spaces(group);
    if (cleaned_group.empty()) {
        throw invalid_argument("Группа не может быть пустой");
    }

    istringstream words(fio);
    vector<vector<string>> parts;
    string word;
    while (words >> word) {
        parts.push_back(utf8_letters(word));
    }

    if (parts.size() < 2 || parts.size() > 3) {
        throw invalid_argument("Укажите фамилию, имя и при наличии отчество");
    }

    string surname = uppercase_letter(parts[0][0]);
    for (size_t i = 1; i < parts[0].size(); ++i) {
        surname += lowercase_letter(parts[0][i]);
    }

    string initials;
    for (size_t i = 1; i < parts.size(); ++i) {
        initials += uppercase_letter(parts[i][0]);
        initials += '.';
    }

    ostringstream result;
    result.imbue(locale::classic());
    result << surname << ' ' << initials
           << ", гр. " << cleaned_group
           << ", GPA " << fixed << setprecision(2) << gpa;
    return result.str();
}

int main() {
    vector<StudentRecord> students = {
        {"Иванов Иван Иванович", "BIVT-25", 4.6},
        {"Петров Пётр", "IKBO-12", 5.0},
        {"Петров Пётр Петрович", "IKBO-12", 5.0},
        {"  сидорова  анна   сергеевна ", "ABB-01", 3.999}
    };

    try {
        for (const StudentRecord& student : students) {
            cout << format_record(student) << '\n';
        }
    } catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
