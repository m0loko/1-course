#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <Windows.h>
using namespace std;
struct Date {
    union {
        struct {
            unsigned short day;
            unsigned short month;
            unsigned short year;
        };
        char dateStr[11];
    };
};
struct Student {
    char surname[50];
    char name[50];
    char lastname[50];
    Date pDate;
    char specialty[50];
    char group[10];
    char faculty[50];
    float srBall;
};
vector<Student> students;
void inputStudent() {
    Student student;
    cin.ignore();
    cout << "�������: ";
    cin.getline(student.surname, 50);
    cout << "���: ";
    cin.getline(student.name, 50);
    cout << "��������: ";
    cin.getline(student.lastname, 50);
    cout << "���� ����������� (�� �� ����): ";
    cin >> student.pDate.day >> student.pDate.month >> student.pDate.year;
    cin.ignore();
    cout << "�������������: ";
    cin.getline(student.specialty, 50);
    cout << "������: ";
    cin.getline(student.group, 10);
    cout << "���������: ";
    cin.getline(student.faculty, 50);
    cout << "������� ����: ";
    cin >> student.srBall;
    students.push_back(student);
    cout << "������� ��������!\n";
}
void outputStudents() {
    if (students.empty()) {
        cout << "������ ��������� ����.\n";
        return;
    }
    for (size_t i = 0; i < students.size(); i++) {
        cout << "\n������� #" << i + 1 << ":\n"
            << "�������: " << students[i].surname << endl
            << "���: " << students[i].name << endl
            << "��������: " << students[i].lastname << endl
            << "���� �����������: "
            << students[i].pDate.day << "."
            << students[i].pDate.month << "."
            << students[i].pDate.year << endl
            << "�������������: " << students[i].specialty << endl
            << "������: " << students[i].group << endl
            << "���������: " << students[i].faculty << endl
            << "������� ����: " << students[i].srBall << endl;
    }
}
void saveToFile() {
    ofstream file("students.txt");
    if (!file) {
        cout << "������ �������� ����� ��� ������!\n";
        return;
    }
    for (const auto& student : students) {
        file << student.surname << endl
            << student.name << endl
            << student.lastname << endl
            << student.pDate.day << " "
            << student.pDate.month << " "
            << student.pDate.year << endl
            << student.specialty << endl
            << student.group << endl
            << student.faculty << endl
            << student.srBall << endl;
    }
    cout << "������ ���������\n";
}
void loadFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cout << "������ �������� �����\n";
        return;
    }
    students.clear();
    Student student;
    while (file.getline(student.surname, 50) &&
        file.getline(student.name, 50) &&
        file.getline(student.lastname, 50) &&
        file >> student.pDate.day >> student.pDate.month >> student.pDate.year &&
        file.ignore() &&
        file.getline(student.specialty, 50) &&
        file.getline(student.group, 10) &&
        file.getline(student.faculty, 50) &&
        file >> student.srBall &&
        file.ignore()) {
        students.push_back(student);
    }
    cout << "��������� �������: " << students.size() << "\n";
}
void searchBySr() {
    float minGrade;
    cout << "������� ����������� ������� ����: ";
    cin >> minGrade;
    bool found = false;
    for (const auto& student : students) {
        if (student.srBall >= minGrade) {
            cout << "\n�������: " << student.surname << endl
                << "���: " << student.name << endl
                << "��������: " << student.lastname << endl
                << "���� �����������: "
                << student.pDate.day << "."
                << student.pDate.month << "."
                << student.pDate.year << endl
                << "�������������: " << student.specialty << endl
                << "������: " << student.group << endl
                << "���������: " << student.faculty << endl
                << "������� ����: " << student.srBall << endl;
            found = true;
        }
    }
    if (!found) cout << "�������� � ����� ������ �� �������\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
            cout<<"\n\t\t����:"
            <<"\n1. ���� ������\n"
            << "2. ����� ���� ������\n"
            << "3. ��������� � ����\n"
            << "4. ��������� �� �����\n"
            << "5. ����� �� �������� �����\n"
            << "6. �����\n"
            << "�������� ��������: ";
        cin >> choice;
        switch (choice) {
        case 1: inputStudent(); break;
        case 2: outputStudents(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: searchBySr(); break;
        case 6: cout << "�����\n"; break;
        default: cout << "������! ������� ����� �� 1 �� 6\n";
        }
    } while (choice != 6);
    return 0;
}
