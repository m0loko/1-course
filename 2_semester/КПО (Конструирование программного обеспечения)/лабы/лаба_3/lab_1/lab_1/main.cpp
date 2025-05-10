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
    cout << "��� " << year << (isLeapYear(year) ? " �������� " : " �� �������� ") << "����������." << endl;
    cout << "���������� ����� ��������� ��� � ����: " << dayOfYear(day, month, year) << endl;

    int birthdayDay, birthdayMonth;
    getValidBirthday(birthdayDay, birthdayMonth, year);

    int targetYear = year;
    if (birthdayDay == 29 && birthdayMonth == 2 && !isLeapYear(year)) {
        targetYear = nextLeapYear(year);
    }

    cout << "���� �� ���������� ��� ��������: " << daysUntilBirthday(day, month, year, birthdayDay, birthdayMonth) << endl;
    


    cout << "-----------------------------------------" << "\n\t\t������� 1" << endl;
    int porDay;
    cout << "������� ���������� ����� ��� ����: ";
    cin >> porDay;

    if (porDay < 1 || porDay >(isLeapYear(year) ? 366 : 365)) {
        cout << "! ������: ������������ ���������� ����� ���. !" << endl;
        return 1;
    }
    int eventDay, eventMonth;
    dateFromDay(porDay, year, eventDay, eventMonth);
    cout << "����: " << eventDay << " ";
    printMonth(eventMonth); 
    cout << " " << year << endl;
    printHoliday(eventDay, eventMonth);

    cout << "-----------------------------------------" << "\n\t\t��� �������:" << endl;
    cout << "-----------------------------------------" << "\n\t\t ����� 1" << endl;
    int d1, m1, y1, d2, m2, y2;
    while (true) {
        cout << "������� ������ ���� ";
        cout << "\n����: "; cin >> d1;
        cout << "\n�����: "; cin >> m1;
        cout << "\n���: "; cin >> y1;
        if (dayOfYear(d1, m1, y1) != -1) break;
        cout << "! ������������ ���� !"<<endl;
    }
    while (true)
    {
        cout << "������� ������ ���� (����, �����, ���): ";
        cout << "\n����: "; cin >> d2;
        cout << "\n�����: "; cin >> m2;
        cout << "\n���: "; cin >> y2;
        if (dayOfYear(d2, m2, y2) != -1) break;
        cout << "! ������������ ���� !" << endl;
    }
    
    int difference = daysBetweenDates(d1, m1, y1, d2, m2, y2);
    cout << "������� ����� ������: " << difference << " ����" << endl;


    cout << "-----------------------------------------" << "\n\t\t ����� 2" << endl;

    int startDay, startMonth, startYear, endDay, endMonth, endYear;
    while (true)
    {
        cout << "������� ������ ���� ";
        cout << "\n����: "; cin >> startDay;
        cout << "\n�����: "; cin >> startMonth;
        cout << "\n���: "; cin >> startYear;
        if (dayOfYear(startDay, startMonth, startYear) != -1) break;
        cout << "! ������������ ���� !" << endl;
    }
    while (true)
    {
        cout << "������� ������ ���� ";
        cout << "\n����: "; cin >> endDay;
        cout << "\n�����: "; cin >> endMonth;
        cout << "\n���: "; cin >> endYear;
        if (dayOfYear(endDay, endMonth, endYear) != -1) break;
        cout << "! ������������ ���� !" << endl;
    }
    int difference2 = hoursBetweenDates(startDay, startMonth, startYear, endDay, endMonth, endYear);
    cout << "������� ����� ������: " << difference2 << " �����" << endl;
    return 0;
}