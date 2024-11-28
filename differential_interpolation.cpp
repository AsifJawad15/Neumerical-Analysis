#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to interpolate y-value at a given x using linear interpolation
double interpolate(const vector<double>& x, const vector<double>& y, double value) {
    int n = x.size();
    for (int i = 0; i < n - 1; i++) {
        if (value >= x[i] && value <= x[i + 1]) {
            return y[i] + (y[i + 1] - y[i]) * (value - x[i]) / (x[i + 1] - x[i]);
        }
    }
    return -1; // Indicating out-of-bound value
}

// Function to calculate first-order derivative
double firstOrderDerivative(const vector<double>& x, const vector<double>& y, double value) {
    double h = x[1] - x[0]; // Assuming uniform spacing

    // Interpolating y-values if needed
    double y1 = interpolate(x, y, value - h); // f(x-h)
    double y2 = interpolate(x, y, value + h); // f(x+h)

    if (y1 == -1 || y2 == -1) {
        cout << "Error: Value out of interpolation bounds for first-order derivative!" << endl;
        return -1;
    }

    return (y2 - y1) / (2 * h);
}

// Function to calculate second-order derivative
double secondOrderDerivative(const vector<double>& x, const vector<double>& y, double value) {
    double h = x[1] - x[0]; // Assuming uniform spacing

    // Interpolating y-values if needed
    double y1 = interpolate(x, y, value - h); // f(x-h)
    double y2 = interpolate(x, y, value);     // f(x)
    double y3 = interpolate(x, y, value + h); // f(x+h)

    if (y1 == -1 || y2 == -1 || y3 == -1) {
        cout << "Error: Value out of interpolation bounds for second-order derivative!" << endl;
        return -1;
    }

    return (y3 - 2 * y2 + y1) / (h * h);
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the x values: ";
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    cout << "Enter the y values: ";
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    double value;
    cout << "Enter the value to find the derivatives at: ";
    cin >> value;

    double firstDerivative = firstOrderDerivative(x, y, value);
    double secondDerivative = secondOrderDerivative(x, y, value);

    cout << fixed << setprecision(6);
    if (firstDerivative != -1) {
        cout << "First-order derivative at " << value << ": " << firstDerivative << endl;
    }
    if (secondDerivative != -1) {
        cout << "Second-order derivative at " << value << ": " << secondDerivative << endl;
    }

    return 0;
}
