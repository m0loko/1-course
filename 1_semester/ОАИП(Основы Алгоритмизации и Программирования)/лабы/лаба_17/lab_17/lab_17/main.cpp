#include <iostream>
#include <windows.h>
using namespace std;

int* task1(int*, int);
void task2(int**, int, int);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;

    do {
        cout << "Какое задание нужно показать" << endl;
        cout << "1 - первое задание" << endl;
        cout << "2 - второе задание" << endl;
        cout << "3 - выход" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            int n;
            cout << "Введите размер одномерного массива: ";
            cin >> n;

            int* A = new int[n];
            cout << "Введите элементы массива:\n";
            for (int i = 0; i < n; i++) {
                cin >> A[i];
            }

            int* count = task1(A, n);
            if (*count > 0) {
                cout << "Количество отрицательных элементов на четных местах: " << *count << endl;
            }
            else {
                cout << "Таких элементов нет\n";
            }
            delete count;
            delete[] A;

            system("pause");
            system("cls");
            break;
        }
        case 2: {
            int n, m;
            cout << "Введите количество строк и столбцов матрицы: ";
            cin >> n >> m;

            int** matr = new int* [n];
            for (int i = 0; i < n; i++) {
                matr[i] = new int[m];
            }

            cout << "Заполните матрицу:\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cin >> matr[i][j];
                }
            }

            task2(matr, n, m);

            for (int i = 0; i < n; i++) {
                delete[] matr[i];
            }
            delete[] matr;

            system("pause");
            system("cls");
            break;
        }
        case 3:
            break;
        }
    } while (choice != 3);

    return 0;
}

int* task1(int* A, int n) {
    int* count_o = new int(0);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0 && A[i] < 0) {
            (*count_o)++;
        }
    }
    return count_o;
}

void task2(int** matr, int n, int m) {
    cout << "Исходная матрица:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }

    bool found = false;
    int rowIndex = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matr[i][j] < 0) {
                rowIndex = i;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (found) {
        cout << "Строка с отрицательным элементом: " << rowIndex + 1 << endl;
        cout << "Обновленная матрица (элементы столбца " << rowIndex + 1 << " уменьшены вдвое):\n";

        for (int i = 0; i < n; i++) {
            matr[i][rowIndex] /= 2;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << matr[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Нет строк с отрицательными элементами.\n";
    }
}
