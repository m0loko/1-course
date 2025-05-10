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
    cout << "Фамилия: " << book.surname << "\n" << "Имя: " << book.name << "\n" << "Отчество: " << book.lastname << "\n" << "Дата рождения: " << book.day << "."
        << book.month << "." << book.year << "\n" << "Адрес: " << book.location << "\n" << "Телефон: " << book.number << endl;
}
void inputBook(vector<Book>& books) {
    unsigned short temp1, temp2, temp3;
    Book book;
    cout << "Введите информацию:\n";
    cout << "Фамилия: ";
    cin >> book.surname;
    cout << "Имя: ";
    cin >> book.name;
    cout << "Отчество: ";
    cin >> book.lastname;
    cout << "Введите информацию про день-рождения:\n";
    cout << "День: "; cin >> temp1;
    book.day = temp1;
    cout << "Месяц: "; cin >> temp2;
    book.month = temp2;
    cout << "Год: "; cin >> temp3;
    book.year = temp3;
    cout << "Введите Адрес: "; cin >> book.location;
    cout << "Введите телефон: "; cin >> book.number;
    books.push_back(book);
}
void outputBooks(vector<Book>& books) {
    if (books.empty()) {
        cout << "Записная книжка пуста\n";
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
            cout << "Запись с фамилией " << surname << " удалена.\n";
            return;
        }
    }
    cout << "Запись с фамилией " << surname << " не найдена.\n";
}
void searchBook(vector<Book>& books, string& surname) {
    for (auto book : books) {
        if (book.surname == surname) {
            cout << "Найдено:\n";
            outputBook(book);
            return;
        }
    }
    cout << "Запись с фамилией " << surname << " не найдена\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Book> books;
    int choice;
    bool pr = true;
    string surname;
    do {
        cout << "\n\t\tМеню:\n";
        cout << "1. Ввод с клавиатуры информации для записной книги\n";
        cout << "2. Вывод на экран информации из записанной книги\n";
        cout << "3. Удалить записанную информацию\n";
        cout << "4. Поиск по фамилии\n";
        cout << "5. Выход\n";
        cout << "Ваш выбор: ";
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
            cout << "Введите фамилию для удаления: ";
            cin >> surname;
            deleteBook(books, surname);
            break;
        }
        case SEARCH_BOOK: {
            cout << "Введите фамилию для поиска: ";
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
