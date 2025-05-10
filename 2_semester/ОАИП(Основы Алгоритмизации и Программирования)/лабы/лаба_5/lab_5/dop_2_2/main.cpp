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
    cout << "������� ����� ������: ";
    cin >> train.trainNumber;
    cin.ignore();
    cout << "������� ����� ����������: ";
    cin.getline(train.pNazn, 50);
    cout << "������� ��� ����������: ";
    cin.getline(train.days, 50);
    cout << "������� ����� �������� (�� ��): ";
    cin >> train.oTime.hour >> train.oTime.minute;
    cout << "������� ����� ����������� (�� ��): ";
    cin >> train.dTime.hour >> train.dTime.minute;
    trains.push_back(train);
    cout << "����� ��������\n";
}
void outputTrains() {
    if (trains.empty()) {
        cout << "������ ������� ����\n";
        return;
    }
    for (size_t i = 0; i < trains.size(); i++) {
        cout << "\n����� #" << i + 1 << ":\n"
            << "����� ������: " << trains[i].trainNumber << endl
            << "����� ����������: " << trains[i].pNazn << endl
            << "��� ����������: " << trains[i].days << endl
            << "����� ��������: "
            << trains[i].oTime.hour << ":"
            << trains[i].oTime.minute << endl
            << "����� �����������: "
            << trains[i].dTime.hour << ":"
            << trains[i].dTime.minute << endl;
    }
}
void saveToFile() {
    ofstream file("trains.txt");
    if (!file) {
        cout << "������ �������� �����!\n";
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
    cout << "������ ���������\n";
}
void loadFromFile() {
    ifstream file("trains.txt");
    if (!file) {
        cout << "������ �������� �����\n";
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
    cout << "��������� �������: " << trains.size() << "\n";
}
void searchBypNazn() {
    cin.ignore();
    char pNazn[50];
    cout << "������� ����� ���������� ��� ������: ";
    cin.getline(pNazn, 50);
    bool found = false;
    for (const auto& train : trains) {
        if (strcmp(train.pNazn, pNazn) == 0) {
            cout << "\n����� ������: " << train.trainNumber << endl
                << "����� ����������: " << train.pNazn << endl
                << "��� ����������: " << train.days << endl
                << "����� ��������: "
                << train.oTime.hour << ":"
                << train.oTime.minute << endl
                << "����� �����������: "
                << train.dTime.hour << ":"
                << train.dTime.minute << endl;
            found = true;
        }
    }
    if (!found) cout << "����� �� '" << pNazn << "' �� ������\n";
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
            cout << "\n\t\t����:\n"
            <<"\n1. ���� ������\n"
            << "2. ����� ���� ������\n"
            << "3. ��������� � ����\n"
            << "4. ��������� �� �����\n"
            << "5. ����� �� ������ ����������\n"
            << "6. �����\n"
            << "�������� ��������: ";
        cin >> choice;
        switch (choice) {
        case 1: inputTrain(); break;
        case 2: outputTrains(); break;
        case 3: saveToFile(); break;
        case 4: loadFromFile(); break;
        case 5: searchBypNazn(); break;
        case 6: cout << "�����\n"; break;
        default: cout << "������! ������� ����� �� 1 �� 6\n";
        }
    } while (choice != 6);
    return 0;
}
