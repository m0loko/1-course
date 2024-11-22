#include <iostream>

int main()
{
    double d{ 10.6 };
    double* pd{ &d };
    std::cout << "Pointer pd: address:" << pd << std::endl;
    pd++;   // увеличение адреса на 8 байт - размер double
    std::cout << "Pointer pd: address:" << pd << std::endl;

    short n{ 5 };
    short* pn{ &n };
    std::cout << "Pointer pn: address:" << pn << std::endl;
    pn++;   // увеличение адреса на 2 байта - размер short
    std::cout << "Pointer pn: address:" << pn << std::endl;
}