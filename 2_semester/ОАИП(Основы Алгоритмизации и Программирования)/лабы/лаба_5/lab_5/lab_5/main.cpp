#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
enum Emenu
{
    INPUT_BOOK = 1, OUTPUT_BOOK, DELETE_BOOK, SEARCH_BOOK, EXIT_PROGRAM
};
struct Book
{
    string name;
    string surname;
    string lastname;
    unsigned day : 5;
    unsigned month : 4;
    unsigned year : 11;
    string location;
    string number;
};
void outputBook(Book& book) {
    cout << "�������: " << book.surname << "\n" << "���: " << book.name << "\n" << "��������: " << book.lastname << "\n" << "���� ��������: " << book.day << "."
        << book.month << "." << book.year << "\n" << "�����: " << book.location << "\n" << "�������: " << book.number << endl;
}
void inputBook(vector<Book>& books) {
    unsigned short temp1, temp2, temp3;
    Book book;
    cout << "������� ����������:\n";
    cout << "�������: ";
    cin >> book.surname;
    cout << "���: ";
    cin >> book.name;
    cout << "��������: ";
    cin >> book.lastname;
    cout << "������� ���������� ��� ����-��������:\n";
    cout << "����: "; cin >> temp1;
    book.day = temp1;
    cout << "�����: "; cin >> temp2;
    book.month = temp2;
    cout << "���: "; cin >> temp3;
    book.year = temp3;
    cout << "������� �����: "; cin >> book.location;
    cout << "������� �������: "; cin >> book.number;
    books.push_back(book);
}
void outputBooks(vector<Book>& books) {
    if (books.empty()) {
        cout << "�������� ������ �����\n";
        return;
    }
    for (auto book : books) {
        outputBook(book);
        cout << endl;
    }
}
void deleteBook(vector<Book>& books, string& surname) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].surname == surname) {
            books.erase(books.begin() + i);  
            cout << "������ � �������� " << surname << " �������.\n";
            return;
        }
    }
    cout << "������ � �������� " << surname << " �� �������.\n";
}
void searchBook(vector<Book>& books, string& surname) {
    for (auto book : books) {
        if (book.surname == surname) {
            cout << "�������:\n";
            outputBook(book);
            return;
        }
    }
    cout << "������ � �������� " << surname << " �� �������\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Book> books;
    int choice;
    bool pr = true;
    string surname;
    do {
        cout << "\n\t\t����:\n";
        cout << "1. ���� � ���������� ���������� ��� �������� �����\n";
        cout << "2. ����� �� ����� ���������� �� ���������� �����\n";
        cout << "3. ������� ���������� ����������\n";
        cout << "4. ����� �� �������\n";
        cout << "5. �����\n";
        cout << "��� �����: ";
        cin >> choice;
        switch (choice) {
        case INPUT_BOOK: {
            inputBook(books);
            break;
        }
        case OUTPUT_BOOK: {
            outputBooks(books);
            break;
        }
        case DELETE_BOOK: {
            cout << "������� ������� ��� ��������: ";
            cin >> surname;
            deleteBook(books, surname);
            break;
        }
        case SEARCH_BOOK: {
            cout << "������� ������� ��� ������: ";
            cin >> surname;
            searchBook(books, surname);
            break;
        }
        case EXIT_PROGRAM:
        {
            pr = false;
            break;
        }
        }
    } while (pr);
    return 0;
}
