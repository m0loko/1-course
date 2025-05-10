#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
enum ExamName {
    MATH,
    PHYSICS,
    CHEMISTRY,
    HISTORY,
    OPI
};
struct ExamDate {
    unsigned day : 5;     
    unsigned month : 4;   
    unsigned year : 11; 
};
struct Teacher {
    string surname;
    ExamName exam;
    ExamDate date;
};
string getExamName(ExamName exam) {
    switch (exam) {
    case MATH:
        return "Математика";
    case PHYSICS:
        return "Физика";
    case CHEMISTRY:
        return "Химия";
    case HISTORY:
        return "История";
    case OPI:
        return"ОПИ";
    default:
        return "?????????";
    }
}
void inputTeacher(vector<Teacher>& teachers) {
    Teacher t;
    int tempExam, tempDay, tempMonth, tempYear;
    cout << "Фамилия преподавателя: ";
    cin >> t.surname;
    cout << "Экзамен (0-Математика, 1-Физика, 2-Химия, 3-История, 4-ОПИ): ";
    cin >> tempExam;
    t.exam = static_cast<ExamName>(tempExam);
    cout << "Дата экзамена (день месяц год): ";
    cin >> tempDay >> tempMonth >> tempYear;
    t.date.day = tempDay;
    t.date.month = tempMonth;
    t.date.year = tempYear;
    teachers.push_back(t);
}
void outputTeachers(vector<Teacher>& teachers) {
    if (teachers.empty()) {
        cout << "Список пуст\n";
        return;
    }
    for (auto t : teachers) {
        cout << "\nПреподаватель: " << t.surname
            << "\nЭкзамен: " << getExamName(t.exam)
            << "\nДата: " << t.date.day << "."
            << t.date.month << "." << t.date.year
            << "\n-------------------\n";
    }
}
void searchDate(vector<Teacher>& teachers,
    unsigned day, unsigned month, unsigned year) {
    bool found = false;
    for (auto t : teachers) {
        if (t.date.day == day &&
            t.date.month == month &&
            t.date.year == year) {
            cout << "Найдено:\n"
                << "Преподаватель: " << t.surname
                << "\nЭкзамен: " << getExamName(t.exam)
                << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "Записей не найдено\n";
}
void deleteTeacher(vector<Teacher>& teachers, string& surname) {
    for (auto it = teachers.begin(); it != teachers.end(); it++) {
        if (it->surname == surname) {
            teachers.erase(it);
            cout << "Запись удалена\n";
            return;
        }
    }
    cout << "Преподаватель не найден\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Teacher> teachers;
    int choice;
    do {
        cout << "\n\t\tМеню:\n"
            << "1. Добавить учителя\n"
            << "2. Показать всех учителей\n"
            << "3. Поиск по дате\n"
            << "4. Удалить учителя\n"
            << "5. Выход\n"
            << "Выберите: ";
        cin >> choice;
        switch (choice) {
        case 1:
            inputTeacher(teachers);
            break;
        case 2:
            outputTeachers(teachers);
            break;
        case 3: {
            unsigned d, m, y;
            cout << "Введите дату (д м г): ";
            cin >> d >> m >> y;
            searchDate(teachers, d, m, y);
            break;
        }
        case 4: {
            string s;
            cout << "Введите фамилию: ";
            cin >> s;
            deleteTeacher(teachers, s);
            break;
        }
        case 5:
            return 0;
        default:
            cout << "Неверный выбор\n";
        }
    } while (true);
    return 0;
}