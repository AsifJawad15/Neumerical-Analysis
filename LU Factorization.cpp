
#include <iostream>
#include <vector>

using namespace std;

void LUFactorization() {
    int n = 5; // Minimum of 5 equations
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> L(n, vector<double>(n, 0));  // Lower triangular matrix
    vector<vector<double>> U(n, vector<double>(n, 0));  // Upper triangular matrix
    vector<double> b(n);  // Right-hand side vector
    vector<double> x(n), y(n);  // Solution vectors

    // Input the coefficients of matrix A
    cout << "Enter the coefficients of a " << n << "x" << n << " matrix A:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    // Input the right-hand side vector b
    cout << "Enter the right-hand side vector b:\n";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    // LU decomposition
    for (int i = 0; i < n; i++) {
        // Upper triangular matrix U
        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        // Lower triangular matrix L
        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1;  // Diagonal as 1
            else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }





    // Forward substitution: Solve L * y = b
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }

    // Backward substitution: Solve U * x = y
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    // Display the solution
    cout << "\nSolution (x values):\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
}

int main() {
    LUFactorization();
    return 0;
}
