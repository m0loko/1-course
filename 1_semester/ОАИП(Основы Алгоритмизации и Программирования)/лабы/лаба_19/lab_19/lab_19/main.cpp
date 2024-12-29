#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>
#define SIZE 5

void pF(const char* inputFile, const char* outputFile) {
    FILE* fInput, * fOutput;
    errno_t errInput, errOutput;

    errInput = fopen_s(&fInput, inputFile, "r");
    errOutput = fopen_s(&fOutput, outputFile, "w");

    if (errInput != 0 || errOutput != 0) {
        perror("Ошибка открытия файлов");
        exit(EXIT_FAILURE);
    }

    int numbers[1000];
    int posBuffer[1000], negBuffer[1000];
    int totalNumbers = 0, posCount = 0, negCount = 0;

    while (fscanf_s(fInput, "%d", &numbers[totalNumbers]) == 1) {
        if (numbers[totalNumbers] > 0) {
            posBuffer[posCount++] = numbers[totalNumbers];
        }
        else {
            negBuffer[negCount++] = numbers[totalNumbers];
        }
        totalNumbers++;
    }
    int i = 0, j = 0;
    while (i < posCount || j < negCount) {
        for (int k = 0; k < SIZE && i < posCount; k++) {
            fprintf(fOutput, "%d ", posBuffer[i++]);
        }
        for (int k = 0; k <SIZE && j < negCount; k++) {
            fprintf(fOutput, "%d ", negBuffer[j++]);
        }
    }
    fclose(fInput);
    fclose(fOutput);
    printf("Файл %s успешно создан.\n", outputFile);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const char* inputFile = "f.txt";
    const char* outputFile = "g.txt";
    pF(inputFile, outputFile);
    return 0;
}
