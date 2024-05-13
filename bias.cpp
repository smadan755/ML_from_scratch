#include <iostream>
#include <cstdlib>
#include <ctime>


using std::cout;
using std::endl;

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

double cost(double w, double b) {
    double result = 0;
    for (size_t i = 0; i < train_count; i++) {
        double x = train[i][0];
        double y = x * w + b;
        double d = y - train[i][1];
        result += d * d;
    }
    return result / train_count;
}

/* x1, x2, x3, x4 ...., b

   w1, w2, w3, w4 ...., b


   y = x1*w1 + x2*w2 + x3*w3 + x4*w4 + ..... + b

*/




int main() {
    srand(time(NULL));
    double w = rand_double() * 10.0; // Some unknown weight

    double b = rand_double() * 5.0;

    double eps = 1e-3;
    double rate = 1e-3;

    for (size_t i = 0; i < 500; i++) {
        double dw = (cost(w + eps, b) - cost(w,b)) / eps;
        double db = (cost(w, b + eps)  - cost(w,b)) / eps;

        w -= rate*dw;

        b -= rate*db;

        cout << "cost = " << cost(w,b) << " w = " << w << " b = " << b << endl;
    }

    printf("-------------------------------\n");

    cout << " w = " << w << " b = " << b << endl;
    return 0;
}