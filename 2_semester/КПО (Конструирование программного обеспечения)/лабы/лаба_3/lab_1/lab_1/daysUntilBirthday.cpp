#include "date.h"
#include"input.h"
#include<iostream>
using namespace std;
int nextLeapYear(int year) {
    do { year++; } while (!isLeapYear(year));
    return year;
}
int daysUntilBirthday(int day, int month, int year, int bDay, int bMonth) {
    if (bDay == 29 && bMonth == 2) {
        if (!isLeapYear(year)) {
            int nextLeap = nextLeapYear(year);
            int daysThisYear = (isLeapYear(year) ? 366 : 365) - dayOfYear(day, month, year);
            int daysBetween = 0;
            for (int y = year + 1; y < nextLeap; y++) {
                daysBetween += isLeapYear(y) ? 366 : 365;
            }

            return daysThisYear + daysBetween + dayOfYear(29, 2, nextLeap);
        }
        else {
            int currentDay = dayOfYear(day, month, year);
            int birthdayDay = dayOfYear(29, 2, year);

            if (currentDay <= birthdayDay) {
                return birthdayDay - currentDay;
            }
            else {
                int nextLeap = nextLeapYear(year + 1);
                return (366 - currentDay) + (nextLeap - year - 1) * 365 + 60; 
            }
        }
    }
    int currentDay = dayOfYear(day, month, year);
    int birthdayDay = dayOfYear(bDay, bMonth, year);

    if (currentDay == -1 || birthdayDay == -1) return -1;

    return (birthdayDay >= currentDay)
        ? birthdayDay - currentDay
        : (isLeapYear(year + 1) ? 366 : 365) - currentDay + birthdayDay;
}