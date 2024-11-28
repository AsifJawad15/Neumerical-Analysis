#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Straight line y = a + b * x
void straightLineFit(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    double b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double a = (sumY - b * sumX) / n;

    cout << "Straight Line Fit: y = " << a << " + " << b << " * x" << endl;
}

// Parabola y = a + b * x + c * x^2
void parabolaFit(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sumX = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0;
    double sumY = 0, sumXY = 0, sumX2Y = 0;

    for (int i = 0; i < n; i++) {
        double x2 = x[i] * x[i];
        sumX += x[i];
        sumX2 += x2;
        sumX3 += x2 * x[i];
        sumX4 += x2 * x2;
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2Y += x2 * y[i];
    }

    // Solving linear equations using matrix approach
    double det = n * (sumX2 * sumX4 - sumX3 * sumX3)
               - sumX * (sumX * sumX4 - sumX2 * sumX3)
               + sumX2 * (sumX * sumX3 - sumX2 * sumX2);

    double a = (sumY * (sumX2 * sumX4 - sumX3 * sumX3)
              - sumX * (sumXY * sumX4 - sumX3 * sumX2Y)
              + sumX2 * (sumXY * sumX3 - sumX2Y * sumX2)) / det;

    double b = (n * (sumXY * sumX4 - sumX3 * sumX2Y)
              - sumY * (sumX * sumX4 - sumX2 * sumX3)
              + sumX2 * (sumX * sumX2Y - sumXY * sumX2)) / det;

    double c = (n * (sumX2 * sumX2Y - sumXY * sumX3)
              - sumX * (sumX * sumX2Y - sumXY * sumX2)
              + sumY * (sumX * sumX3 - sumX2 * sumX2)) / det;

    cout << "Parabola Fit: y = " << a << " + " << b << " * x + " << c << " * x^2" << endl;
}

// Exponential curve y = a * b^x
void exponentialFit(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sumX = 0, sumLogY = 0, sumXLogY = 0, sumX2 = 0;

    for (int i = 0; i < n; i++) {
        if (y[i] <= 0) {
            cout << "Error: y values must be positive for exponential fit." << endl;
            return;
        }
        double logY = log(y[i]); // Transform y into log space
        sumX += x[i];
        sumLogY += logY;
        sumXLogY += x[i] * logY;
        sumX2 += x[i] * x[i];
    }

    double bLog = (n * sumXLogY - sumX * sumLogY) / (n * sumX2 - sumX * sumX);
    double aLog = (sumLogY - bLog * sumX) / n;

    double a = exp(aLog);
    double b = exp(bLog);

    cout << "Exponential Fit: y = " << a << " * " << b << "^x" << endl;
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter x values: ";
    for (int i = 0; i < n; i++) cin >> x[i];
    cout << "Enter y values: ";
    for (int i = 0; i < n; i++) cin >> y[i];

    cout << fixed << setprecision(6);

    // Perform curve fitting
    //straightLineFit(x, y);
    parabolaFit(x, y);
     //exponentialFit(x, y);

    return 0;
}
