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
    cout << "Введите информацию:\n";
    cout << "Фамилия: ";
    cin.getline(book.surname, 50);
    cout << "Имя: ";
    cin.getline(book.name, 50);
    cout << "Отчество: ";
    cin.getline(book.lastname, 50);
    cout << "День рождения: ";
    cin >> book.birthDate.day;
    cout << "Месяц: ";
    cin >> book.birthDate.month;
    cout << "Год: ";
    cin >> book.birthDate.year;
    cin.ignore();
    cout << "Адрес: ";
    cin.getline(book.location, 100);
    cout << "Телефон: ";
    cin.getline(book.number, 20);
    cout << "Место работы/учебы: ";
    cin.getline(book.locWorkStudy, 100);
    cout << "Должность: ";
    cin.getline(book.position, 50);
    books.push_back(book); 
}
void outputBooks() {
    if (books.empty()) {
        cout << "Записей нет\n";
        return;
    }
    for (int i = 0; i < books.size(); i++) {
        cout << "\nЗапись #" << i + 1 << ":\n";
        cout << "Фамилия: " << books[i].surname << endl<< "Имя: " << books[i].name << endl
            << "Отчество: " << books[i].lastname << endl << "Дата рождения: " << books[i].birthDate.day << "."
            << books[i].birthDate.month << "." << books[i].birthDate.year << endl<< "Адрес: " << books[i].location << endl
            << "Телефон: " << books[i].number << endl<< "Место работы/учебы: " << books[i].locWorkStudy << endl<< "Должность: " << books[i].position << endl;
    }
}
void saveToFile() {
    ofstream file("books.txt");
    if (!file) {
        cout << "Ошибка открытия файла\n";
        return;
    }
    for (auto book : books) {
        file << book.surname << endl<< book.name << endl<< book.lastname << endl<< book.birthDate.day << " " << book.birthDate.month << " "<< book.birthDate.year << endl
        << book.location << endl<< book.number << endl<< book.locWorkStudy << endl<< book.position << "\n\n";
    }
    cout << "Данные сохранены в текстовый файл\n";
}

void loadFromFile() {
    ifstream file("books.txt");
    if (!file) {
        cout << "Ошибка открытия файла\n";
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
    cout << "Загружено записей: " << books.size() << "\n";
}
void search() {
    char surname[50];
    cout << "Введите фамилию: ";
    cin.getline(surname, 50);
    bool found = false;

    for (auto book : books) {
        if (strcmp(book.surname, surname) == 0) {
            cout << "\nНайдено:\n"
                << "Фамилия: " << book.surname << endl<< "Имя: " << book.name << endl<< "Отчество: " << book.lastname << endl
                << "Дата рождения: " << book.birthDate.day << "."<< book.birthDate.month << "." << book.birthDate.year << endl
                << "Адрес: " << book.location << endl<< "Телефон: " << book.number << endl
                << "Место работы/учебы: " << book.locWorkStudy << endl<< "Должность: " << book.position << endl;
            found = true;
        }
    }
    if (!found) cout << "Записей с фамилией '" << surname << "' не найдено\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
        cout << "\n\t\tМеню:\n"
            << "1. Ввод данных\n"
            << "2. Вывод всех данных\n"
            << "3. Сохранить в файл\n"
            << "4. Загрузить из файла\n"
            << "5. Поиск по фамилии\n"
            << "6. Выход\n"
            << "> ";    
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: inputBook(); break;
        case 2: outputBooks(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: search(); break;
        case 6: cout << "Выход\n"; break;
        default: cout << "Нет такого варианта\n";
        }
    } while (choice != 6);
    return 0;
}