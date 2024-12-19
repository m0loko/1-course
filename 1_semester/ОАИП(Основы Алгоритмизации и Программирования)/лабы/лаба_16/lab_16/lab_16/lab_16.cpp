#include <iostream>
using namespace std;

int massiv(int* M, int); //прототип
void matrix();            //прототип

int main(void)
{
	setlocale(LC_CTYPE, "Russian");
	int choice;
	do
	{
		cout << "Выберите вариант работы" << endl;
		cout << "1 - с одномерным массивом" << endl;
		cout << "2 - с матрицей" << endl;
		cout << "3 - выход" << endl;
		cin >> choice; //выбор варианта работы
		switch (choice)
		{
		case 1:  int* M, size, i, av;//создали динамический массив М
			cout << "Введите размер массива ";
			cin >> size;
			M = new int[size];
			for (i = 0; i < size; i++)//заполняем массив
			{
				cout << "Введите " << i + 1 << " число ";
				cin >> *(M + i);//обращаемся к элементам массива через указатель
			}
			av = massiv(M, size); //вызов функции и передаём туда массив и размер массива
			cout << "Результат=" << av << endl;//показываем ср.арифм.
			delete[] M; //очищаем память
			break;
		case 2:  matrix();//вызов функции
			break;
		case 3:  break;//просто выходим из программы
		}
	} while (choice != 3);
}
int massiv(int* M, int size)
{
	int sum = 0, avar;
	for (int i = 0; i < size; i++)//находим сумму всех элементов массива
		sum += *(M + i); 
	avar = sum / size; //находим среднее арифмитическое
	return avar;// возвращаем ср.арифм.
}
void matrix()
{
	int** A, row, col, i, j, m; //создание двухмерного динамического массива A
	cout << "Введите число строк матрицы ";
	cin >> row;
	cout << "Введите чиcло столбцов ";
	cin >> col;
	A = new int* [row];
	for (i = 0; i < row; i++)//выделение памяти
		A[i] = new int[col];
	for (i = 0; i < row; i++)//заполнение 
		for (j = 0; j < col; j++)
		{
			cout << "Введите A[" << i << "],[" << j << "]= ";
			cin >> *(*(A + i) + j);//доступ к элементам массива через указатели
		}
	m = A[0][0];//начальное максимальное число в массиве
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			if (*(*(A + i) + j) > m) //проверка на то, если элемент массива больше текущего максимального
				m = *(*(A + i) + j);
	cout << "Результат=" << m << endl;//выводим максимальное число 
	for (i = 0; i < row; i++)//освобождение памяти
		delete A[i];
	delete[] A;
}
