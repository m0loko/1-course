#include <iostream>
#include <vector>
using namespace std;

void main() {
    setlocale(LC_CTYPE, "Russian");
    int rows, cols;
    cout << "������� ���������� �����: ";
    cin >> rows;
    cout << "������� ���������� ��������: ";
    cin >> cols;

    int** array = new int* [rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new int[cols];
    }

    cout << "������� �������� �������: \n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "������� [" << i << "][" << j << "]: ";
            cin >> array[i][j];
        }
    }

    int rz = -1; 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (array[i][j] == 0) {
                rz = i; 
                break;
            }
        }
        if (rz != -1) {
            break;
        }
    }

    if (rz != -1) {
        cout << "\n������, ���������� ����, �������: " << rz + 1 << endl;
        int first_element = array[rz][0];  

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                array[i][j] -= first_element;
            }
        }


        cout << "\n���������� �������:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "\n� ������� ��� ������, ���������� ����.\n";
    }

    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;
}


