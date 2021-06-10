#include <iostream>

using namespace std;

double FirstFunction(double x)
{
	return exp(x);
}
double SecondFunction(double x)
{

	return (5 * cos(x) * sin(x));
}
void MethodOfRectangles(double a, double b, double(*f)(double))
{

	const double eps = 0.001;
	double step = (b - a) / 2;
	double result = (f((a + b) / 2)) * step;
	double x = 0, previousResult = 0;
	int count = 2;
	do
	{
		previousResult = result;
		count *= 2;
		step = (b - a) / count;
		result = 0;
		for (x = a + step; x < b; x += step)
		{
			result += (f((x + x + step) / 2)) * step;
		}
	} while (abs(previousResult - result) > eps);
	cout << "Значение определённого интеграла, найденное методом Прямоугольников: " << result << endl;
}
void MethodOfTrapezoids(double a, double b, double(*f)(double))
{

	const double eps = 0.001;
	double step = (b - a) / 2;
	double result = step * (f(a) + f(a + step)) / 2;
	double x = 0, previousResult = 0;
	int count = 1;
	do
	{
		previousResult = result;
		count *= 2;
		step = (b - a) / count;
		result = 0;
		for (x = a; x < b; x += step)
		{
			result += (f(x) + f(x + step)) * step / 2;
		}
	} while (abs(previousResult - result) > eps);
	cout << "Значение определённого интеграла, найденное методом трапеций: " << result << endl;
}
void SimpsonMethod(double a, double b, double(*f)(double))
{

	const double eps = 0.001;
	double step = (b - a) / 2;
	double result = (f(a) + 4 * f(a + step) + f(b)) * step / 3;
	double x = 0, previousResult = 0;
	int count = 2;
	do
	{
		previousResult = result;
		count *= 2;
		step = (b - a) / count;
		result = 0;
		for (x = a + step; x < b; x += 2 * step)
		{
			result += (f(x - step) + 4 * f(x) + f(x + step)) * step / 3;
		}
	} while (abs(previousResult - result) > eps);
	cout << "Значение определённого интеграла, найденное методом Симпсона: " << result << endl;
}


int main()
{
	double(*f)(double);
	setlocale(LC_ALL, "Russian");
	f = &FirstFunction;
	cout << "Подынтегральная функция:  exp(x)" << endl;
	cout << "Нижняя граница интегрирования: 0" << endl;
	cout << "Верхняя граница интегрирования: 3" << endl;
	cout << endl;
	MethodOfTrapezoids(0, 3, f);
	cout << endl << endl;
	MethodOfRectangles(0, 3, f);
	cout << endl << endl;
	SimpsonMethod(0, 3, f);
	cout << endl << endl;
	f = &SecondFunction;

	cout << "Подынтегральная функция:5 * cos(x) * sin(x)" << endl;
	cout << "Нижняя граница интегрирования: 1" << endl;
	cout << "Верхняя граница интегрирования: 3" << endl;
	cout << endl;
	MethodOfTrapezoids(1, 3, f);
	cout << endl << endl;
	MethodOfRectangles(1, 3, f);
	cout << endl << endl;
	SimpsonMethod(1, 3, f);
	system("Pause");
}
