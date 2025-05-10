#include "date.h"
int dayOfYear(int day, int month, int year) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) daysInMonth[1] = 29;
    if (month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) {
        return -1;
    }

    int total = 0;
    for (int i = 0; i < month - 1; i++) total += daysInMonth[i];
    return total + day;
}
