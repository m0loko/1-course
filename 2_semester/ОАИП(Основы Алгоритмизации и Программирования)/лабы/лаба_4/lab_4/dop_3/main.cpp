#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;
struct Sanat {
    string nameS;          
    string location;        
    string medicalProfile;  
    int count;           
};

void inputSanat(vector<Sanat>& sanats, int size) {
    for (int i = 0; i < size; i++) {
        Sanat sanat;
        cout << "\nВведите данные для санатория № " << i + 1 << ":\n";
        cout << "Название санатория: ";
        cin.ignore();
        getline(cin, sanat.nameS);
        cout << "Место расположения: ";
        getline(cin, sanat.location);
        cout << "Лечебный профиль: ";
        getline(cin, sanat.medicalProfile);
        cout << "Количество путевок: ";
        cin >> sanat.count;
        sanats.push_back(sanat);
    }
}

bool compareSanats(Sanat& a, Sanat& b) {
    if (a.medicalProfile == b.medicalProfile)
        return a.nameS < b.nameS;  
    return a.medicalProfile < b.medicalProfile;
}

void sortSanats(vector<Sanat>& sanats) {
    sort(sanats.begin(), sanats.end(), compareSanats);
}


void printSanats(vector<Sanat>& sanats) {
    if (sanats.empty()) {
        cout << "Нет данных для отображения\n";
        return;
    }

    cout << "\nСписок санаториев (сортирован по лечебному профилю и названию):\n";
    string currentProfile = "";

    for (auto sanat : sanats) {
        if (sanat.medicalProfile != currentProfile) {
            currentProfile = sanat.medicalProfile;
            cout << "\nЛечебный профиль: " << currentProfile << "\n";
        }
        cout << "-------------------------\n";
        cout << "Название: " << sanat.nameS << endl;
        cout << "Расположение: " << sanat.location << endl;
        cout << "Количество путевок: " << sanat.count << endl;
    }
}


void searchSanat( vector<Sanat>& sanats,  string& searchName) {
    bool found = false;
    for (auto sanat : sanats) {
        if (sanat.nameS == searchName) {
            cout << "\nНайден санаторий:\n";
            cout << "-------------------------\n";
            cout << "Название: " << sanat.nameS << "\n";
            cout << "Расположение: " << sanat.location << "\n";
            cout << "Лечебный профиль: " << sanat.medicalProfile << "\n";
            cout << "Количество путевок: " << sanat.count << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nСанаторий с таким именем не найден\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size;
    cout << "Введите количество санаториев: ";
    cin >> size;
    vector<Sanat> sanats;
    inputSanat(sanats, size);
    sortSanats(sanats);
    printSanats(sanats);
    string searchName;
    cout << "\n\nВведите название санатория для поиска: ";
    cin.ignore();
    getline(cin, searchName);
    searchSanat(sanats, searchName);

    return 0;
}
