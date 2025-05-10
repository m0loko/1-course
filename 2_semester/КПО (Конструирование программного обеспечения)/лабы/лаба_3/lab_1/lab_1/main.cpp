#include <iostream>
#include <string>
#include "date.h"
#include "input.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    int day, month, year;
    getValidDate(day, month, year);
    printMonth(month);
    cout << "Год " << year << (isLeapYear(year) ? " является " : " не является ") << "високосным." << endl;
    cout << "Порядковый номер введённого дня в году: " << dayOfYear(day, month, year) << endl;

    int birthdayDay, birthdayMonth;
    getValidBirthday(birthdayDay, birthdayMonth, year);

    int targetYear = year;
    if (birthdayDay == 29 && birthdayMonth == 2 && !isLeapYear(year)) {
        targetYear = nextLeapYear(year);
    }

    cout << "Дней до ближайшего дня рождения: " << daysUntilBirthday(day, month, year, birthdayDay, birthdayMonth) << endl;
    


    cout << "-----------------------------------------" << "\n\t\tЗадание 1" << endl;
    int porDay;
    cout << "Введите порядковый номер дня года: ";
    cin >> porDay;

    if (porDay < 1 || porDay >(isLeapYear(year) ? 366 : 365)) {
        cout << "! Ошибка: некорректный порядковый номер дня. !" << endl;
        return 1;
    }
    int eventDay, eventMonth;
    dateFromDay(porDay, year, eventDay, eventMonth);
    cout << "Дата: " << eventDay << " ";
    printMonth(eventMonth); 
    cout << " " << year << endl;
    printHoliday(eventDay, eventMonth);

    cout << "-----------------------------------------" << "\n\t\tДоп задания:" << endl;
    cout << "-----------------------------------------" << "\n\t\t Часть 1" << endl;
    int d1, m1, y1, d2, m2, y2;
    while (true) {
        cout << "Введите первую дату ";
        cout << "\nДень: "; cin >> d1;
        cout << "\nМесяц: "; cin >> m1;
        cout << "\nГод: "; cin >> y1;
        if (dayOfYear(d1, m1, y1) != -1) break;
        cout << "! Неккоректная дата !"<<endl;
    }
    while (true)
    {
        cout << "Введите вторую дату (день, месяц, год): ";
        cout << "\nДень: "; cin >> d2;
        cout << "\nМесяц: "; cin >> m2;
        cout << "\nГод: "; cin >> y2;
        if (dayOfYear(d2, m2, y2) != -1) break;
        cout << "! Неккоректная дата !" << endl;
    }
    
    int difference = daysBetweenDates(d1, m1, y1, d2, m2, y2);
    cout << "Разница между датами: " << difference << " дней" << endl;


    cout << "-----------------------------------------" << "\n\t\t Часть 2" << endl;

    int startDay, startMonth, startYear, endDay, endMonth, endYear;
    while (true)
    {
        cout << "Введите первую дату ";
        cout << "\nДень: "; cin >> startDay;
        cout << "\nМесяц: "; cin >> startMonth;
        cout << "\nГод: "; cin >> startYear;
        if (dayOfYear(startDay, startMonth, startYear) != -1) break;
        cout << "! Неккоректная дата !" << endl;
    }
    while (true)
    {
        cout << "Введите вторую дату ";
        cout << "\nДень: "; cin >> endDay;
        cout << "\nМесяц: "; cin >> endMonth;
        cout << "\nГод: "; cin >> endYear;
        if (dayOfYear(endDay, endMonth, endYear) != -1) break;
        cout << "! Неккоректная дата !" << endl;
    }
    int difference2 = hoursBetweenDates(startDay, startMonth, startYear, endDay, endMonth, endYear);
    cout << "Разница между датами: " << difference2 << " часов" << endl;
    return 0;
}