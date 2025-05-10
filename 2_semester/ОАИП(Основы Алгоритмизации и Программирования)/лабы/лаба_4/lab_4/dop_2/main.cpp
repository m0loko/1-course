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
        cout << "Введите данные для поезда " << i + 1 << ":\n";
        cout << "Пункт назначения: ";
        cin >> train.destination;
        cout << "Номер поезда: ";
        cin >> train.trainNumber;
        cout << "Время отправления (в формате ччмм): ";
        cin >> train.departureTime;
        trains.push_back(train);
    }
}

void findTrains(vector<TRAIN>& trains,  const string& sTime) {
    bool found = false;
    cout << "Поезда, отправляющиеся после " << sTime << ":\n";
    for (auto train : trains) {
        if (train.departureTime > sTime) {
            cout << "Пункт назначения: " << train.destination
                << ", Номер поезда: " << train.trainNumber
                << ", Время отправления: " << train.departureTime << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Поездов, отправляющихся после " << sTime << ", не найдено.\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<TRAIN> train;
    inputTrain(train);
    string sTime;
    cout << "Введите время для поиска поездов (в формате ччмм): ";
    cin >> sTime;
    findTrains(train, sTime);
    return 0;
}