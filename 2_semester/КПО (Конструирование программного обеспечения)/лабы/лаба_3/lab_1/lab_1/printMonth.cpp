#include "input.h"
#include "date.h"
#include <map>
#include <iostream>
using namespace std;
void printMonth(int &month) {
     map<int, string> nameMonth = {
        {1, "Январь"},
        {2, "Февраль"},
        {3, "Март"},
        {4, "Апрель"},
        {5, "Май"},
        {6, "Июнь"},
        {7, "Июль"},
        {8, "Август"},
        {9, "Сентябрь"},
        {10, "Октябрь"}, 
        {11, "Ноябрь"}, 
        {12, "Декабрь"}
    };
	cout << "Месяц: " << nameMonth[month] << " (номер: " << month << ") ";
}
void dateFromDay(int dayOfYear, int year, int& day, int& month) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) daysInMonth[1] = 29; 
    month = 1;
    while (dayOfYear > daysInMonth[month - 1]) {
        dayOfYear -= daysInMonth[month - 1];
        month++;
    }
    day = dayOfYear;
}
void printHoliday(int day, int month) {
    map<pair<int, int>, string> holidays = {
        {{12, 9}, "День программиста"},
        {{2, 9}, "День рождения интернета"},
        {{12, 4}, "День космонавтики"},
        {{25, 8}, "День рождения Linux"},
        {{8, 3}, "Международный женский день"},
        {{22, 4}, "День Земли"},
        {{9, 5}, "День Победы"},    
        {{1, 6}, "Международный день защиты детей"},
        {{23, 2}, "День защитника Отечества"},
        {{7, 8}, "День рождения Ксении Якубенко"}
    };

    if (holidays.find({ day, month }) != holidays.end()) {
        cout << "Праздник: " << holidays[{day, month}] << endl;
    }
    else {
        cout << endl;
    }
}



//доп задания
int daysBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2) {
    if (year1 > year2 || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2)) {
        swap(day1, day2);
        swap(month1, month2);
        swap(year1, year2);
    }

    if (year1 == year2) {
        return abs(dayOfYear(day2, month2, year2) - dayOfYear(day1, month1, year1));
    }

    int daysInFirstYear = (isLeapYear(year1) ? 366 : 365) - dayOfYear(day1, month1, year1);
    int daysInLastYear = dayOfYear(day2, month2, year2);

    int daysBetween = 0;
    for (int y = year1 + 1; y < year2; y++) {
        daysBetween += isLeapYear(y) ? 366 : 365;
    }

    return daysInFirstYear + daysBetween + daysInLastYear;
}



int hoursBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2) {
    return daysBetweenDates(day1, month1, year1, day2, month2, year2) * 24;
}
