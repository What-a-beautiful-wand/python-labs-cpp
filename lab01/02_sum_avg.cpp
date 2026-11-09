#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string input_1, input_2;
    cout << "a: "; cin >> input_1;
    cout << "b: "; cin >> input_2;
    
    replace(input_1.begin(), input_1.end(), ',', '.');
    replace(input_2.begin(), input_2.end(), ',', '.');
    
    double a = stod(input_1);
    double b = stod(input_2);

    double sum = a + b;
    double avg = sum / 2.0;
    cout << fixed << setprecision(2) << "sum: " << sum << " avg: " << avg << endl;
    return 0;
}