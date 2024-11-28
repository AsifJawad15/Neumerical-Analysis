#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Input: 3x3 matrix A and vector b
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    double b1, b2, b3;

    cout << "Enter coefficients of the 3x3 matrix (row-wise):" << endl;
    cin >> a11 >> a12 >> a13;
    cin >> a21 >> a22 >> a23;
    cin >> a31 >> a32 >> a33;

    cout << "Enter constants (b1, b2, b3):" << endl;
    cin >> b1 >> b2 >> b3;

    // Step 1: Compute U
    double u11 = a11;
    double u12 = a12;
    double u13 = a13;

    double l21 = a21 / u11;
    double u22 = a22 - l21 * u12;
    double u23 = a23 - l21 * u13;

    double l31 = a31 / u11;
    double l32 = (a32 - l31 * u12) / u22;
    double u33 = a33 - l31 * u13 - l32 * u23;

    // Step 2: Compute L
    double l11 = 1, l22 = 1, l33 = 1;

    // Step 3: Forward substitution (L * y = b)
    double y1 = b1;
    double y2 = b2 - l21 * y1;
    double y3 = b3 - l31 * y1 - l32 * y2;

    // Step 4: Back substitution (U * x = y)
    double x3 = y3 / u33;
    double x2 = (y2 - u23 * x3) / u22;
    double x1 = (y1 - u12 * x2 - u13 * x3) / u11;

    // Output results
    cout << "\nL Matrix:" << endl;
    cout << setw(10) << l11 << setw(10) << 0 << setw(10) << 0 << endl;
    cout << setw(10) << l21 << setw(10) << l22 << setw(10) << 0 << endl;
    cout << setw(10) << l31 << setw(10) << l32 << setw(10) << l33 << endl;

    cout << "\nU Matrix:" << endl;
    cout << setw(10) << u11 << setw(10) << u12 << setw(10) << u13 << endl;
    cout << setw(10) << 0 << setw(10) << u22 << setw(10) << u23 << endl;
    cout << setw(10) << 0 << setw(10) << 0 << setw(10) << u33 << endl;

    cout << "\nSolution:" << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "x3 = " << x3 << endl;

    return 0;
}
