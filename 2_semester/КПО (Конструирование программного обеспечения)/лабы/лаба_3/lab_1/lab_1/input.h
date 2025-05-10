#pragma once
void getValidDate(int& day, int& month, int& year);
void getValidBirthday(int& birthdayDay, int& birthdayMonth, int year);
void printMonth(int& month);
void dateFromDay(int dayOfYear, int year, int& day, int& month);
void printHoliday(int day, int month);
int daysBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2);