#include <iostream>
#include <ctime>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    const int N = 100;
    int i, sz, T[N];
    cout << "Введите размер массива: ";
    cin >> sz;
    int razl = 0;
    cout << "Массив T:\n";
    srand((unsigned)time(NULL));
    for (i = 0; i < sz; i++) {
        T[i] = rand() % 2;
        cout << T[i] << endl;
    }

    for (int i = 0; i < sz; i++)
    {
        bool uniq = true;
        for (int j = 0; j < sz; j++) {
            if (T[i] == T[j] && i != j)
            {
                uniq = false;
            }
        }
        if (uniq)
        {
            razl++;
        }
    }cout << "\n\nКоличество различных элементов массива=" << razl;
    return 0;
}
