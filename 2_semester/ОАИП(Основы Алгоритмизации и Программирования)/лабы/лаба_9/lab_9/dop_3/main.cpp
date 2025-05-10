#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

const int SUBJECTS_COUNT = 5;

struct Student {
    string lastName;
    string firstName;
    string middleName;
    int birthYear;
    int course;
    string group;
    double grades[SUBJECTS_COUNT];
    Student* prev;
    Student* next;

    double averageGrade() const {
        double sum = 0.0;
        for (int i = 0; i < SUBJECTS_COUNT; i++) {
            sum += grades[i];
        }
        return sum / SUBJECTS_COUNT;
    }
};

void clearBuffer() {
    cin.clear();
    cin.ignore();
}

Student inputStudent() {
    Student s;

    cout << "\n������� ������ ��������:\n";
    cout << "�������: ";
    getline(cin, s.lastName);
    cout << "���: ";
    getline(cin, s.firstName);
    cout << "��������: ";
    getline(cin, s.middleName);

    cout << "��� ��������: ";
    while (!(cin >> s.birthYear) || s.birthYear < 1000 || s.birthYear > 2025) {
        cout << "������, ������� ���������� ��� �������� (1000-2025): ";
        clearBuffer();
    }
    clearBuffer();

    cout << "���� (1-4): ";
    while (!(cin >> s.course) || s.course < 1 || s.course > 4) {
        cout << "������, ������� ���� (1-4): ";
        clearBuffer();
    }
    clearBuffer();

    cout << "������: ";
    getline(cin, s.group);

    cout << "������ �� " << SUBJECTS_COUNT << " ���������: ";
    for (int i = 0; i < SUBJECTS_COUNT; ) {
        if (cin >> s.grades[i] && s.grades[i] >= 1 && s.grades[i] <= 10) {
            i++;
        }
        else {
            cout << "������, ������� ������ (1-10): ";
            clearBuffer();
        }
    }
    clearBuffer();

    s.prev = nullptr;
    s.next = nullptr;
    return s;
}

void addStudent(Student** head, Student** tail, Student& data) {
    Student* newStudent = new Student(data);
    if (!newStudent) {
        cerr << "������ ��������� ������" << endl;
        return;
    }

    if (*head == nullptr) {
        *head = *tail = newStudent;
        return;
    }

    Student* current = *head;
    while (current) {
        if (data.course < current->course ||
            (data.course == current->course && data.lastName < current->lastName)) {
            newStudent->prev = current->prev;
            newStudent->next = current;
            if (current->prev) {
                current->prev->next = newStudent;
            }
            else {
                *head = newStudent;
            }
            current->prev = newStudent;
            return;
        }
        current = current->next;
    }

    (*tail)->next = newStudent;
    newStudent->prev = *tail;
    *tail = newStudent;
}

void printStudents(Student* head) {
    if (!head) {
        cout << "������ ��������� ����" << endl;
        return;
    }

    cout << "\n������ ��������� (��������������� �� ����� � �������):" << endl;
    Student* current = head;
    while (current) {
        cout << current->course << " ����: "
            << current->lastName << " "
            << current->firstName << " "
            << current->middleName << " (������: " << current->group
            << ", ��� ��������: " << current->birthYear
            << ", ������� ����: " << fixed << setprecision(2) << current->averageGrade() << ")" << endl;
        current = current->next;
    }
}

void calculateGroupAverages(Student* head) {
    if (!head) {
        cout << "������ ��������� ����" << endl;
        return;
    }

    map<string, vector<double>> groupGrades;
    Student* current = head;
    while (current) {
        for (int i = 0; i < SUBJECTS_COUNT; i++) {
            groupGrades[current->group].push_back(current->grades[i]);
        }
        current = current->next;
    }

    cout << "\n������� ���� �� ��������� ��� ������ ������:" << endl;
    for (auto& group : groupGrades) {
        cout << "������ " << group.first << ": ";
        double sum = 0.0;
        for (double grade : group.second) {
            sum += grade;
        }
        cout << fixed << setprecision(2) << sum / group.second.size() << endl;
    }
}

void findOldestYoungest(Student* head) {
    if (!head) {
        cout << "������ ��������� ����" << endl;
        return;
    }

    Student* oldest = head;
    Student* youngest = head;
    Student* current = head->next;

    while (current) {
        if (current->birthYear < oldest->birthYear) {
            oldest = current;
        }
        if (current->birthYear > youngest->birthYear) {
            youngest = current;
        }
        current = current->next;
    }

    cout << "\n����� ������� �������: " << oldest->lastName << " " << oldest->firstName
        << " (��� ��������: " << oldest->birthYear << ")" << endl;
    cout << "����� ������� �������: " << youngest->lastName << " " << youngest->firstName
        << " (��� ��������: " << youngest->birthYear << ")" << endl;
}

void findTopStudents(Student* head) {
    if (!head) {
        cout << "������ ��������� ����" << endl;
        return;
    }

    map<string, Student*> groupTopStudents;
    Student* current = head;

    while (current) {
        if (groupTopStudents.find(current->group) == groupTopStudents.end() ||
            current->averageGrade() > groupTopStudents[current->group]->averageGrade()) {
            groupTopStudents[current->group] = current;
        }
        current = current->next;
    }

    cout << "\n������ �������� �� �������:" << endl;
    for (auto& group : groupTopStudents) {
        cout << "������ " << group.first << ": "
            << group.second->lastName << " " << group.second->firstName
            << " (������� ����: " << fixed << setprecision(2) << group.second->averageGrade() << ")" << endl;
    }
}

void deleteList(Student** head) {
    Student* current = *head;
    while (current) {
        Student* temp = current;
        current = current->next;
        delete temp;
    }
    *head = nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Student* head = nullptr;
    Student* tail = nullptr;

    int choice;
    do {
        cout << "\n����:\n1. �������� ��������\n2. �������� ���������\n3. ������� ���� �����\n4. �������/������� �������\n5. ������ ��������\n6. �����\n�������� ��������: ";
        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "������, ������� ����� �� 1 �� 6: ";
            clearBuffer();
        }
        clearBuffer();

        switch (choice) {
        case 1: {
            Student s = inputStudent();
            addStudent(&head, &tail, s);
            break;
        }
        case 2:
            printStudents(head);
            break;
        case 3:
            calculateGroupAverages(head);
            break;
        case 4:
            findOldestYoungest(head);
            break;
        case 5:
            findTopStudents(head);
            break;
        case 6:
            cout << "�����" << endl;
            break;
        }
    } while (choice != 6);

    deleteList(&head);
    return 0;
}