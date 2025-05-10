#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
enum RoomType {
    LUXURY,      
    ODN,      
    DOO,      
    TRI,      
    APARTMENTS   
};
struct Guest {
    string surname;
    string name;
    string lastname;
    string passport; 
    unsigned checkInDay : 5;
    unsigned checkInMonth : 4;
    unsigned checkInYear : 11;
    unsigned checkOutDay : 5;
    unsigned checkOutMonth : 4;
    unsigned checkOutYear : 11;
    RoomType roomType;
    int roomNumber; 
};
void outputGuest(Guest& guest) {
    cout << "Фамилия: " << guest.surname << endl
        << "Имя: " << guest.name << endl
        << "Отчество: " << guest.lastname << endl
        << "Паспортные данные: " << guest.passport << endl
        << "Дата приезда: " << guest.checkInDay << "." << guest.checkInMonth << "." << guest.checkInYear << endl
        << "Дата отъезда: " << guest.checkOutDay << "." << guest.checkOutMonth << "." << guest.checkOutYear << endl
        << "Номер комнаты: " << guest.roomNumber << endl
        << "Тип размещения: ";

    switch (guest.roomType) {
    case LUXURY: cout << "Люкс"; break;
    case ODN: cout << "Одноместный"; break;
    case DOO: cout << "Двухместный"; break;
    case TRI: cout << "Трехместный"; break;
    case APARTMENTS: cout << "Апартаменты"; break;
    }
    cout << "\n\n";
}

void inputGuest(vector<Guest>& guests) {
    Guest guest;
    int tempDay, tempMonth, tempYear, tempType;
    cout << "Введите фамилию: ";
    cin >> guest.surname;
    cout << "Введите имя: ";
    cin >> guest.name;
    cout << "Введите отчество: ";
    cin >> guest.lastname;
    cout << "Введите паспортные данные: ";
    cin >> guest.passport;
    cout << "Введите дату приезда (день, месяц, год): ";
    cin >> tempDay >> tempMonth >> tempYear;
    guest.checkInDay = tempDay;
    guest.checkInMonth = tempMonth;
    guest.checkInYear = tempYear;
    cout << "Введите дату отъезда (день, месяц, год): ";
    cin >> tempDay >> tempMonth >> tempYear;
    guest.checkOutDay = tempDay;
    guest.checkOutMonth = tempMonth;
    guest.checkOutYear = tempYear;
    cout << "Введите номер комнаты: ";
    cin >> guest.roomNumber;
    cout << "Выберите тип размещения (0-Люкс, 1-Одноместный, 2-Двухместный, 3-Трехместный, 4-Апартаменты): ";
    cin >> tempType;
    guest.roomType = static_cast<RoomType>(tempType);
    guests.push_back(guest);
}
void outputGuests(vector<Guest>& guests) {
    if (guests.empty()) {
        cout << "Список клиентов пуст.\n";
        return;
    }
    for (auto guest : guests) {
        outputGuest(guest);
    }
}
void searchGuest(vector<Guest>& guests, int day, int month, int year) {
    bool found = false;
    for (auto guest : guests) {
        if (guest.checkInDay == day && guest.checkInMonth == month && guest.checkInYear == year) {
            outputGuest(guest);
            found = true;
        }
    }
    if (!found) {
        cout << "Гостей с указанной датой приезда не найдено\n";
    }
}
void deleteGuest(vector<Guest>& guests, string& surname) {
    for (auto it = guests.begin(); it != guests.end(); it++) {
        if (it->surname == surname) {
            guests.erase(it);
            cout << "Гость с фамилией " << surname << " удален\n";
            return;
        }
    }
    cout << "Гость с фамилией " << surname << " не найден\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Guest> guests;
    int choice;
    do {
        cout << "\n\t\tМеню:\n"<< "1. Добавить гостя\n"<< "2. Вывести всех гостей\n"<< "3. Найти гостя по дате приезда\n"<< "4. Удалить гостя по фамилии\n"
        << "5. Выход\n"<< "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            inputGuest(guests);
            break;
        case 2:
            outputGuests(guests);
            break;
        case 3: {
            int day, month, year;
            cout << "Введите дату приезда (день, месяц, год): ";
            cin >> day >> month >> year;
            searchGuest(guests, day, month, year);
            break;
        }
        case 4: {
            string surname;
            cout << "Введите фамилию гостя для удаления: ";
            cin >> surname;
            deleteGuest(guests, surname);
            break;
        }
        case 5:
            cout << "Выход из программы\n";
            return 0;
        default:
            cout << "Некорректный ввод. Повторите попытку\n";
        }
    } while (true);
    return 0;
}
