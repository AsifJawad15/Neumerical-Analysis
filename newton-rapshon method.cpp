#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Evaluate the polynomial at x
double evaluatePolynomial(const vector<double>& coeffs, double x) {
    double result = 0;
    int degree = coeffs.size() - 1;
    for (int i = 0; i <= degree; ++i) {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

// Derivative of the polynomial
vector<double> derivative(const vector<double>& coeffs) {
    vector<double> derivCoeffs;
    int degree = coeffs.size() - 1;
    for (int i = 0; i < degree; ++i) {
        derivCoeffs.push_back(coeffs[i] * (degree - i));
    }
    return derivCoeffs;
}

int main() {
    int degree;

    // User input for polynomial degree
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1);

    // User input for coefficients
    cout << "Enter the coefficients of the polynomial (from highest to lowest degree):\n";
    for (int i = 0; i <= degree; ++i) {
        cin >> coeffs[i];
    }

    // Calculate the derivative coefficients
    vector<double> derivCoeffs = derivative(coeffs);

    double x0, tolerance;

    // User input for initial guess and tolerance
    cout << "Enter initial guess: ";
    cin >> x0;

    cout << "Enter tolerance: ";
    cin >> tolerance;

    cout << fixed << setprecision(6);

    // Newton-Raphson Iteration
    for (int i = 1; i <= 20; ++i) {
        double f_x0 = evaluatePolynomial(coeffs, x0);
        double df_x0 = evaluatePolynomial(derivCoeffs, x0);

        // Check if derivative is zero (to avoid division by zero)
        if (df_x0 == 0) {
            cout << "Derivative is zero. Stopping computation." << endl;
            break;
        }

        // Newton-Raphson formula: x1 = x0 - f(x0) / f'(x0)
        double x1 = x0 - f_x0 / df_x0;

        // Print iteration details
        cout << "Iteration " << i << ": x = " << x1
             << ", f(x) = " << f_x0
             << ", |x1 - x0| = " << fabs(x1 - x0) << endl;

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
