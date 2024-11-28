#include <bits/stdc++.h>
using namespace std;

// Function to perform Gauss-Seidel iterations
void gaussSeidel(const vector<vector<double>>& coefficients, const vector<double>& constants, vector<double>& vars, double tolerance) {
    int n = coefficients.size();  // Number of variables/equations
    vector<double> prevVars(n);   // Store previous variable values
    int step = 1;                 // Iteration counter

    cout << fixed << setprecision(6);
    cout << setw(5) << "Step";
    for (int i = 0; i < n; ++i)
        cout << setw(12) << "x" << i + 1;
    for (int i = 0; i < n; ++i)
        cout << setw(12) << "e" << i + 1;
    cout << endl;

    while (true) {
        bool converged = true;

        // Save the current variable values for error calculation
        prevVars = vars;

        // Perform Gauss-Seidel update
        for (int i = 0; i < n; ++i) {
            double sum = constants[i];
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum -= coefficients[i][j] * vars[j];
                }
            }
            vars[i] = sum / coefficients[i][i];
        }

        // Calculate errors
        vector<double> errors(n);
        for (int i = 0; i < n; ++i) {
            errors[i] = fabs(vars[i] - prevVars[i]);
            if (errors[i] > tolerance) {
                converged = false;
            }
        }

        // Print the current step, values, and errors
        cout << setw(5) << step;
        for (double v : vars)
            cout << setw(12) << v;
        for (double e : errors)
            cout << setw(12) << e;
        cout << endl;

        // Check for convergence
        if (converged)
            break;

        step++;
    }

    // Print the final solution
    cout << endl << "Solution:";
    for (int i = 0; i < n; ++i) {
        cout << " x" << i + 1 << " = " << vars[i];
        if (i != n - 1) cout << ",";
    }
    cout << endl;
}

int main() {
    int n;  // Number of variables/equations
    cout << "Enter the number of variables (or equations): ";
    cin >> n;

    // Input the coefficients and constants for each equation
    vector<vector<double>> coefficients(n, vector<double>(n));
    vector<double> constants(n);
    cout << "Enter the coefficients and constants for each equation:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Equation " << i + 1 << ":\n";
        for (int j = 0; j < n; ++j) {
            cout << "Coefficient a" << i + 1 << j + 1 << ": ";
            cin >> coefficients[i][j];
        }
        cout << "Constant b" << i + 1 << ": ";
        cin >> constants[i];
    }

    double tolerance;
    cout << "Enter the error tolerance: ";
    cin >> tolerance;

    // Initial guesses for the variables
    vector<double> vars(n, 0.0);  // x0, y0, z0...

    // Perform Gauss-Seidel iteration
    gaussSeidel(coefficients, constants, vars, tolerance);

    return 0;
}
