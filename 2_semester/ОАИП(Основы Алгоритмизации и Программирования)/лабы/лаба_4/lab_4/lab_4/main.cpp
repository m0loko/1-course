#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct State
{
    string name;
    string capital;
    int population;
    double area;
    string president;
};
int current_size = 0; 

void inputState(State& s) {
    cout << "����������� �: " << current_size << endl;
    cout << "������� �������� �����������: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "������� �������: ";
    getline(cin, s.capital);

    while (true) {
        cout << "������� ����������� ���������: ";
        cin >> s.population;
        if (s.population >= 0) break;
        cout << "����������� ��������� �� ����� ���� �������������\n";
    }

    while (true) {
        cout << "������� �������: ";
        cin >> s.area;
        if (s.area >= 0) break;
        cout << "������� �� ����� ���� �������������\n";
    }

    cout << "������� ��� ����������: ";
    cin.ignore();
    getline(cin, s.president);
    current_size++;
}

void printState(State& s) {
    cout << "�����������: " << s.name << "\n�������: " << s.capital<< "\n���������: " << s.population << "\n�������: " << s.area << "\n���������: " << s.president << "\n\n";
}

void deleteState(State state[], int& size, int index) {
    if (index < 0 || index >= size) {
        cout << "�������� ������\n";
        return;
    }
    for (int i = index; i < size - 1; i++)
        state[i] = state[i + 1];
    size--;
    current_size--;
    cout << "����������� �������\n";
}

void searchState(State state[], int size,string& name) {
    for (int i = 0; i < size; i++) {
        if (state[i].name == name) {
            printState(state[i]);
            return;
        }
    }
    cout << "����������� �� �������\n";
}

void writeToFile(State state[], int size) {
    ofstream outFile("state.txt");
    if (!outFile) {
        cout << "������ ������ � ����\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        outFile << state[i].name << "\n"<< state[i].capital << "\n"<< state[i].population << "\n"<< state[i].area << "\n"<< state[i].president << "\n";
    }
    outFile.close();
    cout << "������ �������� � ����\n";
}

void readFromFile(State state[], int& size, int maxSize) {
    ifstream inFile("state.txt");
    if (!inFile) {
        cout << "������ ������ �����!\n";
        return;
    }
    size = 0;
    while (size < maxSize && getline(inFile, state[size].name)) {
        getline(inFile, state[size].capital);
        inFile >> state[size].population;
        inFile >> state[size].area;
        inFile.ignore();
        getline(inFile, state[size].president);
        size++;
    }
    inFile.close();
    current_size = size;
    cout << "������ ������� ��������� �� �����\n";
}

int main() {
    setlocale(LC_ALL, "ru");    
    const int maxStates = 100;
    State states[maxStates];
    int size = 0;
    int choice;

    do {
        cout << "\n����:\n";
        cout << "1. �������� �����������\n";
        cout << "2. �������� ��� �����������\n";
        cout << "3. ������� �����������\n";
        cout << "4. ����� ����������� �� ��������\n";
        cout << "5. �������� ������ � ����\n";
        cout << "6. ��������� ������ �� �����\n";
        cout << "7. �����\n";
        cout << "��� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (size < maxStates) inputState(states[size++]);
            else cout << "��������� ��������!\n";
            break;
        }
        case 2: {
            if (size == 0) cout << "������ ���������� ����.\n";
            else {
                for (int i = 0; i < size; i++) {
                    cout << "����������� �" << i << ":\n";
                    printState(states[i]);
                }
            }
            break;
        }
        case 3: {
            int index;
            cout << "������� ������ ����������� ��� ��������: ";
            cin >> index;
            deleteState(states, size, index);
            break;
        }
        case 4: {
            string name;
            cout << "������� �������� �����������: ";
            cin.ignore();
            getline(cin, name);
            searchState(states, size, name);
            break;
        }
        case 5: {
            writeToFile(states, size);
            break;
        }
        case 6: {
            readFromFile(states, size, maxStates);
            if (size > 0) {
                cout << "\n������ �� �����:\n";
                for (int i = 0; i < size; i++) printState(states[i]);
            }
            break;
        }
        case 7: {
            cout << "����� �� ���������.\n";
            break;
        }
        default: {
            cout << "�������� �����! ���������� �����.\n";
            break;
        }
        }
    } while (choice != 7);

    return 0;
}