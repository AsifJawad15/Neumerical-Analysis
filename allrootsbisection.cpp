#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm> // For sort and unique

using namespace std;

// Function to evaluate the polynomial at a given point x
double evaluatePolynomial(const vector<double>& coeffs, double x)
{
    double result = 0;
    int degree = coeffs.size() - 1;
    for (int i = 0; i <= degree; i++)
    {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

// Bisection Method to find a root in a given interval [a, b]
double bisectionMethod(const vector<double>& coeffs, double a, double b, double tolerance)
{
    double mid;
    while ((b - a) >= tolerance)
    {
        mid = (a + b) / 2;
        double f_a = evaluatePolynomial(coeffs, a);
        double f_mid = evaluatePolynomial(coeffs, mid);

        // Check if midpoint is a root
        if (fabs(f_mid) < tolerance)
            return mid;

        // Decide the side to repeat the bisection
        if (f_a * f_mid < 0)
            b = mid;
        else
            a = mid;
    }
    return (a + b) / 2; // Return the midpoint as an approximation
}

int main()
{
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1); // Coefficients of the polynomial
    cout << "Enter the coefficients (from highest degree to constant term):\n";
    for (int i = 0; i <= degree; i++)
    {
        cin >> coeffs[i];
    }

    double a, b;
    cout << "Enter the interval [a, b] to search for roots:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    double tolerance = 0.0000001;

    // Reduced step size for better accuracy
    double step = 0.001;

    // Loop over the interval in small steps to find potential roots
    vector<double> roots;
    for (double i = a; i < b; i += step)
    {
        double f_i = evaluatePolynomial(coeffs, i);
        double f_next = evaluatePolynomial(coeffs, i + step);

        // Check for roots at boundaries or sign change
        if (fabs(f_i) < tolerance) // Check if f(i) is approximately zero
        {
            roots.push_back(i);
        }
        else if (f_i * f_next < 0) // Check for sign change
        {
            double root = bisectionMethod(coeffs, i, i + step, tolerance);
            roots.push_back(root);
        }
    }

    // Remove duplicate roots
    sort(roots.begin(), roots.end()); // Sort roots
    roots.erase(unique(roots.begin(), roots.end(),
        [tolerance](double a, double b) { return fabs(a - b) < tolerance; }),
        roots.end()); // Remove duplicates

    // Output the found roots
    if (!roots.empty())
    {
        cout << "Roots found in the interval [" << a << ", " << b << "]:\n";
        for (double root : roots)
        {
            cout << fixed << setprecision(6) << root << endl;
        }

        // Check if the number of found roots matches the expected number
        if (roots.size() < degree)
        {
            cout << "\nWarning: Not all roots were found in the interval [" << a << ", " << b << "].\n";
            cout << "There might be more roots outside this interval, or consider increasing the range (but this may slow the program potentially!!)\n";
        }
    }
    else
    {
        cout << "No roots found in the given interval.\n";
    }

    return 0;
}
