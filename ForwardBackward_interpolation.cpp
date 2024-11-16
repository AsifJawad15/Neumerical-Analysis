#include <iostream>
#include <vector>
#include <iomanip> // For setting precision
using namespace std;

// Function to calculate factorial
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Function to calculate the difference table
void calculateDifferenceTable(vector<vector<double>>& diffTable, const vector<double>& y) {
    int n = y.size();
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diffTable[i][j] = diffTable[i + 1][j - 1] - diffTable[i][j - 1];
        }
    }
}

// Newton Forward Interpolation
double newtonForward(const vector<double>& x, const vector<vector<double>>& diffTable, double value) {
    int n = x.size();
    double h = x[1] - x[0]; // Assuming equal spacing
    double u = (value - x[0]) / h;
    double result = diffTable[0][0];
    double uProduct = 1;

    for (int i = 1; i < n; i++) {
        uProduct *= (u - (i - 1));
        result += (uProduct * diffTable[0][i]) / factorial(i);
    }

    return result;
}

// Newton Backward Interpolation
double newtonBackward(const vector<double>& x, const vector<vector<double>>& diffTable, double value) {
    int n = x.size();
    double h = x[1] - x[0]; // Assuming equal spacing
    double u = (value - x[n - 1]) / h;
    double result = diffTable[n - 1][0];
    double uProduct = 1;

    for (int i = 1; i < n; i++) {
        uProduct *= (u + (i - 1));
        result += (uProduct * diffTable[n - 1 - i][i]) / factorial(i);
    }

    return result;
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the values of x: ";
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    cout << "Enter the values of y: ";
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    vector<vector<double>> diffTable(n, vector<double>(n, 0));
    calculateDifferenceTable(diffTable, y);

    double value;
    cout << "Enter the value to interpolate: ";
    cin >> value;

    // Determine the middle point
    double middle = x[n / 2];

    double result;
    if (value <= middle) {
        // Use Newton Forward Interpolation
        result = newtonForward(x, diffTable, value);
        cout << "Using Newton Forward Interpolation..." << endl;
    } else {
        // Use Newton Backward Interpolation
        result = newtonBackward(x, diffTable, value);
        cout << "Using Newton Backward Interpolation..." << endl;
    }

    cout << fixed << setprecision(6);
    cout << "Interpolated value at " << value << " is: " << result << endl;

    return 0;
}
