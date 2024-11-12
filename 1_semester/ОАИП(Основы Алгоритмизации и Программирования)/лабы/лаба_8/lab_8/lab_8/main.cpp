#include <stdio.h>
#include <cmath>
void main() {
    float q, t = 2, sum = 0;
    double x[6] = { 6,5,4,3,2,1};
    for (int i = 0; i < 6; i++) {
        sum += ((x[i] + 1) / x[i]);
    }
    q = t + sum;
    printf("Q = %f\n", q);

}
