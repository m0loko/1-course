#include <iostream>
#include <bitset>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "ru");

    // ���� ����� � ����������
    char str[33];
    int A, B, n, p, m, q,c=0;
    cout << "������� ����� A: ";
    cin >> A;
    _itoa_s(A, str, 2);
    cout << str << endl;
    cout << "������� ����� B: ";
    cin >> B;
    cout << "������� ���������� ����� n, ������� ���������� ���������� � 0 � A: ";
    cin >> n;
    cout << "������� ������� p, �� ������� ���������� ������ ������������� ���� � 0 � A: ";
    cin >> p;
    //cout << "������� ���������� ����� m, ������� ���������� �������� � B: ";
    //cin >> m;
    //cout << "������� ������� q, �� ������� ���������� ������ ������ ����� � B: ";
    //cin >> q;
    int maskA = ((1 << n) - 1)<<(p-1);
    _itoa_s(maskA, str, 2);
    cout << str<<endl;
    _itoa_s(((maskA & A) | c)>>(p-1), str, 2);
    cout << str;
    return 0;
}
