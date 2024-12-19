#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void men(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}
int main() {
    setlocale(LC_CTYPE, "Russian");
    srand(time(0));

    const int n = 4;
    float matrix[n][n];

    // Генерация случайной матрицы
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 21 - 10;
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Сортировка элементов на главной диагонали по убыванию
    for (int k = 0; k < n; k++) {
        int max_i = k, max_j = k;
        float max_val = matrix[k][k];

        // Поиск максимального элемента в оставшейся подматрице
        for (int i = k; i < n; i++) {
            for (int j = k; j < n; j++) {
                if (matrix[i][j] > max_val) {
                    max_val = matrix[i][j];
                    max_i = i;
                    max_j = j;
                }
            }
        }

        // Обмен максимального элемента с элементом на диагонали
        men(matrix[k][k], matrix[max_i][max_j]);
    }

    // Вывод измененной матрицы
    cout << "\nИзменённая матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}