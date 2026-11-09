#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int age;
    char name[60];
    cout << "Введите имя: ";
    cin.getline(name, 60);
    cout << "Введите ваш возраст: ";
    cin >> age;
    cout << "В следующем году " << name << " будет " << age + 1 << " лет." << endl;
    return 0;
}