#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to evaluate the polynomial at a given point x
double evaluatePolynomial(const vector<double>& coeffs, double x) {
    double result = 0;
    int degree = coeffs.size() - 1;
    for (int i = 0; i <= degree; ++i) {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

int main() {
    int degree;

    // User input for polynomial degree
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1);

    // User input for coefficients
    cout << "Enter the coefficients of the polynomial (from highest degree to constant term):\n";
    for (int i = 0; i <= degree; ++i) {
        cin >> coeffs[i];
    }

    double x0, x1, tolerance;

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
        double f_x0 = evaluatePolynomial(coeffs, x0);
        double f_x1 = evaluatePolynomial(coeffs, x1);

        // Check if f(x1) and f(x0) are the same to avoid division by zero
        if (f_x1 == f_x0) {
            cout << "f(x1) and f(x0) are equal. Stopping computation to avoid division by zero." << endl;
            break;
        }

        // Secant method formula: x2 = x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0))
        double x2 = x1 - (f_x1 * (x1 - x0)) / (f_x1 - f_x0);

        // Print iteration details
        cout << "Iteration " << i << ": x = " << x2
             << ", f(x1) = " << f_x1
             << ", |x2 - x1| = " << fabs(x2 - x1) << endl;

        // Check for convergence
        if (fabs(x2 - x1) < tolerance) {
            cout << "Converged to " << x2 << " after " << i << " iterations." << endl;
            break;
        }

        // Update x0 and x1 for the next iteration
        x0 = x1;
        x1 = x2;
    }

    return 0;
}
