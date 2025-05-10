#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
enum Emenu
{
    INPUT_CITIZEN = 1, OUTPUT_CITIZEN, DELETE_CITIZEN, SEARCH_CITIZEN, SEARCHBYYEAR, EXIT_PROGRAM
};
enum Gender { Male = 'м', Female = 'ж' };
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
    cout << "Фамилия: " << citizen.surname << "\n"
        << "Имя: " << citizen.name << "\n"
        << "Отчество: " << citizen.lastname << "\n"
        << "Дата рождения: " << citizen.day << "." << citizen.month << "." << citizen.year << "\n"
        << "Адрес: " << citizen.address << "\n"
        << "Телефон: " << citizen.phone << "\n"
        << "Пол: " << (citizen.gender == Male ? "мужской" : "женский") << endl;
}
void inputGorozanin(vector<Gorozanin>& gorozanin) {
    Gorozanin citizen;
    unsigned short temp1, temp2, temp3;
    cout << "Введите информацию о горожанине:\n";
    cout << "Фамилия: "; cin >> citizen.surname;
    cout << "Имя: "; cin >> citizen.name;
    cout << "Отчество: "; cin >> citizen.lastname;
    cout << "Введите информацию про день рождения:\n";
    cout << "День: "; cin >> temp1;
    citizen.day = temp1;
    cout << "Месяц: "; cin >> temp2;
    citizen.month = temp2;
    cout << "Год: "; cin >> temp3;
    citizen.year = temp3;
    cout << "Введите Адрес: "; cin >> citizen.address;
    cout << "Введите телефон: "; cin >> citizen.phone;
    char gender;
    cout << "Пол (м/ж): "; cin >> gender;
    citizen.gender = (gender == 'м' || gender == 'М') ? Male : Female;
    gorozanin.push_back(citizen);
}
void outputGorozanins(vector<Gorozanin>& gorozanin) {
    if (gorozanin.empty()) {
        cout << "Список горожан пуст.\n";
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
            cout << "Запись с фамилией " << surname << " удалена\n";
            return;
        }
    }
    cout << "Запись с фамилией " << surname << " не найдена.\n";
}
void searchGorozanin(const vector<Gorozanin>& gorozanin, const string& surname) {
    for (const auto& citizen : gorozanin) {
        if (citizen.surname == surname) {
            cout << "Найдено:\n";
            output(citizen);
            return;
        }
    }
    cout << "Запись с фамилией " << surname << " не найдена.\n";
}
void searchGorozaninsByYear(vector<Gorozanin>& gorozanin, unsigned year) {
    bool found = false;
    for (auto& citizen : gorozanin) {
        if (citizen.year == year) {
            if (!found) {
                cout << "Найдено записей с годом рождения " << year << ":\n";
                found = true;
            }
            output(citizen);
            cout << endl;
        }
    }
    if (!found) {
        cout << "Записи с годом рождения " << year << " не найдены.\n";
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
        cout << "\n\t\tМеню:\n";
        cout << "1. Ввод с клавиатуры информации о горожанине\n";
        cout << "2. Вывод на экран информации о горожанах\n";
        cout << "3. Удалить информацию о горожанине\n";
        cout << "4. Поиск по фамилии\n";
        cout << "5. Выборка по году рождения\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
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
            cout << "Введите фамилию для удаления: ";
            cin >> surname;
            deleteGorozanin(gorozanin, surname);
            break;
        }
        case SEARCH_CITIZEN: {
            cout << "Введите фамилию для поиска: ";
            cin >> surname;
            searchGorozanin(gorozanin, surname);
            break;
        }
        case SEARCHBYYEAR: {
            unsigned year;
            cout << "Введите год рождения для выборки: ";
            cin >> year;
            searchGorozaninsByYear(gorozanin, year);
            break;
        }
        case EXIT_PROGRAM: {
            pr = false;
            break;
        }
        default: {
            cout << "Неверный выбор, попробуйте снова\n";
            break;
        }
        }
    } while (pr);
    return 0;
}
