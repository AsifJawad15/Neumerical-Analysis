#include <bits/stdc++.h>
using namespace std;

// Function to calculate the next value of a variable in Jacobi iteration
double calculateNext(const vector<double>& coeffs, const vector<double>& vars, double constant, int index) {
    double sum = constant;  // Start with the constant on the RHS
    for (int i = 0; i < coeffs.size(); ++i) {
        if (i != index) {  // Skip the current variable
            sum -= coeffs[i] * vars[i];
        }
    }
    return sum / coeffs[index];  // Divide by the coefficient of the current variable
}

int main() {
    int n;  // Number of variables
    cout << "Enter the number of variables: ";
    cin >> n;

    vector<vector<double>> coefficients(n, vector<double>(n));
    vector<double> constants(n);

    // Input the coefficients and constants
    cout << "Enter the coefficients and constants for the equations:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Equation " << i + 1 << " (coefficients a" << i + 1 << "1 to a" << i + 1 << n << " and constant b" << i + 1 << "):" << endl;
        for (int j = 0; j < n; ++j) {
            cin >> coefficients[i][j];
        }
        cin >> constants[i];
    }

    double tolerance;
    cout << "Enter error tolerance: ";
    cin >> tolerance;

    vector<double> vars(n, 0.0);  // Initial guesses for the variables
    vector<double> newVars(n);   // Stores the updated variables
    vector<double> errors(n);    // Stores the errors for each variable
    int step = 1;

    // Print the header for the output table
    cout << fixed << setprecision(6);
    cout << setw(5) << "Step";
    for (int i = 1; i <= n; ++i) cout << setw(12) << "x" << i;
    for (int i = 1; i <= n; ++i) cout << setw(12) << "e" << i;
    cout << endl;

    do {
        // Update each variable using the Jacobi formula
        for (int i = 0; i < n; ++i) {
            newVars[i] = calculateNext(coefficients[i], vars, constants[i], i);
            errors[i] = fabs(newVars[i] - vars[i]);  // Calculate the error for the current variable
        }

        // Print the current step, variable values, and errors
        cout << setw(5) << step;
        for (int i = 0; i < n; ++i) cout << setw(12) << newVars[i];
        for (int i = 0; i < n; ++i) cout << setw(12) << errors[i];
        cout << endl;

        vars = newVars;  // Update the old variables for the next iteration
        step++;
    } while (*max_element(errors.begin(), errors.end()) > tolerance);  // Continue until all errors are within the tolerance

    cout << endl << "Solution: ";
    for (int i = 0; i < n; ++i) {
        cout << "x" << i + 1 << " = " << vars[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl;

    return 0;
}
