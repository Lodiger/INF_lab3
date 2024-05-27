#include <iostream>
#include <cmath>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

double func(double x);
double fProizv2(double x);
void halfDivid(double a, double b, double eps);
void chord(double a, double b, double eps);
void Newueton(double a, double b, double eps);
void simplei(double a, double b, double eps, int N);
void sekush(double x0, double x1, double eps);
void combain(double a, double b, double eps);

void main()
{
	setlocale(LC_ALL, "RUS");
	int pointer = 10;
	double
		a,
		b,
		eps;
	int N;
	while (pointer != 0)
	{
		cout << "\nВыберите номер метода \n 1) Метод дихотомии.\n 2) Метод хорд.\n 3) Метод Ньютона.\n 4) Метод последовательных приближений.\n 5) Метод секущих.\n 6) Комбинированный метод.\n (0 для выхода)" << endl;
		cin >> pointer;
		switch (pointer)
		{
		case 1:
		{
			cout << "Выбран метод дихотомии \nВведите начало отрезка: ";
			cin >> a;
			cout << "Введите конец отрезка: ";
			cin >> b;
			cout << "Введите точность eps: ";
			cin >> eps;
			halfDivid(a, b, eps);
		}
		break;
		case 2:
		{
			cout << "Выбран метод хорд \nВведите левый конец интервала: ";
			cin >> a;
			cout << "Введите правый конец интервала: ";
			cin >> b;
			cout << "Введите точность eps: ";
			cin >> eps;
			chord(a, b, eps);
		}
		break;
		case 3:
		{
			cout << "Выбран метод Ньютона \nВведите начало отрезка: ";
			cin >> a;
			cout << "Введите конец отрезка: ";
			cin >> b;
			cout << "Введите точность eps: ";
			cin >> eps;
			Newueton(a, b, eps);
		}
		break;
		case 4:
		{
			cout << "Выбран метод Простых итераций \nВведите начало отрезка: ";
			cin >> a;
			cout << "Введите конец отрезка: ";
			cin >> b;
			cout << "Введите кол-во итераций: ";
			cin >> N;
			cout << "Введите точность eps: ";
			cin >> eps;
			simplei(a, b, eps, N);
		}
		break;
		case 5:
		{
			cout << "Введите начальные приближения x0 и x1: ";
			cin >> a >> b;
			cout << "Введите точность eps: ";
			cin >> eps;
			sekush(a, b, eps);
		}
		break;
		case 6:
		{
			cout << "Введите левый конец интервала: ";
			cin >> a;
			cout << "Введите правый конец интервала: ";
			cin >> b;
			cout << "Введите точность eps: ";
			cin >> eps;
			combain(a, b, eps);
		}
		break;
		}
	}
}


double func(double x)
{
	return atan(x - 1) + 2 * x;
}

double fProizv2(double x) 
{
	return (2*pow(x, 2)-4*x+5)/(pow(x,2)-2*x+2);
}

void halfDivid(double a, double b, double eps) 
{
	double 
		fa = func(a),
		fb = func(b),
		x, 
		fx;
	int n = 0;
	if (fa * fb > 0) 
	{
		cout << "На заданном отрезке корней нет" << endl;
	}
	do {
		x = (a + b) / 2;
		fx = func(x);

		if (fa * fx < 0) {
			b = x;
			fb = fx;
		}
		else {
			a = x;
			fa = fx;
		}
		n++;
	} while (fabs(b - a) > eps);
	cout << "Корень уравнения: " << x << endl;
	cout << "Значение функции в корне: " << fx << endl;
	cout << "Количество итераций: " << n << endl;
}

void chord(double a, double b, double eps) 
{
	double 
		x, 
		z, 
		f1, 
		f2, 
		fz, 
		h;
	int n = 1;
	if (func(a) * func(b) >= 0) {
		cout << "На заданном отрезке корней нет" << endl;
		return;
	}
	if (func(a) * fProizv2(a) > 0) {
		x = a;
		z = b;
	}
	else {
		x = b;
		z = a;
	}
	do {
		f1 = func(x);
		f2 = func(x);

		fz = func(z);

		h = (x - z) / (f1 - fz) * f1;
		x = x - h;
		n++;

	} while (abs(h) > eps);
	// Выводим результат
	cout << "Корень уравнения: " << x << endl;
	cout << "Значение функции в корне: " << func(x) << endl;
	cout << "Количество итераций: " << n << endl;
}

void Newueton(double a, double b, double eps)
{
	double 
		x, 
		f1, 
		F, 
		h;
	int n = 0;
	if (func(a) * func(b) > 0) {
		cout << "На заданном отрезке корней нет" << endl;
		return;
	}
	F = func(a);
	f1 = fProizv2(a);
	if (F * f1 > 0) 
	{
		x = b;
	}
	else 
	{
		x = a;
	}
	do {
		F = func(x);
		f1 = fProizv2(x);
		if (fabs(f1) < eps) 
		{
			cout << "Производная функции слишком мала, возможно деление на ноль." << endl;
			return;
		}
		h = F / f1;
		x = x - h;
		n += 1;
	} while (fabs(h) > eps);
	cout << "Корень уравнения: " << x << endl;
	cout << "Значение функции в корне: " << F << endl;
	cout << "Количество итераций: " << n << endl;
}

void simplei(double a, double b, double eps, int N) 
{
	if (func(a) * func(b) < 0) 
	{
		double 
			x0 = a,
			x = x0;
		int n = 0;
		do {
			x = func(a);
			n++;
			x0 = x;
		} while ((fabs(x - x0) > eps) || (n < N));
		{
			func(x);
		}
		cout << "Корень уравнения: " << x << endl;
		cout << "Значение функции в корне: " << func(x) << endl;
		cout << "Количество итераций: " << n << endl;
	}
	else 
	{
		puts("На заданном отрезке корней нет");
	}
}

void sekush(double x0, double x1, double eps) 
{
	int 
		p = 0,
		maxIter = 1000;
	double 
		x2, 
		error;
	for (int i = 1; i <= maxIter; i++) 
	{
		x2 = x1 - func(x1) * (x1 - x0) / (func(x1) - func(x0));
		error = fabs(x2 - x1);
		p++;
		if (error < eps) 
		{
			cout << "Корень найден: " << x2 << endl;
			cout << "Значение функции в корне: " << error << endl;
			cout << "Количество итераций: " << i << endl;
			break;
		}
		x0 = x1;
		x1 = x2;
	}
}

void combain(double a, double b, double eps) 
{
	double 
		aa, 
		bb, 
		x;
	if (func(a) * func(b) < 0)
	{
		int n = 1;
		if (func(a) * fProizv2(a) > 0 || func(b) * fProizv2(b) > 0)
		{
			do 
			{
				aa = a - (func(a) / fProizv2(a));
				bb = b - ((a - b) / (func(a) - func(b))) * func(b);
				n += 1;
				a = aa;
				b = bb;
			} while (fabs(aa - bb) > eps);
			x = (aa + bb) / 2;
			cout << "Корень найден: " << x << endl;
			cout << "Значение функции в корне: " << func(x) << endl;
			cout << "Количество итераций: " << n << endl;
		}
	}
	else
		cout << "На заданном отрезке корней нет" << endl;

}

