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
        return "����������";
    case PHYSICS:
        return "������";
    case CHEMISTRY:
        return "�����";
    case HISTORY:
        return "�������";
    case OPI:
        return"���";
    default:
        return "?????????";
    }
}
void inputTeacher(vector<Teacher>& teachers) {
    Teacher t;
    int tempExam, tempDay, tempMonth, tempYear;
    cout << "������� �������������: ";
    cin >> t.surname;
    cout << "������� (0-����������, 1-������, 2-�����, 3-�������, 4-���): ";
    cin >> tempExam;
    t.exam = static_cast<ExamName>(tempExam);
    cout << "���� �������� (���� ����� ���): ";
    cin >> tempDay >> tempMonth >> tempYear;
    t.date.day = tempDay;
    t.date.month = tempMonth;
    t.date.year = tempYear;
    teachers.push_back(t);
}
void outputTeachers(vector<Teacher>& teachers) {
    if (teachers.empty()) {
        cout << "������ ����\n";
        return;
    }
    for (auto t : teachers) {
        cout << "\n�������������: " << t.surname
            << "\n�������: " << getExamName(t.exam)
            << "\n����: " << t.date.day << "."
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
            cout << "�������:\n"
                << "�������������: " << t.surname
                << "\n�������: " << getExamName(t.exam)
                << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "������� �� �������\n";
}
void deleteTeacher(vector<Teacher>& teachers, string& surname) {
    for (auto it = teachers.begin(); it != teachers.end(); it++) {
        if (it->surname == surname) {
            teachers.erase(it);
            cout << "������ �������\n";
            return;
        }
    }
    cout << "������������� �� ������\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Teacher> teachers;
    int choice;
    do {
        cout << "\n\t\t����:\n"
            << "1. �������� �������\n"
            << "2. �������� ���� ��������\n"
            << "3. ����� �� ����\n"
            << "4. ������� �������\n"
            << "5. �����\n"
            << "��������: ";
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
            cout << "������� ���� (� � �): ";
            cin >> d >> m >> y;
            searchDate(teachers, d, m, y);
            break;
        }
        case 4: {
            string s;
            cout << "������� �������: ";
            cin >> s;
            deleteTeacher(teachers, s);
            break;
        }
        case 5:
            return 0;
        default:
            cout << "�������� �����\n";
        }
    } while (true);
    return 0;
}