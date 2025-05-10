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
    cout << "������� ���������� ��� ��������:\n";
    cout << "�������: ";
    cin >> s.surname;
    cout << "���: ";
    cin >> s.name;
    cout << "��������: ";
    cin >> s.middleName;
    cout << "����� ���������: ";
    cin >> s.countEx;
    s.a.resize(s.countEx);
    cout << "������� ���������� ������ : \n";
    for (int i = 0; i < s.countEx; i++) {
        cout << i + 1 << " �������� : ";
        cin >> s.a[i];
    }
    cout << "�� ����� ��� ������ ������" << endl;
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
    cout << "������� ���������� ���������: ";
    cin >> n;
    vector<InfOfStudents> students(n);
    for (int i = 0; i < n; i++) {
        inputStudents(students[i]);
    }
    double ranking = calculateRanking(students);
    cout << "�������������� ������������: " << ranking << "%" << endl;
    return 0;
}