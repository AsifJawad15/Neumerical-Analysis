#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return x * x * x - x - 1;
}

double falsePosition(double a, double b, double tolerance) {
    if (f(a) * f(b) >= 0) {
        cout << "The function must have different signs at a and b." << endl;
        return -1;
    }

    double c = a;
    double prev_c = c;
    int iteration = 0;

    cout << "Iteration\tc (root estimate)\tError" << endl;

    while (fabs(b - a) >= tolerance) {
        c = b - (f(b) * (b - a)) / (f(b) - f(a));

        double error = fabs(c - prev_c);
        cout << iteration++ << "\t\t" << setprecision(6) << c << "\t\t" << error << endl;

        if (f(c) == 0.0) {
            break;
        }
        else if (f(c) * f(a) < 0) {
            b = c;
        }
        else {
            a = c;
        }

        prev_c = c;

        if (iteration >= 20) {
            break;
        }
    }

    return c;
}

int main() {
    double a = 1, b = 2;
    double tolerance = 1e-3;

    double root = falsePosition(a, b, tolerance);
    if (root != -1) {
        cout << "The root is: " << setprecision(6) << root << endl;
    }
    return 0;
}
