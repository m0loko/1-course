#include <iostream>
#include "Call.h"

int main() {
    int sum = Call::cdecl_func(2, 3, 5);
    std::cout << "_cdecl result: " << sum << std::endl; 

    int x = 2;
    int product = Call::stdcall_func(x, 3, 5);
    std::cout << "_stdcall result: " << product << std::endl; 

    int fast_sum = Call::fastcall_func(2, 3, 5, 10);
    std::cout << "_fastcall result: " << fast_sum << std::endl; 

    return 0;
}