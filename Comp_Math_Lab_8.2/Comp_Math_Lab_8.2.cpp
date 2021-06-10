#include <iostream>

using namespace std;

double f(double x)
{
	return pow(3-pow(x,2), 1/2);
}

double fd(double x)
{
	return sqrt(x);
}

int main()

{
	setlocale(0, "");
	const double EPS = 0.001;
	double x;
	cout << "Enter the initial value of x: " << endl;
	cin >> x;
	while (fabs((x - f(x) / fd(x)) - x) > EPS)
	{
		x = x - f(x) / fd(x);
	}
	cout << x << endl;
	system("pause");
	return 0;
}
