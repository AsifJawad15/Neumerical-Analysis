#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // For sort and unique
#include <iomanip>   // For fixed and setprecision

using namespace std;

// Function to evaluate the polynomial at a given point x
double evaluatePolynomial(const vector<double>& coeffs, double x) {
    double result = 0;
    int degree = coeffs.size() - 1;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

// False Position (Regula Falsi) Method to find a root in a given interval [a, b]
double falsePositionMethod(const vector<double>& coeffs, double a, double b, double tolerance) {
    double fa = evaluatePolynomial(coeffs, a);
    double fb = evaluatePolynomial(coeffs, b);
    double c; // This will store the root approximation

    if (fa * fb >= 0) {
        return NAN; // No sign change, return NAN
    }

    while (fabs(b - a) >= tolerance) {
        // Calculate the position using the false position formula
        c = (a * fb - b * fa) / (fb - fa);
        double fc = evaluatePolynomial(coeffs, c);

        // Check if c is a root
        if (fabs(fc) < tolerance)
            return c;

        // Update interval
        if (fa * fc < 0) {
            b = c;
            fb = fc; // Update f(b)
        } else {
            a = c;
            fa = fc; // Update f(a)
        }
    }

    return c; // Return the root approximation
}

int main() {
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1); // Coefficients of the polynomial
    cout << "Enter the coefficients (from highest degree to constant term):\n";
    for (int i = 0; i <= degree; i++) {
        cin >> coeffs[i];
    }

    double a, b;
    cout << "Enter the interval [a, b] to search for roots:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;

    double tolerance = 1e-7;
    double step = 0.01; // Step size for searching intervals

    // Store unique roots
    vector<double> roots;

    // Search for roots
    for (double x = a; x <= b; x += step) {
        double fx = evaluatePolynomial(coeffs, x);
        if (fabs(fx) < tolerance) {
            // Directly identify a root if it's close to zero
            roots.push_back(x);
        } else {
            // Check for a sign change in the interval [x, x + step]
            double next_x = x + step;
            double f_next = evaluatePolynomial(coeffs, next_x);
            if (fx * f_next < 0) {
                double root = falsePositionMethod(coeffs, x, next_x, tolerance);
                if (!isnan(root)) {
                    roots.push_back(root);
                }
            }
        }
    }

    // Remove duplicate roots (due to multiple detections near the same root)
    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end(), [&](double a, double b) {
        return fabs(a - b) < tolerance;
    }), roots.end());

    // Output the roots
    if (!roots.empty()) {
        cout << "Roots found in the interval [" << a << ", " << b << "]:\n";
        for (double root : roots) {
            cout << fixed << setprecision(6) << root << endl;
        }
    } else {
        cout << "No roots found in the given interval.\n";
    }

    return 0;
}
