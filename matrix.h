/**
 * matrix.h - declaration of matrix class.  This class will be
 * capable of represting a Matrix as a first-class type.
 * 
 * Do not change any public methods in this file unless otherwise
 * instructed.
 *
 * For CS321.  (c) 2015 Dr. Darrin Rothe
 * 
 * Modified by Mitchell Larson on 3/22/18
 */
 
 
// compile guard 
#ifndef MATRIX_H
#define MATRIX_H
 
#include <iostream> // for std::ostream
#include <stdexcept>	// for std::runtime_error
#include <string>	// used in exception
 
// a helper class to bundle a message with any thrown exceptions.
// To use, simply 'throw matrixException("A descriptive message about
// the problem")'.  This will throw the exception object by value.
// Recommendation is to catch by reference (to prevent slicing).
class matrixException:public std::runtime_error
{
	public:
		matrixException(std::string message):
		      std::runtime_error((std::string("Matrix Exception: ") + 
		               message).c_str()) {}
};
 
 
class matrix
{
	class matrix_row {
		private:
			double* row;
			unsigned int cols;

		public:

			/**
			 * Parameterized contstuctor for the matrix row
			 * Input:
			 *      row - array of doubles representing a row
			 *      cols - 0 based number of columns in matrix
			 * Output:
			 *      none
			 **/
			matrix_row(double* row, unsigned int cols);

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
			double& operator[](unsigned int col);

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
			double& operator[](unsigned int col) const;
	};

	public:
		// No default (no argument) constructor.  It doesn't really make
		// sense to have one as we cannot rely on a size.  This may trip
		// us up later, but it will lead to a better implementation.
		// matrix();
 
		// Constructor - createEmptyMatrix Matrix and clear cells.  If rows or
		// cols is < 1, throw a matrixException.  Note, we will not use
		// "exception specifications" as multiple sources report that 
		// the mechanism is not properly supported by most compilers.
		//
		// throw (matrixException)
		//
		matrix(unsigned int rows, unsigned int cols);
 
		// Copy constructor - make a new Matrix just like rhs
		matrix(const matrix& from);
 
		// Destructor.  Free allocated memory
		~matrix();
 
		// Assignment operator - make this just like rhs.  Must function
        // correctly even if rhs is a different size than this.
		matrix& operator=(const matrix& rhs);
 
		// "Named" constructor(s).  This is not a language mechanism, rather
		// a common programming idiom.  The underlying issue is that with
		// overloaded operators, you can loose sight of what various
		// combinations of arguments means.  For our design, constructor
		// arguments set the size of the matrix.  If we want to generate
		// "special" matrices, we are better off with statuc methods that 
		// will generate these and then we can give the metods meaningful
		// names.
		
		// Named Constructor - produce a square identity matrix of the
		// requested size.  Since we do not know how the object produced will
		// be used, we pretty much have to return by value.  A size of 0 
		// would not make sense and should throw an exception.
		//
		// throw (matrixException)
		//
		static matrix identity(unsigned int size);
		
 
 
		// Matrix addition - lhs and rhs must be same size otherwise
		// an exception shall be thrown
		//
		// throw (matrixException)
		//
		matrix operator+(const matrix& rhs) const;
 
		// Matrix multiplication - lhs and rhs must be compatible 
		// otherwise an exception shall be thrown
		//
		// throw (matrixException)
		//
		matrix operator*(const matrix& rhs) const;
 
		// Scalar multiplication.  Note, this function will support
		// someMatrixObject * 5.0, but not 5.0 * someMatrixObject.
		matrix operator*(const double scale) const;

		// Transpose of a Matrix - should always work, hence no exception
		matrix operator~() const;
 
		// Clear Matrix to all members 0.0
		void clear();
  
		// Access Operators - throw an exception if index out of range
		//
		// Note how these operators are to work.  Consider a Matrix
		// object being addressed with two sets of brackets - m1[1][2],
		// for example.  The compiler will execute this: (m1[1])[2].
		// The first set of brackets will call this function, and this
		// function should return a pointer to the first element of the
		// requested row.  The second set of brackets is applied to the
		// matrix_row*, which results in it being treated as an array, thus
		// the requested column is indexed.  The const version is
		// necessary if you would like to use the operator within other
		// const methods.  Both of these operators are extremely
		// dangerous as prototyped.  The nature of the danger and
		// a fix are left up to you to discover and fix.  A proper
		// fix will require a change to these function signatures
		// and the use of an internal "helper class."
		//
		// throw (matrixException)
		//
		matrix_row operator[](unsigned int row);
 
		// const version of above - throws an exception if indices are out of
		// range
		//
		// throw (matrixException)
		//
		matrix_row operator[](unsigned int row) const;
 
		// I/O - for convenience - this is intended to be called by the global
		// << operator declared below.
		std::ostream& out(std::ostream& os) const;

		
		
		
	private:
		// The data - note, per discussion on arrays, you can store these data
		// as a 1-D dynamic array, thus the matrix_row* below.  Alternatively, and
		// perhaps preferred, you could store the data as an array of arrays
		// which would require the_Matrix to be changed to a matrix_row**.
		double** the_matrix;
		unsigned int rows;
		unsigned int cols;

		/** routines **/

		//Private helper function to erase the underlying 2D array. This is made
		//private so that the destructor can utalize the functionality, as well
		//as matrix methods that need the the object to remain instantiated.
		void erase();

		//private helper function so that the underlying 2D array can be called
		//from matrix methods. This is necessary in the = operator override
		void createEmptyMatrix(int rows, int cols);
		// add any "helper" routine here, such as routines to support
		// matrix inversion

		

};

/** Some Related Global Functions **/
 
// Overloaded global << with std::ostream as lhs, Matrix as rhs.  This method
// should generate output compatible with an ostream which is commonly used
// with console (cout) and files.  Something like:
// [[ r0c0, r0c1, r0c2 ]
//  [ r1c0, r1c1, r1c2 ]
//  [ r0c0, r0c1, r0c2 ]]
// would be appropriate.
//
// Since this is a global function, it does not have access to the private
// data of a Matrix object.  So, it will need to use the public interface of
// Matrix to do its job.  The method Matrix::out was added to Matrix
// specifically for this purpose.  The other option would have been to make
// it a "friend"
 
std::ostream& operator<<(std::ostream& os, const matrix& rhs);
 
// We would normally have a corresponding >> operator, but
// will defer that exercise that until a later assignment.


// Scalar multiplication with a global function.  Note, this function will
// support 5.0 * someMatrixObject, but not someMatrixObject * 5.0
matrix operator*(const double scale, const matrix& rhs);

 
#endif