#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
string reverseWord(const string& word) {
    string reversed = word;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}
int main() {
    string sentence;
    cout << "Enter a sentence: ";
    getline(cin, sentence);
    vector<string> words;
    size_t start = 0, end;
    while ((end = sentence.find(' ', start)) != string::npos) {
        words.push_back(sentence.substr(start, end - start));
        start = end + 1;
    }
    words.push_back(sentence.substr(start)); 
    string result = "";

    // Обрабатываем слова
    for (size_t i = 0; i < words.size(); ++i) {
        if (i % 2 == 1) {
            result += reverseWord(words[i]) + " ";
        }
    }
    cout << "Edited sentence: " << result << endl;
    return 0;
}
