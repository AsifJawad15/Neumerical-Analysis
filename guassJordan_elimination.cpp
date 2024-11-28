
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to perform Gauss-Jordan Elimination and calculate the inverse of a matrix
bool gaussJordanInverse(vector<vector<double>>& matrix, vector<vector<double>>& inverse) {
    int n = matrix.size();
    inverse.assign(n, vector<double>(n, 0.0));

    // Initialize inverse as an identity matrix
    for (int i = 0; i < n; ++i) {
        inverse[i][i] = 1.0;
    }

    for (int col = 0; col < n; ++col) {
        // Find the pivot row
        int pivotRow = col;
        for (int i = col + 1; i < n; ++i) {
            if (fabs(matrix[i][col]) > fabs(matrix[pivotRow][col])) {
                pivotRow = i;
            }
        }

        // Check if matrix is singular
        if (fabs(matrix[pivotRow][col]) < 1e-9) {
            return false; // Matrix is singular, no inverse
        }

        // Swap rows in matrix and inverse
        swap(matrix[col], matrix[pivotRow]);
        swap(inverse[col], inverse[pivotRow]);

        // Normalize the pivot row
        double pivot = matrix[col][col];
        for (int j = 0; j < n; ++j) {
            matrix[col][j] /= pivot;
            inverse[col][j] /= pivot;
        }

        // Eliminate other rows
        for (int i = 0; i < n; ++i) {
            if (i != col) {
                double factor = matrix[i][col];
                for (int j = 0; j < n; ++j) {
                    matrix[i][j] -= factor * matrix[col][j];
                    inverse[i][j] -= factor * inverse[col][j];
                }
            }
        }
    }

    return true;
}

// Function to multiply two matrices
vector<double> multiplyMatrix(const vector<vector<double>>& matrix, const vector<double>& vec) {
    int n = matrix.size();
    vector<double> result(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

int main() {
    int n;
    cout << "Enter the number of equations (n): ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    vector<double> constants(n);

    cout << "Enter the coefficients of the matrix (row by row):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Enter the constants vector:\n";
    for (int i = 0; i < n; ++i) {
        cin >> constants[i];
    }

    vector<vector<double>> inverse;

    if (!gaussJordanInverse(matrix, inverse)) {
        cout << "The matrix is singular and cannot be inverted.\n";
        return 1;
    }

    cout << "The inverse of the matrix is:\n";
    for (const auto& row : inverse) {
        for (double val : row) {
            cout << setw(10) << fixed << setprecision(5) << val << " ";
        }
        cout << "\n";
    }

    // Solve the system of equations
    vector<double> solution = multiplyMatrix(inverse, constants);

    cout << "The solution to the system of equations is:\n";
    for (double x : solution) {
        cout << setw(10) << fixed << setprecision(5) << x << "\n";
    }

    return 0;
}
