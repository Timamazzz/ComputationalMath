#include <iostream>
#include <locale>
using namespace std;

int n = 4; double** deltaY, * x, * f;
double getNewtonSequence(double h, double xref) {
	double t = (xref - x[0]) / h;
	double sum = f[0];
	for (int i = 0; i < n - 1; i++) {
		double coef = t;
		for (int j = 0; j < i; j++)
			coef = coef * (t - (j + 1)) / (j + 2);
		sum += coef * deltaY[i][0];
	}
	return sum;
}

int frontRoute(double* a) {
	double h = x[1] - x[0];
	for (int i = 2; i < n; i++) { if (x[i] - x[i - 1] != h) return -1; }
	// Считаем разности функции
	deltaY = new double* [n - 1];
	for (int i = 0; i < n; i++) deltaY[i] = new double[n - 1 - i];
	// Порядок разностей функций для массива deltaY[i][j] равен i + 1
	// Считаем первые разности функций
	for (int i = 0; i < n - 1; i++) deltaY[0][i] = f[i + 1] - f[i];
	// Считаем следующие порядки
	for (int i = 1; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) deltaY[i][j] = deltaY[i - 1][j + 1] - deltaY[i - 1][j];
	}
	cout << "Разности функций:\n";
	for (int i = 0; i < n - 1; i++) {
		cout << i + 1 << ": ";
		for (int j = 0; j < n - 1 - i; j++) cout << "deltaY[" << j << "] = " << deltaY[i][j] << "; ";
		cout << endl;
	}
	for (int i = 0; i < 3; i++) cout << "Значение f(x) в точке a[" << i + 1 << "] = " << a[i] << " равно " << getNewtonSequence(h, a[i]) << endl;
	return 0;
}

int main() {
	setlocale(LC_ALL, "");
	cout << "Введите n: "; cin >> n;
	x = new double[n]; f = new double[n];
	for (int i = 0; i < n; i++) {
		cout << "x[" << i << "]: "; cin >> x[i];
		cout << "f(x[" << i << "]): "; cin >> f[i];
	}

	double a[3]; a[0] = (x[0] + x[1]) / 2; a[1] = (x[1] + x[2]) / 2; a[2] = (x[2] + x[3]) / 2;
	if (frontRoute(a) == -1) cout << "Невозможно посчитать h, разница элементов не статична!\n";
	system("pause");
	return 0;
}
