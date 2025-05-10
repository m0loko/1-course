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
        cout << "\n������� ������ ��� ��������� � " << i + 1 << ":\n";
        cout << "�������� ���������: ";
        cin.ignore();
        getline(cin, sanat.nameS);
        cout << "����� ������������: ";
        getline(cin, sanat.location);
        cout << "�������� �������: ";
        getline(cin, sanat.medicalProfile);
        cout << "���������� �������: ";
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
        cout << "��� ������ ��� �����������\n";
        return;
    }

    cout << "\n������ ���������� (���������� �� ��������� ������� � ��������):\n";
    string currentProfile = "";

    for (auto sanat : sanats) {
        if (sanat.medicalProfile != currentProfile) {
            currentProfile = sanat.medicalProfile;
            cout << "\n�������� �������: " << currentProfile << "\n";
        }
        cout << "-------------------------\n";
        cout << "��������: " << sanat.nameS << endl;
        cout << "������������: " << sanat.location << endl;
        cout << "���������� �������: " << sanat.count << endl;
    }
}


void searchSanat( vector<Sanat>& sanats,  string& searchName) {
    bool found = false;
    for (auto sanat : sanats) {
        if (sanat.nameS == searchName) {
            cout << "\n������ ���������:\n";
            cout << "-------------------------\n";
            cout << "��������: " << sanat.nameS << "\n";
            cout << "������������: " << sanat.location << "\n";
            cout << "�������� �������: " << sanat.medicalProfile << "\n";
            cout << "���������� �������: " << sanat.count << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\n��������� � ����� ������ �� ������\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size;
    cout << "������� ���������� ����������: ";
    cin >> size;
    vector<Sanat> sanats;
    inputSanat(sanats, size);
    sortSanats(sanats);
    printSanats(sanats);
    string searchName;
    cout << "\n\n������� �������� ��������� ��� ������: ";
    cin.ignore();
    getline(cin, searchName);
    searchSanat(sanats, searchName);

    return 0;
}
