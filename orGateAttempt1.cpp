#include <iostream>
#include <cstdlib>
#include <ctime>

// OR gate

using std::cout;
using std::endl;

double train[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};

#define train_count (sizeof(train) / sizeof(train[0]))

double rand_double(void) {
    return (double)rand() / (double)RAND_MAX;
}

double cost(double w1, double w2) {
    double result = 0;
    for (size_t i = 0; i < train_count; i++) {
        double x1 = train[i][0];
        double x2 = train[i][1];

        double y = x1 * w1 + x2 * w2;
        double d = y - train[i][2];
        result += d * d;
    }
    return result / train_count;
}

double predict(double x1, double x2, double w1, double w2) {
    return x1 * w1 + x2 * w2;
}

void evaluate(double w1, double w2) {
    cout << "\nEvaluation:\n";
    for (size_t i = 0; i < train_count; i++) {
        double x1 = train[i][0];
        double x2 = train[i][1];
        double expected = train[i][2];
        double output = predict(x1, x2, w1, w2);
        cout << "Input: (" << x1 << ", " << x2 << ") ";
        cout << "Predicted: " << output << " ";
        cout << "Expected: " << expected << endl;
    }
}

int main() {
    srand(time(NULL));

    double w1 = rand_double();
    double w2 = rand_double();
    double eps = 1e-3;
    double rate = 1e-3;

    for (int i = 0; i < 100000; i++) {
        double c = cost(w1, w2);
        double dw1 = (cost(w1 + eps, w2) - c) / eps;
        double dw2 = (cost(w1, w2 + eps) - c) / eps;
        w1 -= rate * dw1;
        w2 -= rate * dw2;

        if (i % 10 == 0) {
            cout << "Iteration " << i << ": Cost = " << c << " w1 = " << w1 << " w2 = " << w2 << endl;
        }
    }

    evaluate(w1, w2);

    return 0;
}



/*

NOTE: THE LIMITATIONS OF A LINEAR MODEL:

Iteration 99990: Cost = 0.0833335 w1 = 0.666333 w2 = 0.666333

Evaluation:
Input: (0, 0) Predicted: 0 Expected: 0
Input: (0, 1) Predicted: 0.666333 Expected: 1
Input: (1, 0) Predicted: 0.666333 Expected: 1
Input: (1, 1) Predicted: 1.33267 Expected: 1

Process finished with exit code 0


even with '100000' iterations, the model could not accurately model the OR gate:

a 'linear' model is not suitable for a 'binary' classification task.

We must, therefore, introduce a 'nonlinear' 'activation function'.





*/
