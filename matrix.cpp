/**
 * matrix.cpp - Implementation of classes found in the matrix.h file. 
 * Additional global functions implemented.
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: march 22 2018
 */

#include "matrix.h"
#include <string>
#include <cmath>

/**
 * Parameterized contstuctor
 * Input:
 *      rows - 0 based number of rows in matrix
 *      cols - 0 based number of columns in matrix
 * Output:
 *      new matrix object
 * Thows:
 * 		matrixException - thown if rows or cols < 0
 **/
matrix::matrix(unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
{
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}
	createEmptyMatrix(rows, cols);
}

/**
 * Copy contstuctor. Takes an object and returns a new object
 * exactly like the object passed in.
 * Input:
 *      from - reference to matrix to copy
 * Output:
 *      new matrix object
 **/
matrix::matrix(const matrix &from) : rows(from.rows), cols(from.cols)
{
	the_matrix = new double*[rows];

	for (unsigned int i = 0; i < rows; i++)
	{
		the_matrix[i] = new double[cols];

		for (unsigned int j = 0; j < cols; j++)
		{
			the_matrix[i][j] = from[i][j];
		}
	}

	this->rows = rows;
	this->cols = cols;
}

/**
 * Destructor for the matrix class
 * Input:
 *      none
 * Output:
 *      matrix removed from memory
 **/
matrix::~matrix()
{
	erase();
}

/**
 * Overrides the default behavior of = and allows matrix
 * objects to be directly assigned to other matrix objects
 * even if the left side matrix is not the same size as the 
 * right side matrix.
 * Input:
 *      rhs - reference to matrix to assign to "this"
 * Output:
 *      *this - refers to reassigned matrix object
 **/
matrix &matrix::operator=(const matrix &rhs)
{
	if (this->rows != rhs.rows || this->cols != rhs.cols)
	{
		erase();
		the_matrix = new double*[rhs.rows];

		for (unsigned int i = 0; i < rhs.rows; i++)
		{
			the_matrix[i] =  new double[rhs.cols];

			for (unsigned int j = 0; j < rhs.cols; j++)
			{
				the_matrix[i][j] = rhs[i][j];
			}
		}

		this->rows = rhs.rows;
		this->cols = rhs.cols;
	} else {
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < cols; j++)
			{
				the_matrix[i][j] = rhs[i][j];
			}
		}
	}

	return *this;
}

/**
 * Creates the Identity matrix. This is essentially a
 * named constructor.
 * Input:
 *      size - number of rows/columns in the identity matrix.
 * Output:
 *      new matrix object
 * Thows:
 * 		matrixException - thown if size < 0
 **/
matrix matrix::identity(unsigned int size)
{
	// use p-constructor
	matrix identity = matrix(size, size);
	for (unsigned int i = 0; i < size; i++)
	{
		identity[i][i] = 1.0;
	}
	return identity;
}

/**
 * Performs matrix addition of two matrix objects and 
 * returns the result as a new matrix object
 * Input:
 *      rhs - reference to the matrix to be added with "this"
 * Output:
 *      new matrix object
 **/
matrix matrix::operator+(const matrix &rhs) const
{
	//check that arrays are compatiable
	if (rhs.rows != this->rows || rhs.cols != this->cols)
	{
		throw matrixException("Matrixies must have the same number of rows and columns");
	}

	matrix tempMatrix = *this;

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			tempMatrix[i][j] = the_matrix[i][j] + rhs[i][j];
		}
	}

	return tempMatrix;
}

/**
 * Performs cross multiplication of two matrix objects and returns
 * the result in a new matrix
 * Input:
 *      rhs - reference to the matrix to be added with "this"
 * Output:
 *      new matrix object
 * Thows:
 * 		matrixException - thown if this->cols != rhs.cols
 **/
matrix matrix::operator*(const matrix &rhs) const
{
	//check that multiplication is possible
	if (this->cols != rhs.rows)
	{
		std::cout << "Cols: " << this->cols << ", Rows: " << rhs.rows << std::endl;
		throw matrixException("Illegal martix sizes for matrix multiplication.");
	}

	matrix tempMatrix = matrix(this->rows, rhs.cols);

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < rhs.cols; j++)
		{
			double result = 0;
			for (unsigned int k = 0; k < this->cols; k++)
			{
				result += (the_matrix[i])[k] * rhs[k][j];
			}
			tempMatrix[i][j] = result;
		}
	}

	return tempMatrix;
}

/**
 * Multiplies matrix by a scalar value (dot product) and returns the
 * result as a new matrix.
 * Input:
 *      scale - value to multiple matrix elements by
 * Output:
 *      new matrix object
 **/
matrix matrix::operator*(const double scale) const
{
	matrix tempMatrix = *this;

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			tempMatrix[i][j] = scale * (the_matrix[i])[j];
		}
	}

	return tempMatrix;
}

/**
 * Transposes the matrix and returns the result as a new matrix
 * object.
 * Input:
 *      none
 * Output:
 *      new matrix object
 **/
