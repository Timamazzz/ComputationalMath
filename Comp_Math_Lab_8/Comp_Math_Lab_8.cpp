#include <iostream>
#include <cmath>
using namespace std;

double f(double x)
{
	return (1-x)*sin(x)+1;
}

int main()
{
	setlocale(0, "");
	const double EPS = 0.001; double a, b;
	do
	{
		cout << "Enter the boundaries of the section where the function will be considered: \n";
		cout << "Enter a: " << endl;
		cin >> a;
		cout << "Enter b: " << endl;
		cin >> b;
		if ((f(a) * f(b)) > 0) {

			cout << "Unsuitable section" << endl;

		}

	} while ((f(a) * f(b)) > 0);
	double c = (a + b) / 2;
	while ((fabs(b - a)) > EPS)
	{
		if ((f(c) * f(b)) < 0)
		{
			a = c;
		}
		else {
			b = c;
		}
		c = (a + b) / 2;
	}
	cout << "The root of the equation: " << a << endl;
	system("pause");

}
