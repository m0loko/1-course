#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
using namespace std;
struct Time {
    union {
        struct {
            unsigned short hour;
            unsigned short minute;
        };
        char timeStr[6];
    };
};
struct Train {
    int trainNumber;
    char pNazn[50];
    char days[50];
    Time oTime;
    Time dTime;
};
vector<Train> trains;
void inputTrain() {
    Train train;
    cout << "Введите номер поезда: ";
    cin >> train.trainNumber;
    cin.ignore();
    cout << "Введите пункт назначения: ";
    cin.getline(train.pNazn, 50);
    cout << "Введите дни следования: ";
    cin.getline(train.days, 50);
    cout << "Введите время прибытия (чч мм): ";
    cin >> train.oTime.hour >> train.oTime.minute;
    cout << "Введите время отправления (чч мм): ";
    cin >> train.dTime.hour >> train.dTime.minute;
    trains.push_back(train);
    cout << "Поезд добавлен\n";
}
void outputTrains() {
    if (trains.empty()) {
        cout << "Список поездов пуст\n";
        return;
    }
    for (size_t i = 0; i < trains.size(); i++) {
        cout << "\nПоезд #" << i + 1 << ":\n"
            << "Номер поезда: " << trains[i].trainNumber << endl
            << "Пункт назначения: " << trains[i].pNazn << endl
            << "Дни следования: " << trains[i].days << endl
            << "Время прибытия: "
            << trains[i].oTime.hour << ":"
            << trains[i].oTime.minute << endl
            << "Время отправления: "
            << trains[i].dTime.hour << ":"
            << trains[i].dTime.minute << endl;
    }
}
void saveToFile() {
    ofstream file("trains.txt");
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    for (auto& train : trains) {
        file << train.trainNumber << endl
            << train.pNazn << endl
            << train.days << endl
            << train.oTime.hour << " "
            << train.oTime.minute << endl
            << train.dTime.hour << " "
            << train.dTime.minute << endl;
    }
    cout << "Данные сохранены\n";
}
void loadFromFile() {
    ifstream file("trains.txt");
    if (!file) {
        cout << "Ошибка открытия файла\n";
        return;
    }
    trains.clear();
    Train train;
    while (file >> train.trainNumber &&
        file.ignore() &&
        file.getline(train.pNazn, 50) &&
        file.getline(train.days, 50) &&
        file >> train.oTime.hour >> train.oTime.minute &&
        file >> train.dTime.hour >> train.dTime.minute) {
        trains.push_back(train);
    }
    cout << "Загружено записей: " << trains.size() << "\n";
}
void searchBypNazn() {
    cin.ignore();
    char pNazn[50];
    cout << "Введите пункт назначения для поиска: ";
    cin.getline(pNazn, 50);
    bool found = false;
    for (const auto& train : trains) {
        if (strcmp(train.pNazn, pNazn) == 0) {
            cout << "\nНомер поезда: " << train.trainNumber << endl
                << "Пункт назначения: " << train.pNazn << endl
                << "Дни следования: " << train.days << endl
                << "Время прибытия: "
                << train.oTime.hour << ":"
                << train.oTime.minute << endl
                << "Время отправления: "
                << train.dTime.hour << ":"
                << train.dTime.minute << endl;
            found = true;
        }
    }
    if (!found) cout << "Поезд до '" << pNazn << "' не найден\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
            cout << "\n\t\tМеню:\n"
            <<"\n1. Ввод данных\n"
            << "2. Вывод всех данных\n"
            << "3. Сохранить в файл\n"
            << "4. Загрузить из файла\n"
            << "5. Поиск по пункту назначения\n"
            << "6. Выход\n"
            << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1: inputTrain(); break;
        case 2: outputTrains(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: searchBypNazn(); break;
        case 6: cout << "Выход\n"; break;
        default: cout << "Ошибка! Введите номер от 1 до 6\n";
        }
    } while (choice != 6);
    return 0;
}