matrix matrix::operator~() const
{
	matrix tempMatrix = matrix(cols, rows);

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			tempMatrix[j][i] = the_matrix[i][j];
		}
	}

	return tempMatrix;
}

/**
 * Sets all values in the matrix to 0.
 * Input:
 *      none
 * Output:
 *      none
 **/
void matrix::clear()
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			the_matrix[i][j] = 0.0;
		}
	}

	return;
}

/**
 * Access operator that allows a row to be accessed from the matrix. 
 * Includes index access protection.
 * Input:
 *      row to access
 * Output:
 *      matrix_row - object representing a row in the matrix.
 * Thows:
 * 		matrixException - thown if trying to access row larger than the number of rows in matrix.
 **/
matrix::matrix_row matrix::operator[](unsigned int row)
{
	if (row > rows - 1)
	{
		throw matrixException("Attempting to access a matrix row that does not exist.");
	}
	matrix_row mrow = matrix_row(the_matrix[row], cols);
	return mrow;
}

/**
 * Access operator that allows a row to be accessed from the matrix. 
 * Includes index access protection.
 * Input:
 *      row to access
 * Output:
 *      matrix_row - object representing a row in the matrix.
 * Thows:
 * 		matrixException - thown if trying to access row larger than the number of rows in matrix.
 **/
matrix::matrix_row matrix::operator[](unsigned int row) const
{
	if (row > rows - 1)
	{
		throw matrixException("Attempting to access a matrix row that does not exist.");
	}
	matrix_row mrow = matrix_row(the_matrix[row], cols);
	return mrow;
}

/**
 * Prints the matrix to the output stream
 * Input:
 *      os - reference to the output stream
 * Output:
 *      os - output stream
 **/
std::ostream &matrix::out(std::ostream &os) const
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			os << " " << (the_matrix[i])[j] << " ";
		}
		os << std::endl;
	}

	return os;
}

/////////////////////////////////////////////////
// Private Methods
/////////////////////////////////////////////////

/**
 * Private helper method to deallocate memory used by the matrix.
 * Input:
 *      none
 * Output:
 *      none
 **/
void matrix::erase()
{
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] the_matrix[i];
	}

	delete[] the_matrix;
	rows = 0;
	cols = 0;
}

/**
 * Private helper method to initialize a blank matrix
 * Input:
 *      row - 0 based rows in the matrix
 * 		cols - 0 based columns in the matrix
 * Output:
 *      none
 * Throws:
 * 		matrixException - if rows or columns are less than 1
 **/
void matrix::createEmptyMatrix(int rows, int cols)
{
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}

	the_matrix = new double*[rows];

	for (int i = 0; i < rows; i++)
	{
		the_matrix[i] = new double[cols];

		for (int j = 0; j < cols; j++)
		{
			the_matrix[i][j] = 0.0;
		}
	}

	this->rows = rows;
	this->cols = cols;
}

//////////////////////////////////////////
// matrix_row implementation
//////////////////////////////////////////
/**
 * Parameterized contstuctor for the matrix row
 * Input:
 *      row - array of doubles representing a row
 *      cols - 0 based number of columns in matrix
 * Output:
 *      none
 **/
matrix::matrix_row::matrix_row(double* row, unsigned int cols){
	this->row = row;
	this->cols = cols;
}

/**
 * Access operator that allows an element to be accessed from a matrix row 
 * Includes index access protection.
 * Input:
 *      col - column from row to access
 * Output:
 *      double& - element of matrix
 * Thows:
 * 		matrixException - thown if trying to access col outside row
 **/
double& matrix::matrix_row::operator[](unsigned int col)
{
	if (col > cols - 1)
	{
		throw matrixException("Error attempting to access column outside of matrix row.");
	}
	return row[col];
}

/**
 * Access operator that allows an element to be accessed from a matrix row 
 * Includes index access protection.
 * Input:
 *      col - column from row to access
 * Output:
 *      double& - element of matrix
 * Thows:
 * 		matrixException - thown if trying to access col outside row
 **/
double& matrix::matrix_row::operator[](unsigned int col) const
{
	if (col > cols - 1)
	{
		throw matrixException("Error attempting to access column outside of matrix row.");
	}
	return row[col];
}

/////////////////////////////////////////
// Global functions
/////////////////////////////////////////


/**
 * Overrides default << behavior globally. Will print matrix
 * Input:
 *      os - reference to output stream
 * 		rhs - matrix to print
 * Output:
 *      ostream
 **/
std::ostream &operator<<(std::ostream &os, const matrix &rhs)
{
	return rhs.out(os);
}

/**
 * Global scalar multiplication
 * Input:
 *      scale - amount to scale matrix by
 * 		rhs - matrix to manipulate
 * Output:
 *      matrix - result of dot product multiplication
 **/
matrix operator*(const double scale, const matrix &rhs)
{
	matrix temp = rhs * scale;
	return temp;
}
