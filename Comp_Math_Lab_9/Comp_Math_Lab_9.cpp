#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <locale>
using namespace std;
double** mSol, a, b, h;
int n;

double fDer(double x, double y) {
	return (y/(x+1))-pow(y,2);
}

double fy(double x) {
	return 2*(x+1)/(pow(x,2)+2*x+2);
}

double euler(bool editable) {
	for (int i = 1; i < n; i++) {
		mSol[editable][i] = mSol[editable][i - 1] + h * fDer(a + h * (i - 1), mSol[editable][i - 1]);
		if (editable)
			mSol[editable][i] = mSol[editable][i - 1] + h / 2 *
			(fDer(a + h * (i - 1), mSol[editable][i - 1]) + fDer(a + h * i, mSol[editable][i]));
	}
	return 0;
}

double rungeKutta() {
	double k1, k2, k3, k4;
	for (int i = 1; i < n; i++) {
		double x = a + h * (i - 1); double y = mSol[2][i - 1];
		k1 = fDer(x, y);
		k2 = fDer(x + (h / 2), y + ((k1 * h) / 2));
		k3 = fDer(x + (h / 2), y + ((k2 * h) / 2));
		k4 = fDer(x + h, y + k3 * h);
		mSol[2][i] = mSol[2][i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) * (h / 6);
	}
	return 0;
}


int main() {
	setlocale(LC_CTYPE, "Russian");
	cout << "Enter the left limit value of the interval x: "; cin >> a;
	cout << "Enter the right limit value of the interval x: "; cin >> b;
	h = 0.1; // cout << "Введите значение шага h: "; cin >> h;
	n = ((b - a) / h) + 1; mSol = new double* [4]; double y;
	cout << "Enter the initial value of y at point x = " << a << ": "; cin >> y;
	for (int i = 0; i < 4; i++) {
		mSol[i] = new double[n]; mSol[i][0] = y;
	}
	double mistake[3] = { 0 }; // Хранение абсолютной погрешности
	euler(false); // Метод Эйлера
	euler(true);  // Метод Эйлера с пересчётом
	rungeKutta();  // Метод Рунге-Кутты
	for (int i = 0; i < n; i++) mSol[3][i] = fy(a + h * i);
	cout << "|  Value of x | Euler method |Recalculated| Runge-Kutta | y = |\n" << setfill('-') << setw(65) << "\n";
	for (int i = 0; i < n; i++) {
		cout << "| x = " << fixed << setprecision(3) << a + h * i << " | ";
		for (int j = 0; j < 4; j++) {
			cout << "y = " << fixed << setprecision(6) << mSol[j][i] << " | ";
			if (j != 3) mistake[j] += abs(mSol[j][i] - mSol[3][i]) / (mSol[3][i] * n);
		}
		cout << endl;
	}
	cout << setfill('-') << setw(69) << "\n" << "| Abs.err. |" << setfill(' ');
	for (int j = 0; j < 3; j++) cout << setw(12) << mistake[j] << " |";
	cout << endl;  system("pause");
}
