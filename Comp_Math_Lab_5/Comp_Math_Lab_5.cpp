
#include <iostream>
using namespace std;
void Work(double* X, double* Y, int count, double step)
{
	double* firstDerivative = new double[count], * secondDerivative = new double[count];
	firstDerivative[0] = (Y[1] - Y[0]) / step;
	firstDerivative[count - 1] = (Y[count - 1] - Y[count - 2]) / step;
	for (int i = 1; i != count - 1; ++i)
		firstDerivative[i] = (Y[i + 1] - Y[i - 1]) / (2 * step);
	secondDerivative[0] = (firstDerivative[1] - firstDerivative[0]) / step;
	secondDerivative[count - 1] = (firstDerivative[count - 1] - firstDerivative[count - 2]) / step;
	for (int i = 1; i != count - 1; ++i)
		secondDerivative[i] = (Y[i + 1] - 2 * Y[i] + Y[i - 1]) / pow(step, 2);
	cout << endl << "Результат:" << endl << endl;
	for (int i = 0; i != count; ++i)
	{
		cout << "y'(" << X[i] << ") = " << firstDerivative[i] << endl;
		cout << "y''(" << X[i] << ") = " << secondDerivative[i] << endl << endl;
	}
	delete[]firstDerivative;
	delete[]secondDerivative;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int count = 0;
	cout << "Введите количество узлов: ";
	cin >> count;
	double* X = new double[count], * Y = new double[count];
	cout << "Введите значения X: ";
	for (int i = 0; i != count; ++i)
		cin >> X[i];
	cout << "Введите значения Y: ";
	for (int i = 0; i != count; ++i)
		cin >> Y[i];
	Work(X, Y, count, X[1] - X[0]);
	delete[]X;
	delete[]Y;
	system("Pause");
}
