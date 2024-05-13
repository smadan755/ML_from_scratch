#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// AND gate

using std::cout;
using std::endl;

double train[][3] = {
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1},
};

#define train_count (sizeof(train) / sizeof(train[0]))

double rand_double(void) {
    return (double)rand() / (double)RAND_MAX;
}

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

double cost(double w1, double w2, double b) {
    double result = 0;
    for (size_t i = 0; i < train_count; i++) {
        double x1 = train[i][0];
        double x2 = train[i][1];

        double y = sigmoid(x1 * w1 + x2 * w2 + b);
        double d = y - train[i][2];
        result += d * d;
    }
    return result / train_count;
}


double predict(double x1, double x2, double w1, double w2, double b) {
    return sigmoid(x1 * w1 + x2 * w2 + b);
}

void evaluate(double w1, double w2, double b) {
    cout << "\nEvaluation:\n";
    for (size_t i = 0; i < train_count; i++) {
        double x1 = train[i][0];
        double x2 = train[i][1];
        double expected = train[i][2];
        double output = predict(x1, x2, w1, w2, b);
        cout << "Input: (" << x1 << ", " << x2 << ") ";
        cout << "Predicted: " << output << " ";
        cout << "Expected: " << expected << endl;
    }
}

int main() {
    srand(time(NULL));

    double w1 = rand_double();
    double w2 = rand_double();
    double b = rand_double();
    double eps = 1e-3;
    double rate = 1e-2;

    for (int i = 0; i < 100000; i++) {
        double c = cost(w1, w2, b);
        double dw1 = (cost(w1 + eps, w2, b) - c) / eps;
        double dw2 = (cost(w1, w2 + eps, b) - c) / eps;
        double db = (cost(w1, w2, b + eps) - c) / eps;
        w1 -= rate * dw1;
        w2 -= rate * dw2;
        b -= rate * db;

        if (i % 10000 == 0) {
            cout << "Iteration " << i << ": Cost = " << c << " w1 = " << w1 << " w2 = " << w2 << " b = " << b << endl;
        }
    }

    cout << " w1 = " << w1 << " w2 = " << w2 << " b = " << b << endl;


    evaluate(w1, w2, b);

    return 0;
}