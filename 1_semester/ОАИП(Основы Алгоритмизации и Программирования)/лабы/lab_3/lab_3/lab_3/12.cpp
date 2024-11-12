#include <iostream>
void lab_15(){
	std::cout << "вариант 15:" << std::endl;
	float a = 1.75, b = 4.5 * pow(10, -4), y;
	y = a * exp(-2 * b) - sqrt(1 + a);
	std::cout << "y = " << y << std::endl;
	float r = log(1 + 20 * b) / (1 + a);
	std::cout << "r = " << r << std::endl;
}
void lab_4()
{
	std::cout << "вариант 4:" << std::endl;
	float q,p,t = 6, y = -2, x = 0.4e6;
	p = 2.6 * t + cos(y / (3 * x + y));
	std::cout << "p = " << p << std::endl;
	q = sin(t) / cos(t);
	std::cout << "q = " << q << std::endl;
}
void main()
{
	setlocale(LC_ALL, "ru");
	float t, x = 0.095, r = 5 * pow(10, -7);
	float k = 6, u;
	std::cout << "вариант 12:" << std::endl;
	t = tan(x) + r * (1 - log(x));
	std::cout << "t= " << t << std::endl;
	u = t / ((pow(x, 3) + 1) * (1 - exp(k - 4)));
	std::cout << "u= " << u << std::endl<<std::endl;
	lab_15();
	lab_4();
}
