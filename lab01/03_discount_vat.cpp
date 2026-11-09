#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string price_input, discount_input, vat_input;
    cout << "Price: "; cin >> price_input;
    cout << "Discount (%): "; cin >> discount_input;
    cout << "VAT (%): "; cin >> vat_input;

    replace(price_input.begin(), price_input.end(), ',', '.');
    replace(discount_input.begin(), discount_input.end(), ',', '.');
    replace(vat_input.begin(), vat_input.end(), ',', '.');

    double price = stod(price_input);
    double discount = stod(discount_input);
    double vat = stod(vat_input);

    double base = price * (1 - discount / 100.0);
    double vat_amount = base * (vat / 100.0);
    double total = base + vat_amount;

    cout << fixed << setprecision(2);

    cout << "База после скидки:" << string(1, ' ') << base << " ₽\n";
    cout << "НДС:" << string(15, ' ') << vat_amount << " ₽\n";
    cout << "Итого к оплате:" << string(4, ' ') << total << " ₽\n";
    return 0;
}