#include <iostream>
#include <chrono>
#include <vector>
const int VECTOR_SIZE = 1000000000;
void startFor(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
    }
}

void startWhile(const std::vector<int>& vec) {
    size_t i = 0;
    while (i < vec.size()) {
        i++;
    }
}

void startDowhile(const std::vector<int>& vec) {
    size_t i = 0;
    do {
        i++;
    } while (i < vec.size());
}

void startForeach(const std::vector<int>& vec) {
    for (int value : vec) {

    }
}

void startGoto(const std::vector<int>& vec) {
    size_t i = 0;
start:
    if (i < vec.size()) {
        i++;
        goto start;
    }
}
void measureTime(void (*loopFunc)(const std::vector<int>&), const std::vector<int>& vec, const std::string& loopName) {
    auto begin = std::chrono::steady_clock::now();
    loopFunc(vec);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << loopName << " time: " << elapsed_ms.count() << " ms\n";
}
int main() {
    std::vector<int> vec(VECTOR_SIZE, 1);

    measureTime(startFor, vec, "for loop");
    measureTime(startWhile, vec, "while loop");
    measureTime(startDowhile, vec, "do while loop");
    measureTime(startForeach, vec, "foreach loop");
    measureTime(startGoto, vec, "goto loop");

    return 0;
}
