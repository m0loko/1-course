#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

void peres(int* X, int* Y, int k, int n) {
    int minSize = (k < n) ? k : n;
    int* Z = new int[minSize];
    int zSize = 0;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (*(X + i) == *(Y + j)) {
                bool exists = false;
                for (int l = 0; l < zSize; l++) {
                    if (*(Z + l) == *(X + i)) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    *(Z + zSize) = *(X + i);
                    zSize++;
                }
            }
        }
    }

    cout << "\nМассив пересечения Z: ";
    if (zSize == 0) {
        cout << "Нет общих элементов.";
    }
    else {
        for (int i = 0; i < zSize; i++) {
            cout << *(Z + i) << " ";
        }
    }
    cout << endl;

    delete[] Z;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int k, n;
    cout << "Введите размер массива X: ";
    cin >> k;
    cout << "Введите размер массива Y: ";
    cin >> n;
    int* X = new int[k];
    int* Y = new int[n];

    for (int i = 0; i < k; i++) {
        *(X + i) = rand() % 101;
    }
    for (int i = 0; i < n; i++) {
        *(Y + i) = rand() % 101;
    }

    cout << "Массив X: ";
    for (int i = 0; i < k; i++) {
        cout << *(X + i) << " ";
    }
    cout << endl;

    cout << "Массив Y: ";
    for (int i = 0; i < n; i++) {
        cout << *(Y + i) << " ";
    }
    cout << endl;

    peres(X, Y, k, n);

    delete[] X;
    delete[] Y;

    return 0;
}
