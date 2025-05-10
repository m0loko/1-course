#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void generate(string current,int A,ofstream &file) {
	if (current.length() == A) {
		file << current << endl;
		return;
	}

	for (int i = 0; i <= A; i++) {
		generate(current + to_string(i), A, file);
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	int A;
	cout << "Введите цифру A (от 1 до 9) ";
	cin >> A;
	if (A < 1 || A>9)
	{
		cout<<"Ошибка:A должна быть в пределах от 1 до 9" << endl;
		return 1;
	}
	ofstream file("output.txt");
	if (!file.is_open())
	{
		cout << "Не удалось открыть файл";
	}
	generate("", A, file);
	file.close();
	cout << "Все возможные числа записаны в файл output.txt" << endl;
	return 0;
}