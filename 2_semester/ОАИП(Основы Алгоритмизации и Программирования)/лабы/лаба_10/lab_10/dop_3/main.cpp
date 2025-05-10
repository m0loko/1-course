#include <iostream>
#include <vector>
using namespace std;

void per(vector<int>& n, int start) {
    if (start == n.size()) {
        for (int x : n) cout << x << " ";
        cout << endl;
        return;
    }

    for (int i = start; i < n.size(); i++) {
        swap(n[start], n[i]);
        per(n, start + 1);
        swap(n[start], n[i]); 
    }
}   

int main() {
    setlocale(LC_ALL, "ru");
    vector<int> n(5);
    cout << "Введите 5 различных натуральных чисел:\n";
    for (int i = 0; i < 5; i++) cin >> n[i];
    cout << "\nВсе перестановки:\n";
    per(n, 0);
    return 0;
}
