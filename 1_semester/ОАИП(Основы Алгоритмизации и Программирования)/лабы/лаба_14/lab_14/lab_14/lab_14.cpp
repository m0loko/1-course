#include <iostream>
void main()
{
	setlocale(LC_CTYPE, "Russian");
	using namespace std;
	const int n = 2, m = 4;
	int B[n][m];
	int i, j, row = 0, column = 0;
	cout << "Введите элементы массива" << endl;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			cin >> B[i][j];
	int min = B[0][0];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (min > B[i][j])
			{
				min = B[i][j];
				column = i;
				row = j;
			}
	cout << " Исходный массив:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "\n";
		for (int j = 0; j < m; j++)
			cout << "B[" << i << "," << j << "] =" << B[i][j] << "\t";
	}
	cout << endl;
	cout << "Минимальный элемент B[" << column << "," << row << "] =" << min << endl;
}
