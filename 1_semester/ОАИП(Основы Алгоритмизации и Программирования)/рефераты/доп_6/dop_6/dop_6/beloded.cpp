#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0)); 

    cout << "�������� ��������:\n";
    cout << "1. �������������� �� ����������� � ����������� ������\n";
    cout << "2. �������������� �� ������������ � ���������� ������\n";
    int choice;
    cin >> choice;

    int n; // ���������� ������������
    int* dimensions = nullptr; // ����������� ������������ �������
    int totalElements = 1; // ����� ���������� ���������
    int* array = nullptr; // ���������� ������

    switch (choice) {
    case 1: { // �������������� �� ����������� � ����������� ������
        cout << "������� ���������� ������������ �������: ";
        cin >> n;

        dimensions = new int[n];
        cout << "������� ������� �� ������ �����������: ";
        for (int i = 0; i < n; i++) {
            cin >> dimensions[i];
            totalElements *= dimensions[i];
        }

        array = new int[totalElements];
        for (int i = 0; i < totalElements; i++) {
            array[i] = rand() % 100; // ��������� ���������� �������
        }

        cout << "\n���������� ������:\n";
        for (int i = 0; i < totalElements; i++) {
            cout << array[i] << " ";
        }
        cout << "\n\n����������� ������ (� ���� ��������):\n";
        int* indices = new int[n];
        for (int i = 0; i < totalElements; i++) {
            int temp = i;
            for (int j = n - 1; j >= 0; j--) {
                indices[j] = temp % dimensions[j];
                temp /= dimensions[j];
            }

            cout << "[";
            for (int j = 0; j < n; j++) {
                cout << indices[j] << (j < n - 1 ? ", " : "");  
            }
            cout << "] = " << array[i] << "\n";
        }

        delete[] indices;
        break;
    }
    case 2: { // �������������� �� ������������ � ���������� ������
        cout << "������� ���������� ������������ �������: ";
        cin >> n;

        dimensions = new int[n];
        cout << "������� ������� �� ������ �����������: ";
        for (int i = 0; i < n; i++) {
            cin >> dimensions[i];
            totalElements *= dimensions[i];
        }

        array = new int[totalElements];
        for (int i = 0; i < totalElements; i++) {
            array[i] = rand() % 100; // ��������� ���������� �������
        }

        cout << "\n����������� ������ (� ���� ��������):\n";
        int* indices = new int[n];
        for (int i = 0; i < totalElements; i++) {
            int temp = i;
            for (int j = n - 1; j >= 0; j--) {
                indices[j] = temp % dimensions[j];
                temp /= dimensions[j];
            }

            cout << "[";
            for (int j = 0; j < n; j++) {
                cout << indices[j] << (j < n - 1 ? ", " : "");
            }
            cout << "] = " << array[i] << "\n";
        }

        cout << "\n���������� ������:\n";
        for (int i = 0; i < totalElements; i++) {
            cout << array[i] << " ";
        }
        cout << endl;

        delete[] indices;
        break;
    }
    default:
        cout << "�������� �����!\n";
        break;
    }
    delete[] dimensions;
    delete[] array;

    return 0;
}
