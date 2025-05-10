#include "input.h"
#include "date.h"
#include <map>
#include <iostream>
using namespace std;
void printMonth(int &month) {
     map<int, string> nameMonth = {
        {1, "������"},
        {2, "�������"},
        {3, "����"},
        {4, "������"},
        {5, "���"},
        {6, "����"},
        {7, "����"},
        {8, "������"},
        {9, "��������"},
        {10, "�������"}, 
        {11, "������"}, 
        {12, "�������"}
    };
	cout << "�����: " << nameMonth[month] << " (�����: " << month << ") ";
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
        {{12, 9}, "���� ������������"},
        {{2, 9}, "���� �������� ���������"},
        {{12, 4}, "���� ������������"},
        {{25, 8}, "���� �������� Linux"},
        {{8, 3}, "������������� ������� ����"},
        {{22, 4}, "���� �����"},
        {{9, 5}, "���� ������"},    
        {{1, 6}, "������������� ���� ������ �����"},
        {{23, 2}, "���� ��������� ���������"},
        {{7, 8}, "���� �������� ������ ��������"}
    };

    if (holidays.find({ day, month }) != holidays.end()) {
        cout << "��������: " << holidays[{day, month}] << endl;
    }
    else {
        cout << endl;
    }
}



//��� �������
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
