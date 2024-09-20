#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Function whose root we are trying to find
double f(double x) {
   9*x*x - 4*x - 11;
}

// Derivative of the function f(x)
double df(double x) {
    return  18 * x - 4;
}
int main() {


    double x0, tolerance;
    int maxIterations;

    // Initial guess
    cout << "Enter initial guess: ";
    cin >> x0;

    // Tolerance level
    cout << "Enter tolerance: ";
    cin >> tolerance;



    cout << fixed << setprecision(6);

    // Newton-Raphson Iteration
    for (int i = 1; i <= 20; ++i) {
        double f_x0 = f(x0);
        double df_x0 = df(x0);

        // Check if derivative is zero (to avoid division by zero)
        if (df_x0 == 0) {
            cout << "Derivative is zero. Stopping computation." << endl;
            break;
        }

        // Newton-Raphson formula: x1 = x0 - f(x0) / f'(x0)
        double x1 = x0 - f_x0 / df_x0;

        // Print iteration details
        cout << "Iteration " << i << ": x = " << x1 << ", f(x) = " << f_x0 << ", |x1 - x0| = " << fabs(x1 - x0) << endl;

        // Check for convergence
        if (fabs(x1 - x0) < tolerance) {
            cout << "Converged to " << x1 << " after " << i << " iterations." << endl;
            break;
        }

        // Update x0 for the next iteration
        x0 = x1;
    }

    return 0;
}


