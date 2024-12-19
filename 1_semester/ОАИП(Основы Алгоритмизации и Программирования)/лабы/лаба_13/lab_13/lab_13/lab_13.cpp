#include <iostream>
void main()
{
    int num = 5;
    char symb, new_symbol = ' ';
    char* pc;
    pc = &symb;
    *pc = num + '0';
    std::cout << *pc << ' ';
    if (symb >= '0' && symb <= '9')
        num = symb - '0';
    std::cout << num << ' ';
    symb = 'b';
    if (symb >= 'a' && symb <= 'z')
        new_symbol = symb - 'a' + 'A';
    std::cout << new_symbol << ' ';
}

