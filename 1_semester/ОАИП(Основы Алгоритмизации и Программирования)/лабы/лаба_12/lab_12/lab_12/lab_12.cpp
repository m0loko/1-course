#include <iostream>

int main()
{
    double d{ 10.6 };
    double* pd{ &d };
    std::cout << "Pointer pd: address:" << pd << std::endl;
    pd++;   // ���������� ������ �� 8 ���� - ������ double
    std::cout << "Pointer pd: address:" << pd << std::endl;

    short n{ 5 };
    short* pn{ &n };
    std::cout << "Pointer pn: address:" << pn << std::endl;
    pn++;   // ���������� ������ �� 2 ����� - ������ short
    std::cout << "Pointer pn: address:" << pn << std::endl;
}