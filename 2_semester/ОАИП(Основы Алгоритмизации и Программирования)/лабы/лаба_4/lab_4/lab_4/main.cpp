#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct State
{
    string name;
    string capital;
    int population;
    double area;
    string president;
};
int current_size = 0; 

void inputState(State& s) {
    cout << "Государство №: " << current_size << endl;
    cout << "Введите название государства: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Введите столицу: ";
    getline(cin, s.capital);

    while (true) {
        cout << "Введите численность населения: ";
        cin >> s.population;
        if (s.population >= 0) break;
        cout << "Численность населения не может быть отрицательной\n";
    }

    while (true) {
        cout << "Введите площадь: ";
        cin >> s.area;
        if (s.area >= 0) break;
        cout << "Площадь не может быть отрицательной\n";
    }

    cout << "Введите имя президента: ";
    cin.ignore();
    getline(cin, s.president);
    current_size++;
}

void printState(State& s) {
    cout << "Государство: " << s.name << "\nСтолица: " << s.capital<< "\nНаселение: " << s.population << "\nПлощадь: " << s.area << "\nПрезидент: " << s.president << "\n\n";
}

void deleteState(State state[], int& size, int index) {
    if (index < 0 || index >= size) {
        cout << "Неверный индекс\n";
        return;
    }
    for (int i = index; i < size - 1; i++)
        state[i] = state[i + 1];
    size--;
    current_size--;
    cout << "Государство удалено\n";
}

void searchState(State state[], int size,string& name) {
    for (int i = 0; i < size; i++) {
        if (state[i].name == name) {
            printState(state[i]);
            return;
        }
    }
    cout << "Государство не найдено\n";
}

void writeToFile(State state[], int size) {
    ofstream outFile("state.txt");
    if (!outFile) {
        cout << "Ошибка записи в файл\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        outFile << state[i].name << "\n"<< state[i].capital << "\n"<< state[i].population << "\n"<< state[i].area << "\n"<< state[i].president << "\n";
    }
    outFile.close();
    cout << "Данные записаны в файл\n";
}

void readFromFile(State state[], int& size, int maxSize) {
    ifstream inFile("state.txt");
    if (!inFile) {
        cout << "Ошибка чтения файла!\n";
        return;
    }
    size = 0;
    while (size < maxSize && getline(inFile, state[size].name)) {
        getline(inFile, state[size].capital);
        inFile >> state[size].population;
        inFile >> state[size].area;
        inFile.ignore();
        getline(inFile, state[size].president);
        size++;
    }
    inFile.close();
    current_size = size;
    cout << "Данные успешно загружены из файла\n";
}

int main() {
    setlocale(LC_ALL, "ru");    
    const int maxStates = 100;
    State states[maxStates];
    int size = 0;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить государство\n";
        cout << "2. Показать все государства\n";
        cout << "3. Удалить государство\n";
        cout << "4. Поиск государства по названию\n";
        cout << "5. Записать данные в файл\n";
        cout << "6. Прочитать данные из файла\n";
        cout << "7. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (size < maxStates) inputState(states[size++]);
            else cout << "Достигнут максимум!\n";
            break;
        }
        case 2: {
            if (size == 0) cout << "Список государств пуст.\n";
            else {
                for (int i = 0; i < size; i++) {
                    cout << "Государство №" << i << ":\n";
                    printState(states[i]);
                }
            }
            break;
        }
        case 3: {
            int index;
            cout << "Введите индекс государства для удаления: ";
            cin >> index;
            deleteState(states, size, index);
            break;
        }
        case 4: {
            string name;
            cout << "Введите название государства: ";
            cin.ignore();
            getline(cin, name);
            searchState(states, size, name);
            break;
        }
        case 5: {
            writeToFile(states, size);
            break;
        }
        case 6: {
            readFromFile(states, size, maxStates);
            if (size > 0) {
                cout << "\nДанные из файла:\n";
                for (int i = 0; i < size; i++) printState(states[i]);
            }
            break;
        }
        case 7: {
            cout << "Выход из программы.\n";
            break;
        }
        default: {
            cout << "Неверный выбор! Попробуйте снова.\n";
            break;
        }
        }
    } while (choice != 7);

    return 0;
}