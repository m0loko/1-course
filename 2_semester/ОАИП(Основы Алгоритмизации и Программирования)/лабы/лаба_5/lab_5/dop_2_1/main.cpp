#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
enum Emenu
{
    INPUT_CITIZEN = 1, OUTPUT_CITIZEN, DELETE_CITIZEN, SEARCH_CITIZEN, SEARCHBYYEAR, EXIT_PROGRAM
};
enum Gender { Male = '�', Female = '�' };
struct Gorozanin
{
    string name;
    string surname;
    string lastname;
    unsigned day : 5;      
    unsigned month : 4;    
    unsigned year : 11;   
    string address;
    string phone;
    Gender gender;
};
void output(const Gorozanin& citizen) {
    cout << "�������: " << citizen.surname << "\n"
        << "���: " << citizen.name << "\n"
        << "��������: " << citizen.lastname << "\n"
        << "���� ��������: " << citizen.day << "." << citizen.month << "." << citizen.year << "\n"
        << "�����: " << citizen.address << "\n"
        << "�������: " << citizen.phone << "\n"
        << "���: " << (citizen.gender == Male ? "�������" : "�������") << endl;
}
void inputGorozanin(vector<Gorozanin>& gorozanin) {
    Gorozanin citizen;
    unsigned short temp1, temp2, temp3;
    cout << "������� ���������� � ����������:\n";
    cout << "�������: "; cin >> citizen.surname;
    cout << "���: "; cin >> citizen.name;
    cout << "��������: "; cin >> citizen.lastname;
    cout << "������� ���������� ��� ���� ��������:\n";
    cout << "����: "; cin >> temp1;
    citizen.day = temp1;
    cout << "�����: "; cin >> temp2;
    citizen.month = temp2;
    cout << "���: "; cin >> temp3;
    citizen.year = temp3;
    cout << "������� �����: "; cin >> citizen.address;
    cout << "������� �������: "; cin >> citizen.phone;
    char gender;
    cout << "��� (�/�): "; cin >> gender;
    citizen.gender = (gender == '�' || gender == '�') ? Male : Female;
    gorozanin.push_back(citizen);
}
void outputGorozanins(vector<Gorozanin>& gorozanin) {
    if (gorozanin.empty()) {
        cout << "������ ������� ����.\n";
        return;
    }
    for (auto& citizen : gorozanin) {
        output(citizen);
        cout << endl;
    }
}
void deleteGorozanin(vector<Gorozanin>& gorozanin,string& surname) {
    for (auto it = gorozanin.begin(); it != gorozanin.end(); ++it) {
        if (it->surname == surname) {
            gorozanin.erase(it);
            cout << "������ � �������� " << surname << " �������\n";
            return;
        }
    }
    cout << "������ � �������� " << surname << " �� �������.\n";
}
void searchGorozanin(const vector<Gorozanin>& gorozanin, const string& surname) {
    for (const auto& citizen : gorozanin) {
        if (citizen.surname == surname) {
            cout << "�������:\n";
            output(citizen);
            return;
        }
    }
    cout << "������ � �������� " << surname << " �� �������.\n";
}
void searchGorozaninsByYear(vector<Gorozanin>& gorozanin, unsigned year) {
    bool found = false;
    for (auto& citizen : gorozanin) {
        if (citizen.year == year) {
            if (!found) {
                cout << "������� ������� � ����� �������� " << year << ":\n";
                found = true;
            }
            output(citizen);
            cout << endl;
        }
    }
    if (!found) {
        cout << "������ � ����� �������� " << year << " �� �������.\n";
    }
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Gorozanin> gorozanin;
    int choiceInt;
    Emenu choice;
    bool pr = true;
    string surname;
    do {
        cout << "\n\t\t����:\n";
        cout << "1. ���� � ���������� ���������� � ����������\n";
        cout << "2. ����� �� ����� ���������� � ���������\n";
        cout << "3. ������� ���������� � ����������\n";
        cout << "4. ����� �� �������\n";
        cout << "5. ������� �� ���� ��������\n";
        cout << "6. �����\n";
        cout << "��� �����: ";
        cin >> choiceInt;
        choice = static_cast<Emenu>(choiceInt);
        switch (choice) {
        case INPUT_CITIZEN: {
            inputGorozanin(gorozanin);
            break;
        }
        case OUTPUT_CITIZEN: {
            outputGorozanins(gorozanin);
            break;
        }
        case DELETE_CITIZEN: {
            cout << "������� ������� ��� ��������: ";
            cin >> surname;
            deleteGorozanin(gorozanin, surname);
            break;
        }
        case SEARCH_CITIZEN: {
            cout << "������� ������� ��� ������: ";
            cin >> surname;
            searchGorozanin(gorozanin, surname);
            break;
        }
        case SEARCHBYYEAR: {
            unsigned year;
            cout << "������� ��� �������� ��� �������: ";
            cin >> year;
            searchGorozaninsByYear(gorozanin, year);
            break;
        }
        case EXIT_PROGRAM: {
            pr = false;
            break;
        }
        default: {
            cout << "�������� �����, ���������� �����\n";
            break;
        }
        }
    } while (pr);
    return 0;
}
