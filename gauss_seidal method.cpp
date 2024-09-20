#include <bits/stdc++.h>
using namespace std;



#define f1(x, y, z) (85 - 6 * y + z) / 27
#define f2(x, y, z) (72 - 6 * x - 3 * z) / 15
#define f3(x, y, z) (110 - x - y) / 54

int main() {


    float e;
    cin >> e;  // Reading the error tolerance

    float x0 = 0, y0 = 0, z0 = 0, x1, y1, z1, e1, e2, e3;
    int step = 1;

    // Setting up output formatting for alignment
    cout << fixed << setprecision(6);

    // Print the header with column alignment
    cout << setw(5) << "Step" << setw(12) << "x1" << setw(12) << "y1"
         << setw(12) << "z1" << setw(12) << "e1" << setw(12) << "e2" << setw(12) << "e3" << endl;

    do {
        x1 = f1(x0, y0, z0);
        y1 = f2(x1, y0, z0);
        z1 = f3(x1, y1, z0);

        // Calculate errors
        e1 = abs(x1 - x0);
        e2 = abs(y1 - y0);
        e3 = abs(z1 - z0);

        // Print the current step, values, and errors with aligned columns
        cout << setw(5) << step << setw(12) << x1 << setw(12) << y1 << setw(12) << z1
             << setw(12) << e1 << setw(12) << e2 << setw(12) << e3 << endl;

        // Update the old values with new ones for the next iteration
        x0 = x1;
        y0 = y1;
        z0 = z1;
        step++;
    } while (e1 > e || e2 > e || e3 > e);  // Continue until all errors are within the tolerance

    cout << endl << "Solution: x = " << x1 << ", y = " << y1 << ", z = " << z1 << endl;

    return 0;
}
