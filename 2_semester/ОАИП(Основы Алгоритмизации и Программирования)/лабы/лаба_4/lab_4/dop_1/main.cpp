#include <iostream>
#include <vector>
using namespace std;

struct InfOfStudents {
    string name;
    string surname;
    string middleName;
    int countEx;
    vector<int> a;
};

void inputStudents(InfOfStudents& s) {
    cout << "Введите информацию про студента:\n";
    cout << "Фамилия: ";
    cin >> s.surname;
    cout << "Имя: ";
    cin >> s.name;
    cout << "Отчество: ";
    cin >> s.middleName;
    cout << "Число экзаменов: ";
    cin >> s.countEx;
    s.a.resize(s.countEx);
    cout << "Введите полученные оценки : \n";
    for (int i = 0; i < s.countEx; i++) {
        cout << i + 1 << " эказамен : ";
        cin >> s.a[i];
    }
    cout << "Вы ввели все нужные данные" << endl;
}

bool otl(InfOfStudents& student) {
    for (int grade : student.a) {
        if (grade != 4 && grade != 5) {
            return false;
        }
    }
    return true;
}

double calculateRanking(vector<InfOfStudents>& students) {
    if (students.empty()) {
        return 0.0;
    }
    int honorStudents = 0;
    for (auto student : students) {
        if (otl(student)) {
            honorStudents++;
        }
    }
    return (static_cast<double>(honorStudents) / students.size() * 100.0);
}

int main() {
    setlocale(LC_ALL, "ru");
    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    vector<InfOfStudents> students(n);
    for (int i = 0; i < n; i++) {
        inputStudents(students[i]);
    }
    double ranking = calculateRanking(students);
    cout << "Характеристика успеваемости: " << ranking << "%" << endl;
    return 0;
}