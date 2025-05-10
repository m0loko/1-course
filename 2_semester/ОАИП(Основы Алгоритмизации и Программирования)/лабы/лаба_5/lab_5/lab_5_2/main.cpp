#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
using namespace std;
struct Date {
    union {
        struct {
            unsigned short day;
            unsigned short month;
            unsigned short year;
        };
        char dateStr[20];
    };
};
struct Book {
    char surname[50];
    char name[50];
    char lastname[50];
    Date birthDate;
    char location[100];
    char number[20];
    char locWorkStudy[100];
    char position[50];
};
vector<Book> books;
void inputBook() {
    Book book;
    cout << "������� ����������:\n";
    cout << "�������: ";
    cin.getline(book.surname, 50);
    cout << "���: ";
    cin.getline(book.name, 50);
    cout << "��������: ";
    cin.getline(book.lastname, 50);
    cout << "���� ��������: ";
    cin >> book.birthDate.day;
    cout << "�����: ";
    cin >> book.birthDate.month;
    cout << "���: ";
    cin >> book.birthDate.year;
    cin.ignore();
    cout << "�����: ";
    cin.getline(book.location, 100);
    cout << "�������: ";
    cin.getline(book.number, 20);
    cout << "����� ������/�����: ";
    cin.getline(book.locWorkStudy, 100);
    cout << "���������: ";
    cin.getline(book.position, 50);
    books.push_back(book); 
}
void outputBooks() {
    if (books.empty()) {
        cout << "������� ���\n";
        return;
    }
    for (int i = 0; i < books.size(); i++) {
        cout << "\n������ #" << i + 1 << ":\n";
        cout << "�������: " << books[i].surname << endl<< "���: " << books[i].name << endl
            << "��������: " << books[i].lastname << endl << "���� ��������: " << books[i].birthDate.day << "."
            << books[i].birthDate.month << "." << books[i].birthDate.year << endl<< "�����: " << books[i].location << endl
            << "�������: " << books[i].number << endl<< "����� ������/�����: " << books[i].locWorkStudy << endl<< "���������: " << books[i].position << endl;
    }
}
void saveToFile() {
    ofstream file("books.txt");
    if (!file) {
        cout << "������ �������� �����\n";
        return;
    }
    for (auto book : books) {
        file << book.surname << endl<< book.name << endl<< book.lastname << endl<< book.birthDate.day << " " << book.birthDate.month << " "<< book.birthDate.year << endl
        << book.location << endl<< book.number << endl<< book.locWorkStudy << endl<< book.position << "\n\n";
    }
    cout << "������ ��������� � ��������� ����\n";
}

void loadFromFile() {
    ifstream file("books.txt");
    if (!file) {
        cout << "������ �������� �����\n";
        return;
    }
    books.clear();
    Book book;
    while (file.getline(book.surname, 50) &&
        file.getline(book.name, 50) &&
        file.getline(book.lastname, 50) &&
        file >> book.birthDate.day >> book.birthDate.month >> book.birthDate.year &&
        file.ignore() &&
        file.getline(book.location, 100) &&
        file.getline(book.number, 20) &&
        file.getline(book.locWorkStudy, 100) &&
        file.getline(book.position, 50)) {
        books.push_back(book);
        file.ignore();
    }
    cout << "��������� �������: " << books.size() << "\n";
}
void search() {
    char surname[50];
    cout << "������� �������: ";
    cin.getline(surname, 50);
    bool found = false;

    for (auto book : books) {
        if (strcmp(book.surname, surname) == 0) {
            cout << "\n�������:\n"
                << "�������: " << book.surname << endl<< "���: " << book.name << endl<< "��������: " << book.lastname << endl
                << "���� ��������: " << book.birthDate.day << "."<< book.birthDate.month << "." << book.birthDate.year << endl
                << "�����: " << book.location << endl<< "�������: " << book.number << endl
                << "����� ������/�����: " << book.locWorkStudy << endl<< "���������: " << book.position << endl;
            found = true;
        }
    }
    if (!found) cout << "������� � �������� '" << surname << "' �� �������\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
        cout << "\n\t\t����:\n"
            << "1. ���� ������\n"
            << "2. ����� ���� ������\n"
            << "3. ��������� � ����\n"
            << "4. ��������� �� �����\n"
            << "5. ����� �� �������\n"
            << "6. �����\n"
            << "> ";    
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: inputBook(); break;
        case 2: outputBooks(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: search(); break;
        case 6: cout << "�����\n"; break;
        default: cout << "��� ������ ��������\n";
        }
    } while (choice != 6);
    return 0;
}