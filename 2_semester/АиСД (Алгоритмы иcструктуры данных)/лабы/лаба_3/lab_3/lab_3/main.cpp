#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

int* zapoln(int lenght) {
    srand(time(NULL));
    int* arr = new int[lenght];
    for (size_t i = 0; i < lenght; i++) {
        arr[i] = rand() % lenght;
    }
    return arr;
}

void bubbleSort(int arr[], int n) {
    while (n != 0) {
        int max_index = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                int temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                max_index = i;
            }
        }
        n = max_index;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void vbShort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
    }
}

void bstSort(int* mas, int first, int last) {
    int mid, count;
    int f = first, l = last;
    mid = mas[(f + l) / 2];
    do {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        if (f <= l) {
            count = mas[f];
            mas[f] = mas[l];
            mas[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) bstSort(mas, first, l);
    if (f < last) bstSort(mas, f, last);
}

int main() {
    setlocale(LC_ALL, "ru");
    int lenght;
    cout << "Введите длину массива: ";
    cin >> lenght;

    int* arr = zapoln(lenght);
    cout << "Исходный массив: ";
    for (size_t i = 0; i < lenght; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int* B = new int[lenght];
    int* C = new int[lenght];
    int* D = new int[lenght];
    int* E = new int[lenght];
    for (int i = 0; i < lenght; i++) {
        B[i] = arr[i];
        C[i] = arr[i];
        D[i] = arr[i];
        E[i] = arr[i];
    }

    cout << "Сортировка пузырьком: \n";
    auto begin = chrono::steady_clock::now();
    bubbleSort(B, lenght);
    auto end = chrono::steady_clock::now();
    cout << "Время выполнения: "
        << chrono::duration_cast<chrono::minutes>(end - begin).count() << " минут "
        << chrono::duration_cast<chrono::seconds>(end - begin).count() << " секунд "
        << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl;
    for (size_t i = 0; i < lenght; i++) {
        cout << B[i] << " ";
    }
    cout << endl;

    cout << "Сортировка вставкой (Шелла): \n";
    auto beginTwo = chrono::steady_clock::now();
    shellSort(C, lenght);
    auto endTwo = chrono::steady_clock::now();
    cout << "Время выполнения: "
        << chrono::duration_cast<chrono::minutes>(endTwo - beginTwo).count() << " минут "
        << chrono::duration_cast<chrono::seconds>(endTwo - beginTwo).count() << " секунд "
        << chrono::duration_cast<chrono::nanoseconds>(endTwo - beginTwo).count() << " наносекунд" << endl;
    for (size_t i = 0; i < lenght; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    cout << "Сортировка выбора:   \n";
    auto beginThree = chrono::steady_clock::now();
    vbShort(D, lenght);
    auto endThree = chrono::steady_clock::now();
    cout << "Время выполнения: "
        << chrono::duration_cast<chrono::minutes>(endThree - beginThree).count() << " минут "
        << chrono::duration_cast<chrono::seconds>(endThree - beginThree).count() << " секунд "
        << chrono::duration_cast<chrono::nanoseconds>(endThree - beginThree).count() << " наносекунд" << endl;
    for (size_t i = 0; i < lenght; i++) {
        cout << D[i] << " ";
    }
    cout << endl;

    cout << "Быстрая сортировка:   \n";
    auto beginFour = chrono::steady_clock::now();
    bstSort(E, 0, lenght - 1);
    auto endFour = chrono::steady_clock::now();
    cout << "Время выполнения: "
        << chrono::duration_cast<chrono::minutes>(endFour - beginFour).count() << " минут "
        << chrono::duration_cast<chrono::seconds>(endFour - beginFour).count() << " секунд "
        << chrono::duration_cast<chrono::nanoseconds>(endFour - beginFour).count() << " наносекунд" << endl;
    for (size_t i = 0; i < lenght; i++) {
        cout << E[i] << " ";
    }
    cout << endl;

    delete[] arr;
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] E;
    return 0;
}
