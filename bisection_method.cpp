#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return x * x * x - x - 1; // Function x^2 - 6x - 12
}

double bisection(double a, double b, double tolerance) {
    if (f(a) * f(b) >= 0) {
        cout << "The function must have different signs at a and b." << endl;
        return -1;
    }

    double c = a;
    double prev_c = c;
    int iteration = 0;

    cout << "Iteration\tc (root estimate)\tError" << endl;

    while ((b - a) >= tolerance) {
        c = (a + b) / 2; // Bisection step: midpoint of [a, b]

        double error = fabs(c - prev_c); // Calculate the error
        cout << iteration++ << "\t\t" << setprecision(6) << c << "\t\t" << error << endl;

        if (f(c) == 0.0 || fabs(b - a) < tolerance) {
            break; // Found root or interval small enough
        }

        // Check which side of the interval contains the root
        if (f(c) * f(a) < 0) {
            b = c; // Root is in the left half
        } else {
            a = c; // Root is in the right half
        }

        prev_c = c; // Update the previous midpoint

        if (iteration >= 20) { // Break after 20 iterations for demonstration
            break;
        }
    }

    return c;
}

int main() {
    double a = 0, b = 10; // Initial interval
    double tolerance = 1e-5; // Adjusted tolerance for around 20 iterations

    double root = bisection(a, b, tolerance);
    if (root != -1) {
        cout << "The root is: " << setprecision(6) << root << endl;
    }
    return 0;
}
