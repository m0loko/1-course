#include<iostream>
#include<string>
using namespace std;
void getrussian() {
    string input;
    cout << "<------------------------------------------------------------------->" << endl;
    cout << "Введите символов строку символов русского алфавита: ";
    getline(cin, input);
    for (int i = 0; i < input.length(); i++)
    {
        unsigned char q = input[i];
        int q_code = static_cast<int>(q);
        if (q_code >= 192 && q_code <= 255) {
            int toupperLet_1 = 0, tolowerLet_1 = 0;

            if (q_code > 223) {
                toupperLet_1 = q_code - 32;
                tolowerLet_1 = q_code;
            }
            else if (q_code > 191 && q_code < 224) {
                toupperLet_1 = q_code;
                tolowerLet_1 = q_code + 32;
            }

            int difference_1 = abs(toupperLet_1 - tolowerLet_1);
            cout << "Код прописной буквы '" << (char)toupperLet_1 << "' (ASCII: " << toupperLet_1 << ") и код строчной буквы '"
                << (char)tolowerLet_1 << "' (ASCII: " << tolowerLet_1 << ")." << endl;
            cout << "Разница между кодами: " << difference_1 << endl;
        }
        else {
            cout << "Символ '" << q << "' не является буквой русского алфавита." << endl;
        }
    }
}