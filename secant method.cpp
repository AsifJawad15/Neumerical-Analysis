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

// Synthetic division to deflate the polynomial after finding a root
vector<double> syntheticDivision(const vector<double>& coeffs, double root) {
    int degree = coeffs.size() - 1;
    vector<double> newCoeffs(degree);

    newCoeffs[0] = coeffs[0]; // The leading coefficient remains the same
    for (int i = 1; i < degree; ++i) {
        newCoeffs[i] = coeffs[i] + newCoeffs[i - 1] * root;
    }

    return newCoeffs;
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

    double tolerance;
    cout << "Enter tolerance: ";
    cin >> tolerance;

    vector<double> roots;
    cout << fixed << setprecision(6);

    while (coeffs.size() > 1) { // Keep finding roots until the polynomial is deflated to a constant
        double x0, x1;
        cout << "Enter first initial guess (x0): ";
        cin >> x0;

        cout << "Enter second initial guess (x1): ";
        cin >> x1;

        bool converged = false;

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

            // Check for convergence
            if (fabs(x2 - x1) < tolerance) {
                cout << "Root found: " << x2 << endl;
                roots.push_back(x2);
                coeffs = syntheticDivision(coeffs, x2);
                converged = true;
                break;
            }

            // Update x0 and x1 for the next iteration
            x0 = x1;
            x1 = x2;
        }

        if (!converged) {
            cout << "Failed to converge to a root." << endl;
            break;
        }
    }

    // Output all roots
    cout << "All roots found: ";
    for (double root : roots) {
        cout << root << " ";
    }
    cout << endl;

    return 0;
}
