#include <iomanip>      // std::setw
#include <sstream>
#include "Matrix.h"

// Ctors =============
Matrix::Matrix(int numOfRows, int numOfColumns)
{
	// Check if arguments are valid
	if ((numOfRows < 1) ||(numOfColumns < 1))
	{
		throw "Failed to create a new matrix - Invalid matrix size";
	}

	m_numOfRows = numOfRows;
	m_numOfColumns = numOfColumns;
	
	try
	{
		m_matrix = new double[numOfRows * numOfColumns];
	}
	catch (std::bad_alloc)
	{
		throw "Failed to create a new matrix - Not enough memory";
	}

	// Initialize array to 0
	for (int i = 0; i < numOfRows * numOfColumns; ++i)
	{
		m_matrix[i] = 0;
	}
}

Matrix::Matrix(const Matrix& matrixToCopy)
{
	m_numOfRows = matrixToCopy.m_numOfRows;
	m_numOfColumns = matrixToCopy.m_numOfColumns;
	
	try
	{
		m_matrix = new double[m_numOfRows * m_numOfColumns];
	}
	catch (std::bad_alloc)
	{
		throw "Copy failed - Not enough memory";
	}

	// Copy matrixToCopy into newly created matrix
	operator=(matrixToCopy);
}

// Dtor =============
Matrix::~Matrix()
{
	delete[] m_matrix;
}

// Getters =============
int Matrix::getNumOfRows() const
{
	return m_numOfRows;
}

int Matrix::getNumOfColumns() const
{
	return m_numOfColumns;
}

double Matrix::getValue(int row, int column) const
{
	// Check column and row are in bounds
	if ((row < 0) || (row >= m_numOfRows) || (column < 0) || (column >= m_numOfColumns))
	{
		throw "Failed to get Value - Position not in range";
	}

	return m_matrix[(getPosInArray(row, column))];
}

// Setters =============
void Matrix::setValue(int row, int column, double value)
{
	// Check column and row are in bounds
	if ((row < 0) || (row >= m_numOfRows) || (column < 0) || (column >= m_numOfColumns))
	{
		throw "Failed to set Value - Position not in range";
	}
	m_matrix[(getPosInArray(row, column))] = value;
}

// Operator overloading =============
Matrix Matrix::operator+(const Matrix& m) const
{
	// Check if both matrices are equal in size
	if ((m_numOfRows != m.m_numOfRows) || (m_numOfColumns != m.m_numOfColumns))
	{
		throw "Failed to add matrices - Not the same size";
	}

	Matrix result(*this);

	// Sum both matrices into new matrix
	for (int i = 0; i < m_numOfRows * m_numOfColumns; ++i)
	{
		result.m_matrix[i] = m_matrix[i] + m.m_matrix[i];
	}

	return result;
}


Matrix Matrix::operator-(const Matrix& m) const
{
	// Check if both matrices are equal in size
	if ((m_numOfRows != m.m_numOfRows) || (m_numOfColumns != m.m_numOfColumns))
	{
		throw "Failed to subtract matrices - Not the same size";
	}

	Matrix result(*this);

	// Subtract matrices into new matrix
	for (int i = 0; i < m_numOfRows * m_numOfColumns; ++i)
	{
		result.m_matrix[i] = m_matrix[i] - m.m_matrix[i];
	}

	return result;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	// Check if both matrices are equal in size
	if ((m_numOfRows != m.m_numOfRows) || (m_numOfColumns != m.m_numOfColumns))
	{
		throw "Failed to assign matrices - Not the same size";
	}

	// Copy values from m 
	for (int i = 0; i < m_numOfRows * m_numOfColumns; ++i)
	{
		m_matrix[i] = m.m_matrix[i];
	}

	return *this;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	// Check if matrices can be multiplied (sizes should be compatible)
	if (m_numOfColumns != m.m_numOfRows)
	{
		throw "Failed to multiply - Matrices not of appropriate size";
	}

	Matrix result(m_numOfRows, m.m_numOfColumns);

	// Make multiplication
	for (int row = 0; row < m_numOfRows; ++row)
	{
		for (int col = 0; col < m.m_numOfColumns; ++col)
		{
			for (int i = 0; i < m_numOfColumns; ++i)
			{
				result.m_matrix[result.getPosInArray(row, col)] += m_matrix[getPosInArray(row, i)] * m.m_matrix[m.getPosInArray(i, col)];
			}
		}
	}

	return result;
}

// Matrix multiplied by scalar
Matrix Matrix::operator*(double scalar) const
{
	Matrix result(*this);

	// multiply all values by scalar
	for (int i = 0; i < m_numOfRows * m_numOfColumns; ++i)
	{
		result.m_matrix[i] *= scalar;
	}
	return result;
}

// Non member function - scalar multiplied by matrix
Matrix operator*(double scalar, const Matrix& m)
{
	return m.operator*(scalar);
}

bool Matrix::operator==(const Matrix& m) const
{
	// If matrices have different sized then they are not equal
	if ((m_numOfRows != m.m_numOfRows) || (m_numOfColumns != m.m_numOfColumns))
	{
		return false;
	}

	// Look for a value that is not equal in both matrices
	for (int row = 0; row < m_numOfRows; ++row)
	{
		for (int col = 0; col < m_numOfColumns; ++col)
		{
			if (m_matrix[getPosInArray(row, col)] != m.m_matrix[getPosInArray(row, col)])
			{
				return false;
			}
		}
	}
	// Every value is equal, and size is equal
	return true;
}

// Returns the location of row,col in the matrix array
int Matrix::getPosInArray(int row, int column) const
{
	return (row * m_numOfColumns) + column;
}

std::string Matrix::to_string() const
{

	std::stringstream s;
	
	for (int row = 0; row < m_numOfRows; ++row)
	{
		for (int col = 0; col < m_numOfColumns - 1; ++col)
		{
			s << std::setw(10) << std::setprecision(4) << m_matrix[(getPosInArray(row, col))];
		}
		
		s << std::setw(10) << std::setprecision(4) << m_matrix[(getPosInArray(row, m_numOfColumns - 1))] << std::endl;
	}

	return s.str();
}

// Non member function
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	os << m.to_string();
	return os;
}