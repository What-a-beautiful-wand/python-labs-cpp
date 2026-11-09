#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    int total_minutes;
    cout << "Минуты: "; cin >> total_minutes;

    if (total_minutes < 0 || total_minutes > 1440) {
        throw invalid_argument("Минуты должны быть в диапазоне от 0 до 1440");
    }

    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;

    cout << hours << ":" << minutes << endl;
    return 0;
}