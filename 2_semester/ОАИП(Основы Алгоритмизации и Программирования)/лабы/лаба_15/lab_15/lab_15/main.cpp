#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

void bubbleSort(vector<int>& a) {
    int t;
    for (int i = 1; i < a.size(); i++)
        for (int j = a.size() - 1; j >= i; j--)
        if (a[j - 1] > a[j]) {
         t = a[j - 1];
         a[j - 1] = a[j];
         a[j] = t;
        }
}

void shellSort(vector<int>& a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}


void merge(vector<int>& a, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void vbSort(vector<int>& a) {
    int minIndex;
    for (int i = 0; i < a.size() - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < a.size(); j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(a[i], a[minIndex]);
        }
    }
}

void insertionSort(vector<int>& a) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int sizes[] = { 1000, 2000, 3000, 4000, 5000 };

    for (int size : sizes) {
        vector<int> A(size);
        for (int i = 0; i < size; i++) A[i] = rand() % 10000;

        vector<int> B;
        for (int i = 0; i < size; i += 2) B.push_back(A[i]);

        vector<int> B_bubble = B;
        auto start1 = steady_clock::now();
        bubbleSort(B_bubble);
        auto end1 = steady_clock::now();

        vector<int> B_merge = B;
        auto start2 = steady_clock::now();
        mergeSort(B_merge, 0, B_merge.size() - 1);
        auto end2 = steady_clock::now();

        vector<int> B_vb = B;
        auto start3 = steady_clock::now();
        vbSort(B_vb);
        auto end3 = steady_clock::now();

        vector<int> B_shell = B;
        auto start4 = steady_clock::now();
        shellSort(B_shell);
        auto end4 = steady_clock::now();

        vector<int> B_insertion = B;
        auto start5 = steady_clock::now();
        insertionSort(B_insertion);
        auto end5 = steady_clock::now();

        auto timeShellSort = duration_cast<nanoseconds>(end4 - start4).count();
        auto timeBubbleSort = duration_cast<nanoseconds>(end1 - start1).count();
        auto timemergesort = duration_cast<nanoseconds>(end2 - start2).count();
        auto timevbSort = duration_cast<nanoseconds>(end3 - start3).count();

        cout << "\nРазмер массива: " << size;
        cout << "\nВремя пузырьковой сортировки: " << timeBubbleSort << " наносекунд";
        cout << "\nВремя сортировки слиянием: " << timemergesort << " наносекунд\n";
        cout << "\nВремя сортировки выбором: " << timevbSort << " наносекунд\n";
        cout << "\nВремя сортировки Шелла: " << timeShellSort << " наносекунд\n";
        cout << "\nСортировка вставками: " << duration_cast<nanoseconds>(end5 - start5).count() << " нс\n";
    }

    return 0;
}
