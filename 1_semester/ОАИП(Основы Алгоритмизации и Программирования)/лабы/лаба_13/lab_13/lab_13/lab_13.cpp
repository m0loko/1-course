#include <iostream>
#include <fstream>
#include <string>
#include <thread> // ��� ��������
#include <chrono> // ��� ��������

using namespace std;

// �������������� ��������
void welcomeAnimation() {
    cout << "---------------------------" << endl;
    cout << "|   ����� ����������!     |" << endl;
    cout << "---------------------------" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    for (int i = 0; i < 3; i++) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl << "�������� ���������!" << endl;
}

// ������� ����
void mainMenu() {
    cout << "\n=== ������� ���� ===" << endl;
    cout << "1. ������ ������ �������" << endl;
    cout << "2. ��������� ������ �� �����" << endl;
    cout << "3. ����� �� ���������" << endl;
    cout << "�������� ��������: ";
}

// ��������� ����� ������ �������
void manualInput() {
    string data;
    cout << "������� ������ �������: ";
    cin.ignore();
    getline(cin, data);
    cout << "�� �����: " << data << endl;
}

// ������ ������ �� �����
void fileParser() {
    string filename;
    cout << "������� ��� �����: ";
    cin >> filename;

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        cout << "������ �� �����:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "������: ���� �� ������!" << endl;
    }
}

// �������� ���������
int main() {
    setlocale(LC_ALL, "ru");
    welcomeAnimation(); // �������������� ��������

    while (true) {
        mainMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            manualInput();
            break;
        case 2:
            fileParser();
            break;
        case 3:
            cout << "����� �� ���������. �� ��������!" << endl;
            return 0;
        default:
            cout << "������: �������� ����. ���������� �����." << endl;
            system("cls");
        }
    }

    return 0;
}