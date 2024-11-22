#include <iostream>
#include <bitset>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "ru");

    // ¬вод чисел и параметров
    char str[33];
    int A, B, n, p, m, q,c=0;
    cout << "¬ведите число A: ";
    cin >> A;
    _itoa_s(A, str, 2);
    cout << str << endl;
    cout << "¬ведите число B: ";
    cin >> B;
    cout << "¬ведите количество битов n, которые необходимо установить в 0 в A: ";
    cin >> n;
    cout << "¬ведите позицию p, от которой необходимо начать устанавливать биты в 0 в A: ";
    cin >> p;
    //cout << "¬ведите количество битов m, которые необходимо заменить в B: ";
    //cin >> m;
    //cout << "¬ведите позицию q, от которой необходимо начать замену битов в B: ";
    //cin >> q;
    int maskA = ((1 << n) - 1)<<(p-1);
    _itoa_s(maskA, str, 2);
    cout << str<<endl;
    _itoa_s(((maskA & A) | c)>>(p-1), str, 2);
    cout << str;
    return 0;
}
