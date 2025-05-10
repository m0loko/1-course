#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    int n;
    while (true) {
        cout << "Введите количество участников (n < 10000): ";
        cin >> n;
        if (n <= 0 || n >= 10000) {
            cout << "Ошибка. Введите натуральное число меньше 10000\n";
        }
        else {
            break;
        }
    }

    vector<int> scores(n);
    cout << "Сгенерированные баллы участников:\n";
    for (int i = 0; i < n; i++) {
        scores[i] = rand() % 100 + 1;
        cout << scores[i] << " ";
    }
    cout << "\n";


    bubbleSort(scores);

    vector<int> top3;
    for (int i = 0; i < n && top3.size() < 3; i++) {
        if (top3.empty() || scores[i] != top3.back()) {
            top3.push_back(scores[i]);
        }
    }

    int prizery = 0;
    for (int i = 0; i < n; i++) {
        if (scores[i] == top3[0] ||
            (top3.size() > 1 && scores[i] == top3[1]) ||
            (top3.size() > 2 && scores[i] == top3[2])) {
            prizery++;
        }
        else {
            break; 
        }
    }

    cout << "\nКоличество призеров: " << prizery << endl;

    return 0;
}
