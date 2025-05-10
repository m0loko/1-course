#include <iostream>
#include <string>
using namespace std;

struct Tree {
    int key;
    string text;
    Tree* Left, * Right;
};

Tree* makeTree(Tree* Root);
Tree* list(int key, const string& text);
Tree* insertElem(Tree* Root, int key, const string& text);
Tree* search(Tree* root, int key);
Tree* delet(Tree* root, int key);
void view(Tree* root, int level = 0);
double dop_1(Tree* t);
int sumNodes(Tree* root);
int sumKeys(Tree* root);
void delAll(Tree*& root);

Tree* Root = nullptr;

int main() {
    setlocale(LC_ALL, "ru");
    int choice, key;
    string text;
    char letter;

    while (true) {
        cout << "\n1 - ������� ������\n"
            "2 - �������� �������\n"
            "3 - ����� �������\n"
            "4 - ������� �������\n"
            "5 - ������� ������\n"
            "6 - ������ �������������� ���� ��������� ������\n"
            "7 - �������� ������\n"
            "8 - �����\n"
            "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Root = makeTree(Root);
            break;
        case 2:
            cout << "����: ";
            cin >> key;
            cout << "�����: ";
            cin >> text;
            Root = insertElem(Root, key, text);
            break;
        case 3:
            cout << "���� ��� ������: ";
            cin >> key;
            if (Tree* found = search(Root, key))
                cout << "�������: " << found->text << endl;
            else
                cout << "�� �������" << endl;
            break;
        case 4:
            cout << "���� ��� ��������: ";
            cin >> key;
            Root = delet(Root, key);
            break;
        case 5:
            if (Root) {
                cout << "\n������:\n";
                view(Root);
            }
            else {
                cout << "������ �����" << endl;
            }
            break;
        case 6:
            cout << "������� �������������� ������: " << dop_1(Root) << endl;
            break;
        case 7:
            delAll(Root);
            cout << "������ �������" << endl;
            break;
        case 8:
            delAll(Root);
            return 0;
        default:
            cout << "�������� �����" << endl;
        }
    }
}

Tree* makeTree(Tree* Root) {
    int key;
    string text;
    cout << "��� ���������� ����� ������� ������������� ����\n";

    if (!Root) {
        cout << "���� �����: ";
        cin >> key;
        if (key < 0) return nullptr;
        cout << "����� �����: ";
        cin >> text;
        Root = list(key, text);
    }

    while (true) {
        cout << "����: ";
        cin >> key;
        if (key < 0) break;
        cout << "�����: ";
        cin >> text;
        Root = insertElem(Root, key, text);
    }
    return Root;
}

Tree* list(int key, const string& text) {
    Tree* node = new Tree;
    node->key = key;
    node->text = text.substr(0, 4);
    node->Left = node->Right = nullptr;
    return node;
}

Tree* insertElem(Tree* root, int key, const string& text) {
    if (!root) return list(key, text);

    Tree* current = root;
    Tree* parent = nullptr;

    while (current) {
        parent = current;
        if (key == current->key) {
            cout << "���� ��� ����������" << endl;
            return root;
        }
        current = (key < current->key) ? current->Left : current->Right;
    }

    if (key < parent->key)
        parent->Left = list(key, text);
    else
        parent->Right = list(key, text);

    return root;
}

Tree* delet(Tree* root, int key) {
    if (!root) return nullptr;

    if (key < root->key) {
        root->Left = delet(root->Left, key);
    }
    else if (key > root->key) {
        root->Right = delet(root->Right, key);
    }
    else {
        if (!root->Left) {
            Tree* temp = root->Right;
            delete root;
            return temp;
        }
        else if (!root->Right) {
            Tree* temp = root->Left;
            delete root;
            return temp;
        }

        Tree* temp = root->Right;
        while (temp->Left) temp = temp->Left;
        root->key = temp->key;
        root->text = temp->text;
        root->Right = delet(root->Right, temp->key);
    }
    return root;
}

Tree* search(Tree* root, int key) {
    if (!root || root->key == key) return root;
    return (key < root->key) ? search(root->Left, key) : search(root->Right, key);
}

int myVar(Tree* r) {
    if (!r) return 0;
    int count = (r->key % 2 == 0) ? 1 : 0;
    return count + myVar(r->Left) + myVar(r->Right);
}

void view(Tree* root, int level) {
    if (root) {
        view(root->Right, level + 1);
        for (int i = 0; i < level; i++) cout << "    ";
        cout << root->key << " (" << root->text << ")\n";
        view(root->Left, level + 1);
    }
}

void delAll(Tree*& root) {
    if (root) {
        delAll(root->Left);
        delAll(root->Right);
        delete root;
        root = nullptr;
    }
}

int sumKeys(Tree* root) {
    if (!root) return 0;
    return root->key + sumKeys(root->Left) + sumKeys(root->Right);
}

int sumNodes(Tree* root) {
    if (!root) return 0;
    return 1 + sumNodes(root->Left) + sumNodes(root->Right);
}

double dop_1(Tree* root) {
    if (!root) return 0.0; 
    int sum = sumKeys(root);
    int count = sumNodes(root);
    return static_cast<double>(sum) / count;
}