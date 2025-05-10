#include<iostream>
#include "input.h"
#include "date.h"
#include <string>
using namespace std;
void getValidDate(int& day, int& month, int& year) {
    using namespace std;
    string input;

    while (true) {
        cout << "Введите дату в формате ДДММГГГГ: ";
        getline(cin, input);

        if (input.size() == 8 && input.find_first_not_of("0123456789") == string::npos) {
            day = stoi(input.substr(0, 2));
            month = stoi(input.substr(2, 2));
            year = stoi(input.substr(4, 4));

            if (dayOfYear(day, month, year) != -1) break;
        }
        cout << "! Ошибка. Некорректная дата" << endl;
    }
}