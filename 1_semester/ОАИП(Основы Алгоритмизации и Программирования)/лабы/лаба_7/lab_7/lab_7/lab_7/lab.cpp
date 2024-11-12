#include <iostream>

int main()
{
	setlocale(LC_ALL, "ru");
	//указываем массу пшеницы и одного зерна в милиграммах
	double americanmiligr = 49320000000000000, russianmiligr = 92800000000000000, belarusianmiligr = 8000000000000000, zernomiligr = 60, q = 2;
	int n;

	//расчет количества клеток шахматной доски через формулу суммы геометрической прогрессии (1) для Америки
	n = log2(americanmiligr / zernomiligr + 1) + 1;
	printf("Запас пшеницы у США закончится на %d", n);
	printf(" клетке\n");

	//(1) для России
	n = log2(russianmiligr / zernomiligr + 1) + 1;
	printf("Запас пшеницы у России закончится на %d", n);
	printf(" клетке\n");

	// (1) для Беларуси
	n = log2(belarusianmiligr / zernomiligr + 1) + 1;
	printf("Запас пшеницы у Беларуси закончится на %d", n);
	printf(" клетке\n");
	printf("Россия, кстати, продержится дольше всех\n");
	printf("Удачи:)");

	return 0;
}
