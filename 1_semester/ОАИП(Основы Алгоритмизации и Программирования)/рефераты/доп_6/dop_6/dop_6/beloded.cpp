#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0)); 

    cout << "¬ыберите действие:\n";
    cout << "1. ѕреобразование из одномерного в многомерный массив\n";
    cout << "2. ѕреобразование из многомерного в одномерный массив\n";
    int choice;
    cin >> choice;

    int n; // количество размерностей
    int* dimensions = nullptr; // размерности многомерного массива
    int totalElements = 1; // общее количество элементов
    int* array = nullptr; // одномерный массив

    switch (choice) {
    case 1: { // преобразование из одномерного в многомерный массив
        cout << "¬ведите количество размерностей массива: ";
        cin >> n;

        dimensions = new int[n];
        cout << "¬ведите размеры по каждой размерности: ";
        for (int i = 0; i < n; i++) {
            cin >> dimensions[i];
            totalElements *= dimensions[i];
        }

        array = new int[totalElements];
        for (int i = 0; i < totalElements; i++) {
            array[i] = rand() % 100; // заполн€ем случайными числами
        }

        cout << "\nќдномерный массив:\n";
        for (int i = 0; i < totalElements; i++) {
            cout << array[i] << " ";
        }
        cout << "\n\nћногомерный массив (в виде индексов):\n";
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
    case 2: { // преобразование из многомерного в одномерный массив
        cout << "¬ведите количество размерностей массива: ";
        cin >> n;

        dimensions = new int[n];
        cout << "¬ведите размеры по каждой размерности: ";
        for (int i = 0; i < n; i++) {
            cin >> dimensions[i];
            totalElements *= dimensions[i];
        }

        array = new int[totalElements];
        for (int i = 0; i < totalElements; i++) {
            array[i] = rand() % 100; // паполн€ем случайными числами
        }

        cout << "\nћногомерный массив (в виде индексов):\n";
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

        cout << "\nќдномерный массив:\n";
        for (int i = 0; i < totalElements; i++) {
            cout << array[i] << " ";
        }
        cout << endl;

        delete[] indices;
        break;
    }
    default:
        cout << "Ќеверный выбор!\n";
        break;
    }
    delete[] dimensions;
    delete[] array;

    return 0;
}
