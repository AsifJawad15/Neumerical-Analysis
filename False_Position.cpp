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

// False Position (Regula Falsi) Method to find a root in a given interval [a, b]
double falsePositionMethod(const vector<double>& coeffs, double a, double b, double tolerance)
{
    double fa = evaluatePolynomial(coeffs, a);
    double fb = evaluatePolynomial(coeffs, b);
    double c;  // This will store the root approximation

    if (fa * fb >= 0) {
        cout << "The function must have opposite signs at a and b for the false position method to work.\n";
        return NAN; // Not a number to indicate invalid input
    }

    while (fabs(b - a) >= tolerance)
    {
        // Calculate the position using the false position formula
        c = (a * fb - b * fa) / (fb - fa);
        double fc = evaluatePolynomial(coeffs, c);

        // Check if c is a root
        if (fabs(fc) < tolerance)
            return c;

        // Update interval
        if (fa * fc < 0) {
            b = c;
            fb = fc;  // Update f(b)
        } else {
            a = c;
            fa = fc;  // Update f(a)
        }
    }

    return c;  // Return the root approximation
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
    double tolerance = 0.0000001;

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
            double root = falsePositionMethod(coeffs, i, i + step, tolerance);
            if (!isnan(root))  // Only add valid roots
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
            cout << "There might be more roots outside this interval, or consider increasing the range.\n";
        }
    }
    else
    {
        cout << "No roots found in the given interval.\n";
    }

    return 0;
}

