#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

int main() {
    int n;
    cout << "in_1: "; cin >> n;
    int onSite = 0;
    int remote = 0;
    for (int i = 2; i < n + 2; i++) {
        string surname, name, age, format;
        cout << "in_" << i << ": "; cin >> surname >> name >> age >> format;
        if (format == "True") {
            onSite++;
        } else if (format == "False") {
            remote++;
        }
    }
    cout << "out: " << onSite << ' ' << remote << endl;

    return 0;
}