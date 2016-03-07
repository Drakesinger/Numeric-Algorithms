/** Authors: Horia Mut, Romain Claret Yakovenko, Nils Ryter */

#include <iostream>
#include "CramerMatrix.h"
//#include <vld.h>

using namespace std;

void printMatrix(CramerMatrix &m, double solution[])
{
	for (int i = 0; i < m.getMatrixSize(); ++i)
	{
		std::cout << " | ";
		for (int j = 0; j < m.getMatrixSize(); ++j)
		{
			cout << m.getCellValue(i, j);
			cout << " | ";
		}
        cout << "= " << solution[i];
		std::cout << endl;
	}
}

CramerMatrix inputmatrixFromPrompt()
{
	int size = -1;
	while (size < 0)
	{
		cout << "Entrez la taille de la matrice : ";
        std::cin >> size;
	}

	CramerMatrix m(size);

	cout << "Entrez les valeurs de la matrice avec i pour les lignes et j pour les colonnes : ";
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
            cout << "i=" << i << ":" << "j=" << j << " ";
			double value = 0;
			cin >> value;
			m.setCellValue(i, j, value);
		}
        cout << endl;
	}

	return m;
}

int main(int argc, const char * argv[]) {
	cout << "Algo Num Labo 3: Methode Cramer" << endl;

	CramerMatrix m = inputmatrixFromPrompt();

	double solutionsOfOriginalMatrix[m.getMatrixSize()];

	for (int i = 0; i < m.getMatrixSize(); i++)
	{
		cout << "Enter the solution of the lign: " << i + 1 << " :" << endl;
		cin >> solutionsOfOriginalMatrix[i];
	}

	cout << "Representation of the Matrix: " << endl;
    printMatrix(m, solutionsOfOriginalMatrix);
	cout << endl;

	cout << "Determinant = " << m.getDet() << endl;

	double cramerSolutionsTab[m.getMatrixSize()];

	int cramerResult = m.getCramer(solutionsOfOriginalMatrix, cramerSolutionsTab);

	if (cramerResult == -1)
	{
		cout << "No solution" << endl;
	}
	else
	{
		cout << "The solutions are: " << "{ ";
		for (int i = 0; i < m.getMatrixSize(); i++)
		{
			cout << " " << cramerSolutionsTab[i];
			if (i < m.getMatrixSize() - 1)
				cout << ", ";
		}
		cout << " }" << endl;
	}

	return 0;
}
