#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Define the function f(x, y) = dy/dx
double f(double x, double y, const vector<double>& coeffs) {
    double result = 0.0;
    int degree = coeffs.size() - 1;

    // Calculate the value of the polynomial
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, degree - i);
    }

    return result;
}

// Runge-Kutta 4th Order Method
void rungeKutta(double x0, double y0, double x, double h, const vector<double>& coeffs) {
    int n = (int)((x - x0) / h);  // Number of steps
    double k1, k2, k3, k4;       // Slopes
    double y = y0;               // Initial value of y

    cout << fixed << setprecision(6);
    cout << setw(10) << "x" << setw(15) << "y" << endl;
    cout << setw(10) << x0 << setw(15) << y0 << endl;

    for (int i = 0; i < n; i++) {
        k1 = h * f(x0, y, coeffs);
        k2 = h * f(x0 + h / 2.0, y + k1 / 2.0, coeffs);
        k3 = h * f(x0 + h / 2.0, y + k2 / 2.0, coeffs);
        k4 = h * f(x0 + h, y + k3, coeffs);

        // Update y for the next step
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;

        // Update x for the next step
        x0 += h;

        // Print current values
        cout << setw(10) << x0 << setw(15) << y << endl;
    }

    cout << "\nThe approximate value of y at x = " << x << " is " << y << endl;
}

int main() {
    double x0, y0, x, h;
    int degree;

    // Input the degree of the polynomial
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    // Input the coefficients of the polynomial
    vector<double> coeffs(degree + 1);
    cout << "Enter the coefficients of the polynomial (from highest to lowest degree):\n";
    for (int i = 0; i <= degree; i++) {
        cout << "Coefficient of x^" << (degree - i) << ": ";
        cin >> coeffs[i];
    }

    // Input initial conditions and step size
    cout << "Enter initial value of x (x0): ";
    cin >> x0;
    cout << "Enter initial value of y (y0): ";
    cin >> y0;
    cout << "Enter the value of x at which to compute y: ";
    cin >> x;
    cout << "Enter the step size (h): ";
    cin >> h;

    // Call Runge-Kutta method
    rungeKutta(x0, y0, x, h, coeffs);

    return 0;
}
