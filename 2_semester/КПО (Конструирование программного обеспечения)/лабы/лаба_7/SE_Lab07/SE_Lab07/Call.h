#pragma once

namespace Call {
    int __cdecl cdecl_func(int a, int b, int c);

    int __stdcall stdcall_func(int& a, int b, int c);

    int __fastcall fastcall_func(int a, int b, int c, int d);
}
