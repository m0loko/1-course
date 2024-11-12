#include <iostream>
// задание 9
//MakarevichKirill2006
//МакаревичКириллВитальевич2006
//Макаревич2006Kirill

// задание 10
/* 4D 61 6B 61 72 65 76 69  63 68 4B 69 72 69 6C 6C 32 30 30 36 */
/* CC E0 EA E0 F0 E5 E2 E8 F7 CA E8 F0 E8 EB EB C2 E8 F2 E0 EB FC E5 E2 E8 F7 32 30 30 36 */
/* CC E0 EA E0 F0 E5 E2 E8 F7 32 30 30 36 4B 69 72 69 6C 6C */

// задание 11
//utf-8
/* 4D 61 6B 61 72 65 76 69 63 68 4B 69 72 69 6C 6C 32 30 30 36 */
/* D0 9C D0 B0 D0 BA D0 B0 D1 80 D0 B5 D0 B2 D0 B8 D1 87 D0 9A D0 B8 D1 80 D0 B8 D0 BB D0 BB D0 92 D0 B8 D1 82 D0 B0 D0 BB D1 8C D0 B5 D0 B2 D0 B8 D1 87 D1 87 32 30 30 36 */
/* D0 9C D0 B0 D0 BA D0 B0 D1 80 D0 B5 D0 B2 D0 B8 D1 87 32 30 30 36 4B 69 72 69 6C 6C */
//utf-16
/* 00 4D 00 61 00 6B 00 61 00 72 00 65 00 76 00 69 00 63 00 68 00 4B 00 69 00 72 00 69 00 6C 00 6C 00 32 00 30 00 30 00 36 */
/* 041C 0430 0430 0440 0435 0432 0438 0447 041A 0438 0440 0438 043B 043B 0412 0438 0442 0430 043B 044C 0435 0432 0438 0447 0437 0032 0030 0030 0036 */
/* 041C 0430 043A 0430 0440 0435 0432 0438 0447 0032 0030 0030 0036 004B 0069 0072 0069 006C 006C */
int main() {
    int number = 0x12345678;
    char hello[] = "Hello, ";
    char lfie[] = "MakarevichKirill2006";
    char rfie[] = "МакаревичКирилл2006";
    char lr[] = "Макаревич2006Kirill";

    wchar_t Lfie[] = L"MakarevichKirill2006";
    wchar_t Rfie[] = L"МакаревичКирилл2006";
    wchar_t LR[] = L"Макаревич2006Kirill";

    std::cout << hello << lfie << std::endl;
    return 0;
}
