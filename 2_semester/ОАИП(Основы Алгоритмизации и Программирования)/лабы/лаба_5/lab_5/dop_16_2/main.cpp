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
    cout << "Фамилия: ";
    cin.getline(student.surname, 50);
    cout << "Имя: ";
    cin.getline(student.name, 50);
    cout << "Отчество: ";
    cin.getline(student.lastname, 50);
    cout << "Дата поступления (дд мм гггг): ";
    cin >> student.pDate.day >> student.pDate.month >> student.pDate.year;
    cin.ignore();
    cout << "Специальность: ";
    cin.getline(student.specialty, 50);
    cout << "Группа: ";
    cin.getline(student.group, 10);
    cout << "Факультет: ";
    cin.getline(student.faculty, 50);
    cout << "Средний балл: ";
    cin >> student.srBall;
    students.push_back(student);
    cout << "Студент добавлен!\n";
}
void outputStudents() {
    if (students.empty()) {
        cout << "Список студентов пуст.\n";
        return;
    }
    for (size_t i = 0; i < students.size(); i++) {
        cout << "\nСтудент #" << i + 1 << ":\n"
            << "Фамилия: " << students[i].surname << endl
            << "Имя: " << students[i].name << endl
            << "Отчество: " << students[i].lastname << endl
            << "Дата поступления: "
            << students[i].pDate.day << "."
            << students[i].pDate.month << "."
            << students[i].pDate.year << endl
            << "Специальность: " << students[i].specialty << endl
            << "Группа: " << students[i].group << endl
            << "Факультет: " << students[i].faculty << endl
            << "Средний балл: " << students[i].srBall << endl;
    }
}
void saveToFile() {
    ofstream file("students.txt");
    if (!file) {
        cout << "Ошибка открытия файла для записи!\n";
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
    cout << "Данные сохранены\n";
}
void loadFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cout << "Ошибка открытия файла\n";
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
    cout << "Загружено записей: " << students.size() << "\n";
}
void searchBySr() {
    float minGrade;
    cout << "Введите минимальный средний балл: ";
    cin >> minGrade;
    bool found = false;
    for (const auto& student : students) {
        if (student.srBall >= minGrade) {
            cout << "\nФамилия: " << student.surname << endl
                << "Имя: " << student.name << endl
                << "Отчество: " << student.lastname << endl
                << "Дата поступления: "
                << student.pDate.day << "."
                << student.pDate.month << "."
                << student.pDate.year << endl
                << "Специальность: " << student.specialty << endl
                << "Группа: " << student.group << endl
                << "Факультет: " << student.faculty << endl
                << "Средний балл: " << student.srBall << endl;
            found = true;
        }
    }
    if (!found) cout << "Студенты с таким баллом не найдены\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
            cout<<"\n\t\tМеню:"
            <<"\n1. Ввод данных\n"
            << "2. Вывод всех данных\n"
            << "3. Сохранить в файл\n"
            << "4. Загрузить из файла\n"
            << "5. Поиск по среднему баллу\n"
            << "6. Выход\n"
            << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1: inputStudent(); break;
        case 2: outputStudents(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: searchBySr(); break;
        case 6: cout << "Выход\n"; break;
        default: cout << "Ошибка! Введите номер от 1 до 6\n";
        }
    } while (choice != 6);
    return 0;
}
