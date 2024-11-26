#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int A, B, n, p, q,m;
    char tmp[33];
    cout << "������� ����� ����� A: ";
    cin >> A;
    cout << "������� ����� ����� B: ";
    cin >> B;
    cout << "������� ����� ����� A ����� ���������� � 0? ";
    cin >> n;
    cout << "������� ������� p � ����� A, ������ �� ������� ����� ���������� � 0 ����: ";
    cin >> p;
    cout << "������� ����� ����� B ����� ��������? ";
    cin >> m;
    cout << "������� ������� q � ����� B, ������� � ������� ����� �������� ����: ";
    cin >> q;
    _itoa_s(A, tmp, 2);
    cout << "����� A � �������� �������: " << tmp << endl;
    _itoa_s(B, tmp, 2);
    cout << "����� B � �������� �������: " << tmp << endl;
    // �������� ����� ��� ��������� n ����� � 0 ����� �� ������� p
    int maskA = ((1 << n) - 1) << (p - n);
    _itoa_s(maskA, tmp, 2);
    cout << "����� A: " << tmp << endl;
    // ��������� n ����� � 0 � ����� A
    A = A & ~maskA;
    _itoa_s(A, tmp, 2);
    cout << "����� A ����� ��������� ����� � 0: " << tmp << endl;
    // ���������� n ����� �� ����� A
    int extractedBits = (A & maskA) >> p;
    _itoa_s(extractedBits, tmp, 2);
    cout << "����������� ���� �� ����� A: " << tmp << endl;
    // �������� ����� ��� ������ m ����� � ����� B ������� � ������� q
    int maskB = ((1 << m) - 1) << q;
    _itoa_s(maskB, tmp, 2);
    cout << "����� B: " << tmp << endl;
    // ������� m ����� � ����� B � ������ �� ������������ ������
    B = (B & ~maskB) | (extractedBits << (q - 1));
    _itoa_s(B, tmp, 2);
    cout << "����� B ����� ������ �����: " << tmp << endl;
    return 0;
}
