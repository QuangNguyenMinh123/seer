#include <iostream>
#include "arithmetic.h"
#include "advanced.h"

using namespace std;

int main() {
    int a = 10, b = 3;

    cout << "Basic Arithmetic:" << endl;
    cout << a << " + " << b << " = " << add(a, b) << endl;
    cout << a << " - " << b << " = " << subtract(a, b) << endl;
    cout << a << " * " << b << " = " << multiply(a, b) << endl;
    cout << a << " / " << b << " = " << divide(a, b) << endl;

    cout << "\nAdvanced Math:" << endl;
    cout << "Factorial of 5 = " << factorial(5) << endl;
    cout << "Fibonacci of 7 = " << fibonacci(7) << endl;

    return 0;
}