/********************************************************************
	created:	2015/03/08
	created:	8:3:2015   21:40
	filename: 	C:\Development\Projects\NumericAlgorithms\BinaryNumberRepresentation\BinaryNumberRepresentation\Source.cpp
	file path:	C:\Development\Projects\NumericAlgorithms\BinaryNumberRepresentation\BinaryNumberRepresentation
	file base:	Source
	file ext:	cpp
	author:		Horia Mut, Nils Ryter, Romain Claret Yakovenko

	purpose:	Main program stdin.
	*********************************************************************/
#include <iostream>
#include <stdio.h>

#include "MFloat17.h"

using namespace std;
int main()
{
	/*
	int SizeMFloat17 = sizeof(MFloat17);

	// Test invalid values.
	MFloat17 Nan = MFloat17(NaN);
	bool isNan = Nan.IsNaN();

	// Test max and min values.
	MFloat17 Max = MFloat17(32650);
	MExponent MaxExp;
	MaxExp.E = 30;
	MMantissa MaxMantissa;
	MaxMantissa.M = 2047;

	Max.SetE(MaxExp);
	Max.SetM(MaxMantissa);
	Max.UpdateType();

	cout << "Max:" << Max.ToString() << endl;
	cout << "Max:" << Max.ToDouble() << endl;

	MFloat17 Min = MFloat17(0.0);
	MExponent MinExp;
	MinExp.E = 0;
	MMantissa MinMantissa;
	MinMantissa.M = 1;

	Min.SetE(MinExp);
	Min.SetM(MinMantissa);
	Min.UpdateType();

	cout << "Min:" << Min.ToString() << endl;
	cout << "Min:" << Min.ToDouble() << endl;

	// Test number representation.
	MFloat17* Num2 = new MFloat17(0.56);
	cout << "0.56: " << Num2->ToString() << endl;
	cout << "0.56: " << Num2->ToDouble() << endl;
	MFloat17* Num3 = new MFloat17(100.1456);
	cout << "100.1456: " << Num3->ToString() << endl;
	cout << "100.1456: " << Num3->ToDouble() << endl;

	// Test addition.
	MFloat17* Nr_20 = new MFloat17(20);
	cout << "20: " << Nr_20->ToString() << endl;
	cout << "20: " << Nr_20->ToDouble() << endl;

	MFloat17 Nr_10;
	Nr_10 = MFloat17(10);
	cout << "10:\t" << Nr_10.ToString() << endl;
	cout << "10:\t" << Nr_10.ToDouble() << endl;

	MFloat17 Addition = Nr_10 + *Nr_20;
	cout << "20+10:\t" << Addition.ToString() << endl;
	cout << "20+10:\t" << Addition.ToDouble() << endl;
	cout << "30=\t" << MFloat17(30).ToString() << endl;

	// Test multiplication.
	MFloat17* Num4 = new MFloat17(10.56);
	cout << "10.56 - Left:\t" << Num4->ToString() << endl;
	cout << "10.56 - Left:\t" << Num4->ToDouble() << endl;

	MFloat17* Num5 = new MFloat17(2);
	cout << "2 - Right:\t" << Num5->ToString() << endl;
	cout << "2 - Right:\t" << Num5->ToDouble() << endl;

	MFloat17 CorD = MFloat17(21.12);
	cout << "21.12 - Correct:\t" << CorD.ToString() << endl;
	cout << "21.12 - Correct:\t" << CorD.ToDouble() << endl;

	MFloat17 NumD = *Num4 * *Num5;
	cout << "Result:\t" << NumD.ToString() << endl;
	cout << "Result:\t" << NumD.ToDouble() << endl;
	*/
	cout << "Voici notre encodage en virgule flotante sur 17 bits" << endl << endl;
	cout << "Entrez deux nombres a virgule et le programme vous donnera leur représentation en virgule flotante (17 bits) ainsi que la représentation de leur addition" << endl << endl;
	cout << "Entrez un nombre :" << endl;
	double ValUser1 = 0;
	cin >> ValUser1;
	cout << endl << "Entrez un nombre :" << endl;
	double ValUser2 = 0;
	cin >> ValUser2;
	MFloat17 N1(ValUser1);
	MFloat17 N2(ValUser2);
	MFloat17 Addition = N2 + N1;

	cout << endl << "1er nombre:\t\t" << N1.ToString() << endl;
	cout << "2eme nombre:\t\t" << N2.ToString() << endl;
	cout << "Addition:\t\t" << Addition.ToString() << endl;

	cout << endl << "Voila, au revoir" << endl << endl;

	return 0;
}