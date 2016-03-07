/**
	Haute Ecole Arc
	Cours d'Algorithme Numerique
	Labo 3
	
	@author Equipe 5 (Mut Horia, Ryter Nils, Yakovenko Roman)
	@date 2015-04-30
 */

#include "CramerMatrix.h"

CramerMatrix::CramerMatrix(int size)
{
	// Check if the size supplied is negative, if that's the case, set it to 0.
	size = size < 1 ? 1 : size;
	matrixSize = size;

	values = new double*[matrixSize];
	for (int currentRow = 0; currentRow < matrixSize; ++currentRow)
	{
		values[currentRow] = new double[matrixSize];

		for (int currentCol = 0; currentCol < matrixSize; ++currentCol)
		{
			values[currentRow][currentCol] = 0; //set the cell to 0
		}
	}
}

CramerMatrix::CramerMatrix(const CramerMatrix &o)
{
	// Check if the size supplied is negative, if that's the case, set it to 0.
	this->matrixSize = o.matrixSize;

	values = new double*[matrixSize];
	for (int currentRow = 0; currentRow < matrixSize; ++currentRow)
	{
		values[currentRow] = new double[matrixSize];

		for (int currentCol = 0; currentCol < matrixSize; ++currentCol)
		{
			values[currentRow][currentCol] = o.values[currentRow][currentCol];
		}
	}
}

CramerMatrix::~CramerMatrix()
{
    for (int currentRow = 0; currentRow < matrixSize; ++currentRow)
    {
        // Delete the whole row.
        delete[] values[currentRow];
    }
    delete[] values;
}

CramerMatrix &CramerMatrix::operator=(CramerMatrix o) //Force copy
{
    std::swap(this->matrixSize, o.matrixSize);
    std::swap(this->values, o.values);
    return *this;
}

//Set a specific cell
void CramerMatrix::setCellValue(int row, int column, double value)
{
	if (row < 0 || column < 0)
	{
		cout << "Error: Tried to set negative coordinate cell." << endl;
	}
	else if (row < matrixSize || column < matrixSize)
	{
		this->values[row][column] = value;
	}
	else
	{
		cout << "error: set cell out of reach" << endl;
	}
}

//Return the cell value at a specific row and column
double CramerMatrix::getCellValue(int row, int column)
{
	if (row < matrixSize && column < matrixSize && this->values != 0 && row >= 0 && column >= 0)
	{
		return this->values[row][column];
	}
	else
	{
		cout << "error : get cell out of reach" << endl;
		return -1;
	}
}

int CramerMatrix::getMatrixSize()
{
	return matrixSize;
}

// Return the determiant
double CramerMatrix::getDet()
{
	double determinant = 0;

	switch (matrixSize)
	{
	case 1:
		determinant = getCellValue(0, 0);
		break;

	case 2:
		determinant = getCellValue(0, 0) * getCellValue(1, 1) - getCellValue(1, 0) * getCellValue(0, 1);
		break;

	default:
		for (int column = 0; column < matrixSize; column++)
		{
			CramerMatrix m = minor(0, column);
			int sign = (column % 2 == 1) ? -1 : 1;
			determinant += (sign * getCellValue(0, column) * m.getDet());
		}
		break;
	}

	return determinant;
}

//Return the Minor squared matrix (without the row and column received)
CramerMatrix CramerMatrix::minor(int row, int column)
{
	CramerMatrix tmp(matrixSize - 1);

    for (int new_row = 0; new_row < matrixSize; new_row++)
    {
        for (int new_column = 0; new_column < matrixSize; new_column++)
        {
            if(new_row != row && new_column != column)
            {
                int tmp_row = new_row - (new_row > row ? 1 : 0);
                int tmp_column = new_column - (new_column > column ? 1 : 0);
                double tmp_value = values[new_row][new_column];
                tmp.setCellValue(tmp_row, tmp_column, tmp_value);
            }
        }
    }

	return tmp;
}

// Modify the solution table and the constant table
// Return 1 if everything went fine, and -1 if it's not possible to solve
int CramerMatrix::getCramer(double solutionsOfOriginalMatrix[], double cramerSolutionsTab[])
{
	double determinant = this->getDet();

	if (determinant == 0) {
		return -1;
	}

	CramerMatrix tmp = CramerMatrix(matrixSize);

	for (int row = 0; row < matrixSize; row++)
	{
		for (int column = 0; column < matrixSize; column++)
		{
			tmp.setCellValue(row, column, values[row][column]);
		}
	}

	for (int row = 0; row < matrixSize; row++)
	{
		for (int column = 0; column < matrixSize; column++)
		{
			tmp.setCellValue(column, row, solutionsOfOriginalMatrix[column]);
		}

		cramerSolutionsTab[row] = tmp.getDet() / determinant;

		for (int column = 0; column < matrixSize; column++)
		{
			tmp.setCellValue(column, row, values[column][row]);
		}
	}

	return 1;
}
