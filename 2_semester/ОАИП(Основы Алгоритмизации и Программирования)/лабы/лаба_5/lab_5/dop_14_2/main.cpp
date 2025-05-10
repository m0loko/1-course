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
        cout << "������ ������� ����: " << dateStr << " (��������� ��.��.����)\n";
        date = { 0, 0, 0 };
        return;
    }
        date.day = stoi(dateStr.substr(0, 2));
        date.month = stoi(dateStr.substr(3, 2));
        date.year = stoi(dateStr.substr(6, 4));
}

void inputClient() {
    Client client;
    cout << "������� ���������� � �������:\n";
    cout << "�������: ";
    cin.getline(client.surname, 50);
    cout << "���: ";
    cin.getline(client.name, 50);
    cout << "��������: ";
    cin.getline(client.lastname, 50);
    cout << "���������� ������: ";
    cin.getline(client.passport, 20);
    string dInDate, dOutDate;
    cout << "���� ������ (��.��.����): ";
    getline(cin, dInDate);
    parseDate(dInDate, client.dIn);
    cout << "���� ������ (��.��.����): ";
    getline(cin, dOutDate);
    parseDate(dOutDate, client.dOut);
    cout << "����� �������: ";
    cin >> client.roomNumber;
    cin.ignore();
    cout << "��� ����������: ";
    cin.getline(client.roomType, 30);
    clients.push_back(client);
    cout << "������ ������� ��������\n";
}
void outputClients() {
    if (clients.empty()) {
        cout << "������ �������� ����\n";
        return;
    }
    cout << "\n������ ��������:\n";
    for (size_t i = 0; i < clients.size(); i++) {
        cout << "\n������ #" << i + 1 << ":\n"
            << "�������: " << clients[i].surname << endl
            << "���: " << clients[i].name << endl
            << "��������: " << clients[i].lastname << endl
            << "�������: " << clients[i].passport << endl
            << "�����: " << clients[i].dIn.day << "." << clients[i].dIn.month << "." << clients[i].dIn.year << endl
            << "�����: " << clients[i].dOut.day << "." << clients[i].dOut.month << "." << clients[i].dOut.year << endl
            << "�������: " << clients[i].roomNumber << endl
            << "���: " << clients[i].roomType << endl;
    }
}
void saveToFile() {
    ofstream file("clients.txt");
    if (!file) {
        cout << "������ �������� �����!\n";
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
    cout << "������ ���������\n";
}
void loadFromFile() {
    ifstream file("clients.txt");
    if (!file) {
        cout << "������ �������� �����!\n";
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
            cerr << "������ ������ ������ �������\n";
            break;
        }
        file.ignore();
        if (!file.getline(client.roomType, 30)) {
            cerr << "������ ������ ���� �������\n";
            break;
        }
        parseDate(dInDate, client.dIn);
        parseDate(dOutDate, client.dOut);
        clients.push_back(client);
    }
    cout << "��������� �������: " << clients.size() << endl;
}
void searchBySurname() {
    char surname[50];
    cout << "������� �������: ";
    cin.getline(surname, 50);
    bool found = false;
    for (auto& client : clients) {
        if (strcmp(client.surname, surname) == 0) {
            cout << "\n�������: " << client.surname << endl
                << "���: " << client.name << endl
                << "��������: " << client.lastname << endl
                << "�������: " << client.passport << endl
                << "�����: " << client.dIn.day << "." << client.dIn.month << "." << client.dIn.year << endl
                << "�����: " << client.dOut.day << "." << client.dOut.month << "." << client.dOut.year << endl
                << "�������: " << client.roomNumber << endl
                << "���: " << client.roomType << endl;
            found = true;
        }
    }
    if (!found) cout << "������ �� ������!\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
        cout << "\n����:\n"
            << "1. �������� �������\n"
            << "2. �������� ����\n"
            << "3. ��������� � ����\n"
            << "4. ��������� �� �����\n"
            << "5. ����� �� �������\n"
            << "6. �����\n"
            << "> ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: inputClient(); break;
        case 2: outputClients(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: searchBySurname(); break;
        case 6: cout << "�����\n"; break;
        default: cout << "�������� �����!\n";
        }
    } while (choice != 6);
    return 0;
}