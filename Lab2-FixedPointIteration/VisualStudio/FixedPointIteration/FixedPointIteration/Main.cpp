/** Authors: Horia Mut, Romain Claret Yakovenko, Nils Ryter */

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

double fx(double x)
{
	return sin(x) + x / 13;
}

double gx(double x)
{
	const int labda = 1;
	return x + labda*fx(x);
}

double yx(double x)
{
	return x;
}

void main0()
{
	const double valMax = 1E+200;
	const double epsilon = 0.001;
	const double maxIteration = 1000;

	double delta = epsilon + 1;
	double x;
	int cptLoop = 0;

	cout << "Please enter START-value for iteration :" << endl;
	cin >> x;

	while (delta > epsilon && cptLoop < maxIteration)
	{
		double _yx = yx(x);
		double _gx = gx(x);

		x = _gx;

		if (x > valMax) break;
		delta = fabs(_gx - _yx);

		++cptLoop;
	}

	if (x > valMax)
	{
		cout << endl << "WARNING : x out of range !  May the function diverge with you?" << endl;
	}

	if (cptLoop >= maxIteration)
	{
		cout << endl << "WARNING : maximum iteration reached ! May the function diverge with you?" << endl;
	}

	cout << endl << "Hey ! I am a (g)Root : " << x << endl;

	//return 0;
}