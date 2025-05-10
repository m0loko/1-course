#include <iostream>
#include <string>
#include "date.h"
#include "input.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    int day, month, year;
    getValidDate(day, month, year);

    cout << "Год " << year << (isLeapYear(year) ? " является " : " не является ") << "високосным." << endl;
    cout << "Порядковый номер введённого дня в году: " << dayOfYear(day, month, year) << endl;

    int birthdayDay, birthdayMonth;
    getValidBirthday(birthdayDay, birthdayMonth, year);

    int targetYear = year;
    if (birthdayDay == 29 && birthdayMonth == 2 && !isLeapYear(year)) {
        targetYear = nextLeapYear(year);
    }

    cout << "Дней до ближайшего дня рождения: " << daysUntilBirthday(day, month, year, birthdayDay, birthdayMonth) << endl;
    return 0;
}