#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
struct TRAIN {
    string destination;
    int trainNumber;    
    string departureTime; 
};
void inputTrain(vector<TRAIN>& trains) {
    for (int i = 0; i < 3; ++i) {
        TRAIN train;
        cout << "������� ������ ��� ������ " << i + 1 << ":\n";
        cout << "����� ����������: ";
        cin >> train.destination;
        cout << "����� ������: ";
        cin >> train.trainNumber;
        cout << "����� ����������� (� ������� ����): ";
        cin >> train.departureTime;
        trains.push_back(train);
    }
}

void findTrains(vector<TRAIN>& trains,  const string& sTime) {
    bool found = false;
    cout << "������, �������������� ����� " << sTime << ":\n";
    for (auto train : trains) {
        if (train.departureTime > sTime) {
            cout << "����� ����������: " << train.destination
                << ", ����� ������: " << train.trainNumber
                << ", ����� �����������: " << train.departureTime << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "�������, �������������� ����� " << sTime << ", �� �������.\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<TRAIN> train;
    inputTrain(train);
    string sTime;
    cout << "������� ����� ��� ������ ������� (� ������� ����): ";
    cin >> sTime;
    findTrains(train, sTime);
    return 0;
}