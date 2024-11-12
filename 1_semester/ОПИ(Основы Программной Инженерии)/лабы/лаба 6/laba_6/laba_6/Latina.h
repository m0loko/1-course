#include<iostream>
#include<string>
using namespace std;
void getlatina()
{
    string input;
    cout << "<------------------------------------------------------------------->" << endl;
    cout << "Введите символ или строку символов латинского алфавита: ";
    getline(cin, input);

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        if (static_cast<int>(c) >= 65 && (static_cast<int>(c) <= 90 || static_cast<int>(c) >= 97) && static_cast<int>(c) <= 122) {
            int toupperLet = static_cast<int>(toupper(c));
            int tolowerLet = static_cast<int>(tolower(c));
            int difference = abs(toupperLet - tolowerLet);
            cout << "Код прописной буквы '" << (char)toupper(c) << "' (ASCII: " << toupperLet << ") " << "и код строчной буквы '" << (char)tolower(c) << "' (ASCII: " << tolowerLet << ")." << endl;
            cout << "Разница между кодами: " << difference << endl;
        }
        else {
            cout << "Символ '" << c << "' не является латинской буквой." << endl;
        }
    }
}