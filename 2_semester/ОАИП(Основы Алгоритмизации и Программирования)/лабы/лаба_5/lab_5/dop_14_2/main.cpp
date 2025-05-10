#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <Windows.h>
using namespace std;
union Date {
    struct {
        unsigned short day;
        unsigned short month;
        unsigned short year;
    };
    unsigned short date[3];
};
struct Client {
    char surname[50];
    char name[50];
    char lastname[50];
    char passport[20];
    Date dIn;
    Date dOut;
    int roomNumber;
    char roomType[30];
};
vector<Client> clients;
void parseDate(string& dateStr, Date& date) {
    size_t dot1 = dateStr.find('.');
    size_t dot2 = dateStr.find('.', dot1 + 1);
    if (dot1 == string::npos || dot2 == string::npos || dot1 != 2 || dot2 != 5) {
        cout << "Ошибка формата даты: " << dateStr << " (ожидается дд.мм.гггг)\n";
        date = { 0, 0, 0 };
        return;
    }
        date.day = stoi(dateStr.substr(0, 2));
        date.month = stoi(dateStr.substr(3, 2));
        date.year = stoi(dateStr.substr(6, 4));
}

void inputClient() {
    Client client;
    cout << "Введите информацию о клиенте:\n";
    cout << "Фамилия: ";
    cin.getline(client.surname, 50);
    cout << "Имя: ";
    cin.getline(client.name, 50);
    cout << "Отчество: ";
    cin.getline(client.lastname, 50);
    cout << "Паспортные данные: ";
    cin.getline(client.passport, 20);
    string dInDate, dOutDate;
    cout << "Дата заезда (дд.мм.гггг): ";
    getline(cin, dInDate);
    parseDate(dInDate, client.dIn);
    cout << "Дата выезда (дд.мм.гггг): ";
    getline(cin, dOutDate);
    parseDate(dOutDate, client.dOut);
    cout << "Номер комнаты: ";
    cin >> client.roomNumber;
    cin.ignore();
    cout << "Тип размещения: ";
    cin.getline(client.roomType, 30);
    clients.push_back(client);
    cout << "Клиент успешно добавлен\n";
}
void outputClients() {
    if (clients.empty()) {
        cout << "Список клиентов пуст\n";
        return;
    }
    cout << "\nСписок клиентов:\n";
    for (size_t i = 0; i < clients.size(); i++) {
        cout << "\nКлиент #" << i + 1 << ":\n"
            << "Фамилия: " << clients[i].surname << endl
            << "Имя: " << clients[i].name << endl
            << "Отчество: " << clients[i].lastname << endl
            << "Паспорт: " << clients[i].passport << endl
            << "Заезд: " << clients[i].dIn.day << "." << clients[i].dIn.month << "." << clients[i].dIn.year << endl
            << "Выезд: " << clients[i].dOut.day << "." << clients[i].dOut.month << "." << clients[i].dOut.year << endl
            << "Комната: " << clients[i].roomNumber << endl
            << "Тип: " << clients[i].roomType << endl;
    }
}
void saveToFile() {
    ofstream file("clients.txt");
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    for (auto& client : clients) {
        file << client.surname << endl
            << client.name << endl
            << client.lastname << endl
            << client.passport << endl
            << (client.dIn.day < 10 ? "0" : "") << client.dIn.day << "."
            << (client.dIn.month < 10 ? "0" : "") << client.dIn.month << "."
            << client.dIn.year << endl
            << (client.dOut.day < 10 ? "0" : "") << client.dOut.day << "."
            << (client.dOut.month < 10 ? "0" : "") << client.dOut.month << "."
            << client.dOut.year << endl
            << client.roomNumber << endl
            << client.roomType << endl;
    }
    cout << "Данные сохранены\n";
}
void loadFromFile() {
    ifstream file("clients.txt");
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    clients.clear();
    Client client;
    string dInDate, dOutDate;
    while (file.getline(client.surname, 50) &&
        file.getline(client.name, 50) &&
        file.getline(client.lastname, 50) &&
        file.getline(client.passport, 20) &&
        getline(file, dInDate) &&
        getline(file, dOutDate)) {
        if (!(file >> client.roomNumber)) {
            cerr << "Ошибка чтения номера комнаты\n";
            break;
        }
        file.ignore();
        if (!file.getline(client.roomType, 30)) {
            cerr << "Ошибка чтения типа комнаты\n";
            break;
        }
        parseDate(dInDate, client.dIn);
        parseDate(dOutDate, client.dOut);
        clients.push_back(client);
    }
    cout << "Загружено записей: " << clients.size() << endl;
}
void searchBySurname() {
    char surname[50];
    cout << "Введите фамилию: ";
    cin.getline(surname, 50);
    bool found = false;
    for (auto& client : clients) {
        if (strcmp(client.surname, surname) == 0) {
            cout << "\nФамилия: " << client.surname << endl
                << "Имя: " << client.name << endl
                << "Отчество: " << client.lastname << endl
                << "Паспорт: " << client.passport << endl
                << "Заезд: " << client.dIn.day << "." << client.dIn.month << "." << client.dIn.year << endl
                << "Выезд: " << client.dOut.day << "." << client.dOut.month << "." << client.dOut.year << endl
                << "Комната: " << client.roomNumber << endl
                << "Тип: " << client.roomType << endl;
            found = true;
        }
    }
    if (!found) cout << "Клиент не найден!\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Добавить клиента\n"
            << "2. Показать всех\n"
            << "3. Сохранить в файл\n"
            << "4. Загрузить из файла\n"
            << "5. Поиск по фамилии\n"
            << "6. Выход\n"
            << "> ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: inputClient(); break;
        case 2: outputClients(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: searchBySurname(); break;
        case 6: cout << "Выход\n"; break;
        default: cout << "Неверный выбор!\n";
        }
    } while (choice != 6);
    return 0;
}