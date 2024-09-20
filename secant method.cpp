
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Function whose root we are trying to find
double f(double x) {
    return 9*x * x - 4*x+11;  // Example: f(x) = x^2 - 4
}

int main() {


    double x0, x1, tolerance;
    int maxIterations;

    // Initial guesses
    cout << "Enter first initial guess (x0): ";
    cin >> x0;

    cout << "Enter second initial guess (x1): ";
    cin >> x1;

    // Tolerance level
    cout << "Enter tolerance: ";
    cin >> tolerance;



    cout << fixed << setprecision(6);

    // Secant Method Iteration
    for (int i = 1; i <= 20; ++i) {
        double f_x0 = f(x0);
        double f_x1 = f(x1);

        // Check if f(x1) and f(x0) are the same to avoid division by zero
        if (f_x1 == f_x0) {
            cout << "f(x1) and f(x0) are equal. Stopping computation to avoid division by zero." << endl;
            break;
        }

        // Secant method formula: x2 = x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0))
        double x2 = x1 - (f_x1 * (x1 - x0)) / (f_x1 - f_x0);

        // Print iteration details
       // cout << "Iteration " << i << ": x = " << x2 << ", f(x1) = " << f_x1 << ", |x2 - x1| = " << fabs(x2 - x1) << endl;
cout<<fabs(x2 - x1) << endl;
        // Check for convergence
        if (fabs(x2 - x1) < tolerance) {
            //cout << "Converged to " << x2 << " after " << i << " iterations." << endl;
            break;
        }

        // Update x0 and x1 for the next iteration
        x0 = x1;
        x1 = x2;
    }

    return 0;
}
