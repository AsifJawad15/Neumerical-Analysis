#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

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
    return (a + b) / 2;  // Return the midpoint as an approximation
}

int main()
{
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1);  // Coefficients of the polynomial
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
    double tolerance=0.0000001;


    // Step size to search for potential root intervals
    double step = 0.01;  // Smaller step size to improve precision and capture roots accurately

    // Loop over the interval in small steps to find potential roots
    vector<double> roots;
    for (double i = a; i < b; i += step)
    {
        double f_i = evaluatePolynomial(coeffs, i);
        double f_next = evaluatePolynomial(coeffs, i + step);

        // If there's a sign change between f(i) and f(i + step), there's a root in this interval
        if (f_i * f_next < 0)
        {
            double root = bisectionMethod(coeffs, i, i + step, tolerance);
            roots.push_back(root);
        }
    }

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
            cout << "There might be more roots outside this interval, or consider increasing the range(but this may slow the program potentially!!)\n";
        }
    }
    else
    {
        cout << "No roots found in the given interval.\n";
    }

    return 0;
}
