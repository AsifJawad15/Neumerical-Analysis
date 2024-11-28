#include <iostream>
#include <iomanip>
#include <algorithm> // for std::swap
using namespace std;

// Function to swap rows of a 4x4 matrix and a constants vector
void swapRows(double matrix[4][4], double constants[4], int row1, int row2) {
    for (int i = 0; i < 4; ++i)
        swap(matrix[row1][i], matrix[row2][i]);
    swap(constants[row1], constants[row2]);
}

int main() {
    // Input: 4x4 matrix A and vector b
    double A[4][4];
    double b[4];

    cout << "Enter coefficients of the 4x4 matrix (row-wise):" << endl;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> A[i][j];

    cout << "Enter constants (b1, b2, b3, b4):" << endl;
    for (int i = 0; i < 4; i++)
        cin >> b[i];

    // Pivoting if A[0][0] is zero
    if (A[0][0] == 0) {
        for (int i = 1; i < 4; ++i) {
            if (A[i][0] != 0) {
                swapRows(A, b, 0, i);
                break;
            }
        }
    }

    // Step 1: Compute U
    double u11 = A[0][0];
    double u12 = A[0][1];
    double u13 = A[0][2];
    double u14 = A[0][3];

    double l21 = A[1][0] / u11;
    double u22 = A[1][1] - l21 * u12;
    double u23 = A[1][2] - l21 * u13;
    double u24 = A[1][3] - l21 * u14;

    double l31 = A[2][0] / u11;
    double l32 = (A[2][1] - l31 * u12) / u22;
    double u33 = A[2][2] - l31 * u13 - l32 * u23;
    double u34 = A[2][3] - l31 * u14 - l32 * u24;

    double l41 = A[3][0] / u11;
    double l42 = (A[3][1] - l41 * u12) / u22;
    double l43 = (A[3][2] - l41 * u13 - l42 * u23) / u33;
    double u44 = A[3][3] - l41 * u14 - l42 * u24 - l43 * u34;

    // Step 2: Compute L
    double l11 = 1, l22 = 1, l33 = 1, l44 = 1;

    // Step 3: Forward substitution (L * y = b)
    double y1 = b[0];
    double y2 = b[1] - l21 * y1;
    double y3 = b[2] - l31 * y1 - l32 * y2;
    double y4 = b[3] - l41 * y1 - l42 * y2 - l43 * y3;

    // Step 4: Back substitution (U * x = y)
    double x4 = y4 / u44;
    double x3 = (y3 - u34 * x4) / u33;
    double x2 = (y2 - u23 * x3 - u24 * x4) / u22;
    double x1 = (y1 - u12 * x2 - u13 * x3 - u14 * x4) / u11;

    // Output results
    cout << "\nL Matrix:" << endl;
    cout << setw(10) << l11 << setw(10) << 0 << setw(10) << 0 << setw(10) << 0 << endl;
    cout << setw(10) << l21 << setw(10) << l22 << setw(10) << 0 << setw(10) << 0 << endl;
    cout << setw(10) << l31 << setw(10) << l32 << setw(10) << l33 << setw(10) << 0 << endl;
    cout << setw(10) << l41 << setw(10) << l42 << setw(10) << l43 << setw(10) << l44 << endl;

    cout << "\nU Matrix:" << endl;
    cout << setw(10) << u11 << setw(10) << u12 << setw(10) << u13 << setw(10) << u14 << endl;
    cout << setw(10) << 0 << setw(10) << u22 << setw(10) << u23 << setw(10) << u24 << endl;
    cout << setw(10) << 0 << setw(10) << 0 << setw(10) << u33 << setw(10) << u34 << endl;
    cout << setw(10) << 0 << setw(10) << 0 << setw(10) << 0 << setw(10) << u44 << endl;

    cout << "\nSolution:" << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "x3 = " << x3 << endl;
    cout << "x4 = " << x4 << endl;

    return 0;
}
