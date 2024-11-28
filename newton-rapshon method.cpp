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

// Perform synthetic division
vector<double> syntheticDivision(const vector<double>& coeffs, double root) {
    vector<double> newCoeffs(coeffs.size() - 1);
    newCoeffs[0] = coeffs[0];
    for (size_t i = 1; i < newCoeffs.size(); ++i) {
        newCoeffs[i] = coeffs[i] + root * newCoeffs[i - 1];
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
    cout << "Enter the coefficients of the polynomial (from highest to lowest degree):\n";
    for (int i = 0; i <= degree; ++i) {
        cin >> coeffs[i];
    }

    double tolerance;
    cout << "Enter tolerance: ";
    cin >> tolerance;

    cout << fixed << setprecision(6);

    vector<double> roots;

    while (coeffs.size() > 1) {
        double x0;
        cout << "Enter initial guess: ";
        cin >> x0;

        vector<double> derivCoeffs = derivative(coeffs);
        bool converged = false;
        for (int i = 1; i <= 20; ++i) {
            double f_x0 = evaluatePolynomial(coeffs, x0);
            double df_x0 = evaluatePolynomial(derivCoeffs, x0);

            // Check if derivative is zero (to avoid division by zero)
            if (df_x0 == 0) {
                cout << "Derivative is zero. Stopping computation for this guess." << endl;
                break;
            }

            // Newton-Raphson formula: x1 = x0 - f(x0) / f'(x0)
            double x1 = x0 - f_x0 / df_x0;

            // Check for convergence
            if (fabs(x1 - x0) < tolerance) {
                roots.push_back(x1);
                cout << "Root found: " << x1 << " after " << i << " iterations." << endl;
                coeffs = syntheticDivision(coeffs, x1);
                converged = true;
                break;
            }

            // Update x0 for the next iteration
            x0 = x1;
        }

        if (!converged) {
            cout << "Failed to converge for the current initial guess." << endl;
            break;
        }
    }

    // Display all roots
    cout << "\nAll roots found:" << endl;
    for (const auto& root : roots) {
        cout << root << endl;
    }

    return 0;
}
