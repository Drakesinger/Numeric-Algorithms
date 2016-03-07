/** Authors: Horia Mut, Romain Claret Yakovenko, Nils Ryter */
//
//  CramerMatrix.h
//  X-Lab3
//

#pragma once

#include <iostream>

using namespace std;

class CramerMatrix
{
public:

	/** \brief
	 * Specialized Cramer Matrix constructor.
	 * Construct a square matrix of a certain size and fill it with zeroes.
	 * By default, if the size is not specified, it constructs a 0-sized matrix.
	 * \param int   Size of the square matrix
	 */
	CramerMatrix(int size = 0); //arg: size

    CramerMatrix &operator=(CramerMatrix o) ;

    CramerMatrix(const CramerMatrix &o);

	/** \brief
	 * Default destructor.
	 */
	~CramerMatrix();

	/** \brief
	 *
	 * \param row int
	 * \param column int
	 * \param value double
	 * \return void
	 *
	 */
	void setCellValue(int row, int column, double value); //args: row, column, value

	/** \brief
	 *
	 * \param pValuesTab double**
	 * \return void
	 *
	 */
	void setMatrixTable(double** pValuesTab); //arg: table of table of value

	/** \brief
	 *
	 * \param row int
	 * \param column int
	 * \return double
	 *
	 */
	double getCellValue(int row, int column);

	/** \brief
	 * Retrieve the matrix' size.
	 * \return int
	 *
	 */
	int getMatrixSize();

	/** \brief
	 * Retrieve the matrix's determinant.
	 * \return double	The Determinant
	 */
	double getDet();

	/** \brief
	 *
	 * \param constantsTab double*
	 * \param solutionsTab double*
	 * \return int
	 *
	 */
	int getCramer(double* constantsTab, double* solutionsTab); //args: constantesTab, solutionsTab

private:
	int matrixSize;
	double** values;

	/** \brief
	 *
	 * \param row int
	 * \param col int
	 * \return CramerMatrix*
	 *
	 */
	CramerMatrix minor(int row, int col);

};
