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
    cout << "�������: " << guest.surname << endl
        << "���: " << guest.name << endl
        << "��������: " << guest.lastname << endl
        << "���������� ������: " << guest.passport << endl
        << "���� �������: " << guest.checkInDay << "." << guest.checkInMonth << "." << guest.checkInYear << endl
        << "���� �������: " << guest.checkOutDay << "." << guest.checkOutMonth << "." << guest.checkOutYear << endl
        << "����� �������: " << guest.roomNumber << endl
        << "��� ����������: ";

    switch (guest.roomType) {
    case LUXURY: cout << "����"; break;
    case ODN: cout << "�����������"; break;
    case DOO: cout << "�����������"; break;
    case TRI: cout << "�����������"; break;
    case APARTMENTS: cout << "�����������"; break;
    }
    cout << "\n\n";
}

void inputGuest(vector<Guest>& guests) {
    Guest guest;
    int tempDay, tempMonth, tempYear, tempType;
    cout << "������� �������: ";
    cin >> guest.surname;
    cout << "������� ���: ";
    cin >> guest.name;
    cout << "������� ��������: ";
    cin >> guest.lastname;
    cout << "������� ���������� ������: ";
    cin >> guest.passport;
    cout << "������� ���� ������� (����, �����, ���): ";
    cin >> tempDay >> tempMonth >> tempYear;
    guest.checkInDay = tempDay;
    guest.checkInMonth = tempMonth;
    guest.checkInYear = tempYear;
    cout << "������� ���� ������� (����, �����, ���): ";
    cin >> tempDay >> tempMonth >> tempYear;
    guest.checkOutDay = tempDay;
    guest.checkOutMonth = tempMonth;
    guest.checkOutYear = tempYear;
    cout << "������� ����� �������: ";
    cin >> guest.roomNumber;
    cout << "�������� ��� ���������� (0-����, 1-�����������, 2-�����������, 3-�����������, 4-�����������): ";
    cin >> tempType;
    guest.roomType = static_cast<RoomType>(tempType);
    guests.push_back(guest);
}
void outputGuests(vector<Guest>& guests) {
    if (guests.empty()) {
        cout << "������ �������� ����.\n";
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
        cout << "������ � ��������� ����� ������� �� �������\n";
    }
}
void deleteGuest(vector<Guest>& guests, string& surname) {
    for (auto it = guests.begin(); it != guests.end(); it++) {
        if (it->surname == surname) {
            guests.erase(it);
            cout << "����� � �������� " << surname << " ������\n";
            return;
        }
    }
    cout << "����� � �������� " << surname << " �� ������\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Guest> guests;
    int choice;
    do {
        cout << "\n\t\t����:\n"<< "1. �������� �����\n"<< "2. ������� ���� ������\n"<< "3. ����� ����� �� ���� �������\n"<< "4. ������� ����� �� �������\n"
        << "5. �����\n"<< "�������� ��������: ";
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
            cout << "������� ���� ������� (����, �����, ���): ";
            cin >> day >> month >> year;
            searchGuest(guests, day, month, year);
            break;
        }
        case 4: {
            string surname;
            cout << "������� ������� ����� ��� ��������: ";
            cin >> surname;
            deleteGuest(guests, surname);
            break;
        }
        case 5:
            cout << "����� �� ���������\n";
            return 0;
        default:
            cout << "������������ ����. ��������� �������\n";
        }
    } while (true);
    return 0;
}
