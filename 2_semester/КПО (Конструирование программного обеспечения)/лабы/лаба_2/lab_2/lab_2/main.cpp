#include<iostream>
using namespace std;
// задание 21
int sum(int x, int y) { return x + y; }; // 0x00FA55F0  55 8b ec 81 ec
int main() {
	// задание 2(вариант 12),	x=21, y=22, z=23 , s=13.0

	//задание 4,  
	bool b1 = true;  // 0x0113F947  01 
	bool b2 = false; // 0x0113F93B  00
	//задание 5
	char  c1 = 'a';   // 0x012FFE5F  61
	//задание 6
	char c2 = 'а';  // 0x012FFE53  e0
	//задание 7
	wchar_t wc1 = L'M'; // 0x006FFB44  4d
	//задание 8
	wchar_t wc2 = L'М'; // 0x012FF8EC  cc ff cc cc cc cc cc cc cc cc cc cc 4d 00
	//задание 9 
	short n1 = 21; // 15 - ручной ,  0x010FFDC0  15 00 - память
	short n2 = -21; // -15 - ручной, 0x010FFDB4  eb ff cc cc cc cc cc cc cc cc cc cc 15 00 - память
	//задание 10
	short maxSmall = 0x8000; // проверить можно через SHRT_MIN (-32768)
	short maxBig = 0x7FFF; 
	//задание 11
	unsigned short usMax = 0xFFFF; //2^16
	unsigned short usMin = 0x0000;
	//задание 12
	int y1 = 22; // 16-ручной, 0x00B5FC00  16 00 00 00
	int y2 = -22; // -16 - ручной, 0x00B5FBF4  ea ff ff ff cc cc cc cc cc cc cc cc 16 00 00 00
	//задание 13
	int maxI = 0x7FFFFFFF; // 2147483647
	int minI = 0x80000000; // -2147483648
	// задание 14
	unsigned int maxUI = 0xFFFFFFFF; //	4294967295
	unsigned int minUI = 0x00000000; // 0
	// задание 15
	long zM1 = 23; // 17 - ручной, 0x004FFCA4  17
	long zM2 = -23; // -17 - ручной, 0x00AFFC30  e9 ff ff ff cc cc cc cc cc cc cc cc 17
	// задание 16
	long maxL = 0x7FFFFFFF; // 2147483647
	long minL = 0x80000000; // -2147483648
	// задание 17
	unsigned long ulMax = 0xFFFFFFFFFFFFFFFF; // 4294967295
	unsigned long ulMin = 0x00000000; // 0
	// задание 18
	float lf1 = 13.000; // 0xD - ручной , IEEE 754  0x00AFF9A0  00 00 50 41
	float lf2 = -13.000; // -0xD - ручной , AFF994  00 00 50 c1
	// задание 19
	float f1 = 23.6f;
	float f2=  f1 / 0.0f; // Положительная бесконечность
	float f3 = -23.6;
	float f4 = f3/ 0.0f; // Отрицательная бесконечность
	float f5 = sqrt(-2.0f); // приколы с компилятором
	float f6 = std::numeric_limits<float>::quiet_NaN(); // так явно указывается 
	// задание 20
	char ch = 'A';
	wchar_t wch = L'B';
	short sh = 32767;
	int i = 12345;
	float f = 3.14f;
	double d = 2.71828;

	char* ptr_ch = &ch; // 0x00F3F9BB  41
	wchar_t* ptr_wch = &wch; // 0x00F3F9AC  42
	short* ptr_sh = &sh; // 0x00F3F9A0  ff7f
	int* ptr_i = &i; // 0x00F3F994  39 30 00 00
	float* ptr_f = &f; // 0x00F3F988  c3 f5 48 40 
	double* ptr_d = &d; // 0x00F3F978  90 f7 aa 95 09

	ptr_ch += 3; // 0x0058F8FE  cc cc cc cc cc cc 00 00 c0 7f
	ptr_wch += 3; // 0x0058F8F2  cc cc cc cc cc cc cc cc cc 41
	ptr_sh += 3; // 0x0058F8E6  cc cc cc cc cc cc 42 00
	ptr_i += 3; // 0x0058F8E0  ff 7f
	ptr_f += 3; // 0x0058F8D4  39 30 00 00
	ptr_d += 3; // 0x0058F8D0  cc cc cc cc 39 30 00 00 
	
	//задание 21
	int (*ff)(int, int) = sum; // 0x00FA55F0  55 8b ec 81 ec
	int x = ff(2, 4); // 0x00B8F684  06 00 00 00
	return 0;		
}