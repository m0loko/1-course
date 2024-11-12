#include<iostream>
#include<string>
using namespace std;
void getnumber()
{
    string input;
    cout << "<------------------------------------------------------------------->" << endl;
    cout << "Введите цифру или строку цифр: ";
    getline(cin, input);
    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        if (static_cast<int>(c) >= 48 && static_cast<int>(c) <= 57 ) {
            cout << "Код цифры " << c << " = " << static_cast<int>(c) << endl;
        }
        else {
            cout << "Символ '" << c << "' не является цифрой." << endl;
        }
    }
}