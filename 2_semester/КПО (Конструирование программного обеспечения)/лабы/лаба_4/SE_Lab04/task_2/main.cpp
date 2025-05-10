#include <iostream>
typedef unsigned int seconds;
typedef unsigned int minutes;
typedef unsigned int hours;
struct Time
{
	hours h;
	minutes m;
	seconds s;
};
bool operator<(Time t1, Time t2) {
	if (t1.h < t2.h || (t1.h == t2.h && t1.m < t2.m) || (t1.h == t2.h && t1.m == t2.m && t1.s < t2.s))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator>(Time t1, Time t2) {
	if (t1.h > t2.h || (t1.h == t2.h && t1.m > t2.m) || (t1.h == t2.h && t1.m == t2.m && t1.s > t2.s))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator==(Time t1, Time t2) {
	return (t1.h == t2.h && t1.m == t2.m && t1.s == t2.s);
}
int main()
{
	setlocale(LC_ALL, "ru");
	Time t1 = { 10, 50, 6 };
	Time t2 = { 25, 35, 45 };
	Time t3 = { 25, 35, 45 };
	if (t1<t2) std::cout << "истина\n";
	else std::cout << "ложь\n";
	
	if (t1 > t2) std::cout << "истина\n";
	else std::cout << "ложь\n";

	if (t2 == t3) std::cout << "истина\n";
	else std::cout << "ложь\n";

}