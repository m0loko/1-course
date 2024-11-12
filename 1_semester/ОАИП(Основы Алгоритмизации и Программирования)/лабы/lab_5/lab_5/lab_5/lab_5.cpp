//доп.хадание номер 2
#include <iostream> 
#include<cmath>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int Sy;
	char Sx;
	char arr[8]{ 'a','b','c','d','e','f','g','h' };
	char arr2[8]{ 'a','b','c','d','e','f','g','h' };
	cout << "¬ведите ваше расположение фигуры (oY): ";
	do
	{
		cin >> Sy;
	} while (Sy != 1 && Sy != 2 && Sy != 3 && Sy != 4 && Sy != 5 && Sy != 6 && Sy != 7 && Sy != 8);
	cout << "¬ведите расположение слона по X: a,b,c,d,e,f,g,h" << endl;;
	do
	{
		cin >> Sx;
		
	} while (Sx != arr[0] && Sx != arr[1] && Sx != arr[2] && Sx != arr[3] && Sx != arr[4] && Sx != arr[5] && Sx != arr[6] && Sx != arr[7]);
	int Uy;
	char Ux;
	cout << "¬ведите ваше расположение фигуры (oY): ";
	do
	{
		cin >> Uy;
	} while (Uy != 1 && Uy != 2 && Uy != 3 && Uy != 4 && Uy != 5 && Uy != 6 && Uy != 7 && Uy != 8);
	cout << "¬ведите ваше расположение фигуры (oX): ";
	do
	{
		cin >> Ux;
	} while (Ux != arr2[0] && Ux != arr2[1] && Ux != arr2[2] && Ux != arr2[3] && Ux != arr2[4] && Ux != arr2[5] && Ux != arr2[6] && Ux != arr2[7]);
	cout << endl << endl;
	int index_1, index_2;
	for (int i = 0; i < 8; i++) {
		if (arr[i] == Sx) {
			index_1 = i;
		}
		if (arr[i] == Ux) {
			index_2 = i;
		}
	}
	if (abs(index_1-index_2)==abs(Sy-Uy))
	{
		cout << "‘игуре угрожает слон" << endl;
	}
	else
	{
		cout << "‘игура в безопасности" << endl;
	}
	return 0;
}
