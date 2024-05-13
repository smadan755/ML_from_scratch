#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double train[][2] = {   // Basic model
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
};

#define train_count (sizeof(train)/sizeof(train[0]))

double rand_double(void) {
    return (double) rand() / (double) RAND_MAX;
}

double cost(double w) {
    double result = 0;
    for (size_t i = 0; i < train_count; i++) {
        double x = train[i][0];
        double y = x * w;
        double d = y - train[i][1];
        result += d * d;
    }
    return result / train_count;
}

int main() {
    srand(time(NULL));
    double w = rand_double() * 10.0; // Some unknown weight

    double eps = 1e-3;
    double rate = 1e-3;

    for (size_t i = 0; i < 500; i++) {
        double dcost = (cost(w + eps) - cost(w)) / eps;
        w -= rate * dcost;
        printf("cost = %f, w = %f\n", cost(w), w);
    }

    printf("-------------------------------\n");

    printf("%f\n", w);

    return 0;
}
