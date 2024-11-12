#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int variant;
    cout << "Выберете вариант использования программы:" << endl
        << "1) Определение разницы значений кодов в ASCII буквы в прописном и строчном написании, если введен символ латинского алфавита"
        << endl << "2) Определение разницы значений кодов в Windows-1251 буквы в прописном и строчном написании, если введен символ русского алфавита"
        << endl << "3) Вывод в консоль кода символа, соответствующего введенной цифре"
        << endl << "4) Выход из программы" << "\n\n"
        << "<------------------------------------------------------------------->" << endl;
    cin >> variant;

    switch (variant) {
    case 1: {
        char c;
        cout << "<------------------------------------------------------------------->" << endl;
        cout << "Введите символ латинского алфавита:";
        cin >> c;
        while (static_cast<int>(c) < 65 || (static_cast<int>(c) > 90 && static_cast<int>(c) < 97) || static_cast<int>(c) > 122) {
            cout << "Введите символ латинского алфавита ! : ";
            cin >> c;
        }
        int toupperLet = static_cast<int>(toupper(c));
        int tolowerLet = static_cast<int>(tolower(c));
        int difference = abs(toupperLet - tolowerLet);
        cout << "Код прописной буквы '" << (char)toupper(c) << "' (ASCII: " << toupperLet << ") "
            << "и код строчной буквы '" << (char)tolower(c) << "' (ASCII: " << tolowerLet << ")." << endl;
        cout << "Разница между кодами: " << difference << endl;
        break;
    }

    case 2: {
        unsigned char q;
        cout << "<------------------------------------------------------------------->" << endl;
        cout << "Введите символ русского алфавита ! : ";
        cin >> q;
        while ((static_cast<int>(q) < 192 || static_cast<int>(q) > 255) && static_cast<int>(q) != 184 && static_cast<int>(q) != 168) {
            cout << "Введите символ русского алфавита! : ";
            cin >> q;
        }

        int q_code = static_cast<int>(q);
        int toupperLet_1, tolowerLet_1;

        if (q_code == 184) {  // 'ё'
            toupperLet_1 = 168;
            tolowerLet_1 = 184;
        }
        else if (q_code == 168) {  // 'Ё'
            toupperLet_1 = 168;
            tolowerLet_1 = 184;
        }
        else if (q_code > 223) {  // Lowercase letters
            toupperLet_1 = q_code - 32;
            tolowerLet_1 = q_code;
        }
        else if (q_code > 191 && q_code < 224) {  // Uppercase letters
            toupperLet_1 = q_code;
            tolowerLet_1 = q_code + 32;
        }

        int difference_1 = abs(toupperLet_1 - tolowerLet_1);
        cout << "Код прописной буквы '" << (char)toupperLet_1 << "' (ASCII: " << toupperLet_1 << ") и код строчной буквы '"
            << (char)tolowerLet_1 << "' (ASCII: " << tolowerLet_1 << ")." << endl;
        cout << "Разница между кодами: " << difference_1 << endl;
        break;
    }

    case 3: {
        char c;
        cout << "<------------------------------------------------------------------->" << endl;
        cout << "Введите цифру" << endl;
        cin >> c;
        while (static_cast<int>(c) < 48 || static_cast<int>(c) > 57) {
            cout << "Введите цифру ! : ";
            cin >> c;
        }
        cout << "Код цифры " << c << " = " << static_cast<int>(c) << endl;
        break;
    }

    case 4: {
        cout << "<------------------------------------------------------------------->" << endl;
        cout << "Выходим из программы";
        break;
    }
    }

    return 0;
}
