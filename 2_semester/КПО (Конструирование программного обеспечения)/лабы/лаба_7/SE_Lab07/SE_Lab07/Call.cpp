#include "Call.h"

namespace Call {
    int __cdecl cdecl_func(int a, int b, int c) {
        return a + b + c;
    }

    int __stdcall stdcall_func(int& a, int b, int c) {
        return a * b * c;
    }

    int __fastcall fastcall_func(int a, int b, int c, int d) {
        return a + b + c + d;
    }
}