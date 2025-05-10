#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool scobki(const string& expr) {
    stack<char> s;
    for (char ch : expr) {
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.empty()) {
                return false;
            }
            char top = s.top();
            if ((ch == ')' && top == '(') || (ch == ']' && top == '[') || (ch == '}' && top == '{')) {
                s.pop();
            }
            else {
                return false;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    string input;
    cout << "������� ��������� �� ��������: ";
    getline(cin, input);

    if (scobki(input)) {
        cout << "C����� ����������� �����\n";
    }
    else {
        cout << "������ ����������� �� �����\n";
    }

    return 0;
}
