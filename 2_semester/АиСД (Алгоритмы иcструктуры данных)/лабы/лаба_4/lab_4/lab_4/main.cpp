#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    int n;
    while (true) {
        cout << "Введите количество товаров (N < 10000): ";
        cin >> n;
        if (n <= 0 || n >= 10000) {
            cout << "Ошибка. Пожалуйста, введите натуральное число меньше 10000\n";
        }
        else {
            break;
        }
    }

    vector<int> prices(n);
    for (int i = 0; i < n; i++) {
        prices[i] = rand() % 1000 ; 
    }

    cout << "\nЦены товаров:\n";
    for (int i = 0; i < n; i++) {
        cout << prices[i] << " ";
    }
    cout << endl;

    bubbleSort(prices);
    int k = (n + 1) / 2;
    vector<int> paid(prices.begin(), prices.begin() + k);
    vector<int> free(prices.begin() + k, prices.end());
    reverse(free.begin(), free.end());

    vector<int> order;
    int paid_idx = 0, free_idx = 0;
    while (paid_idx < paid.size() || free_idx < free.size()) {
        if (paid_idx < paid.size()) {
            order.push_back(paid[paid_idx++]);
        }
        if (free_idx < free.size()) {
            order.push_back(free[free_idx++]);
        }
    }

    cout << "\nПорядок пробивания товаров:\n";
    for (int i = 0; i < order.size(); i++) {
        if (i != 0) cout << " ";
        cout << order[i];
    }

    int total = 0;
    for (int price : paid) {
        total += price;
    }
    cout << "\nМаксимальная сумма в чеке: " << total << endl;

    return 0;
}
