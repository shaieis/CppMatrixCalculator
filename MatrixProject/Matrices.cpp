#include "Matrices.h"
# include <iostream>

using namespace Matrix_ns;

void Matrices::switchRows(Matrix & matrix, int row1, int row2)
{
	// Check if rows are in bounds
	if (row1 < 0 || row2 < 0 ||
		(row1 >= matrix.getNumOfRows()) ||
		(row2 >= matrix.getNumOfRows()))
	{
		throw "Cant switch rows - row does not exist in matrix";
	}

	double temp;

	// Switch between every coresponding value in rows
	for (int col = 0; col < matrix.getNumOfColumns(); ++col)
	{
		temp = matrix.getValue(row1, col);
		matrix.setValue(row1, col, matrix.getValue(row2, col));
		matrix.setValue(row2, col, temp);
	}
}

void Matrices::switchColumns(Matrix & matrix, int column1, int column2)
{
	// Check if columms are in bounds
	if (column1 < 0 || column2 < 0 ||
		(column1 >= matrix.getNumOfColumns()) || 
		(column2 >= matrix.getNumOfColumns()))
	{
		throw "Cant switch columns - column does not exist in matrix";
	}

	double temp;

	// Switch between every coresponding value in columns
	for (int row = 0; row < matrix.getNumOfRows(); ++row)
	{
		temp = matrix.getValue(row, column1);
		matrix.setValue(row, column1, matrix.getValue(row, column2));
		matrix.setValue(row, column2, temp);
	}
}

void Matrices::multiplyRow(Matrix & matrix, int row, double scalar)
{
	// Check if row is in bounds
	if (row < 0 || row >= matrix.getNumOfRows())
	{
		throw "Cant multiply row - row does not exist in matrix";
	}

	// Multiply the row
	for (int col = 0; col < matrix.getNumOfColumns(); ++col)
	{
		matrix.setValue(row, col, matrix.getValue(row, col) * scalar);
	}
}
void Matrices::multiplyColumn(Matrix & matrix, int column, double scalar)
{
	// Check if column is in bounds
	if (column < 0 || column >= matrix.getNumOfColumns())
	{
		throw "Cant multiply column - column does not exist in matrix";
	}

	// Multiply the column
	for (int row = 0; row < matrix.getNumOfRows(); ++row)
	{
		matrix.setValue(row, column, matrix.getValue(row, column) * scalar);
	}
}

Matrix Matrices::transpose(const Matrix& matrix)
{
	// Create a new matrix with transposed size
	Matrix result(matrix.getNumOfColumns(), matrix.getNumOfRows());

	// Copy values to transposed matrix
	for (int row = 0; row < matrix.getNumOfRows(); ++row)
	{
		for (int col = 0; col < matrix.getNumOfColumns(); ++col)
		{
			result.setValue(col, row, matrix.getValue(row, col));
		}
	}
	return result;
}

void Matrices::addToRow(Matrix& matrix, int rowToAddTo, int rowToAdd, double scalar)
{
	// Check if rows are in bounds
	if (rowToAddTo < 0 || rowToAdd < 0 ||
		(rowToAddTo >= matrix.getNumOfRows()) ||
		(rowToAdd >= matrix.getNumOfRows()))
	{
		throw "Can't add rows - One of rows does not exist";
	}

	// rowToAddTo <- rowToAddTo + scalar*rowToAdd
	for (int col = 0; col < matrix.getNumOfColumns(); ++col)
	{
		matrix.setValue(rowToAddTo, col, matrix.getValue(rowToAddTo, col) + (matrix.getValue(rowToAdd, col) * scalar));
	}
}

// Returns the value which was used to normalize the row
double Matrices::normalizeRow(Matrix& matrix, int row, int byColumn)
{
	// Check if rows and columns are in bounds
	if (row < 0 || byColumn < 0 ||
		(row >= matrix.getNumOfRows()) ||
		(byColumn >= matrix.getNumOfColumns()))
	{
		throw "Cant normalize row - row or column does not exist in matrix";
	}

	double normalizator = matrix.getValue(row, byColumn);

	// Normalize each value in row using normalizator
	for (int col = 0; col < matrix.getNumOfColumns(); ++col)
	{
		matrix.setValue(row, col, matrix.getValue(row, col) / normalizator);
	}

	return normalizator;
}

void Matrices::gaussianElimination(Matrix& matrix, bool includeLastCol)
{
	elimination(matrix, includeLastCol);
}

double Matrices::determinant(const Matrix& matrix)
{
	// Check if matrix is square
	if (matrix.getNumOfRows() != matrix.getNumOfColumns())
	{
		throw "Cant calculate determinant - Matrix not square";
	}

	
	Matrix gaussianMat(matrix);

	// do guassian elimination on copy of the matrix and copy the multiplier 
	double result = elimination(gaussianMat, true);
	
	// multiply the multiplier value with value of the multiplication of the matrix main diagonal values 
	for (int i = 0; i < matrix.getNumOfRows(); ++i)
	{
		result *= gaussianMat.getValue(i, i);
	}
	return result;
}

// Used to find the next available row to normalize during the guassian elimination process. If no such row, returns -1
int Matrices::findNextRowToNormalize(const Matrix& matrix, int currRow, int column)
{
	
	for (int row = currRow + 1; row < matrix.getNumOfRows(); ++row)
	{
		// Find first row in with value of (row,col) is not zero
		if (matrix.getValue(row, column) != 0)
		{
			return row;
		}
	}
	return -1;
}

// Same as guassian eliminatin, but returns the multiplier that results from the guassian elimination process
double Matrices::elimination(Matrix& matrix, bool includeLastCol)
{
	double multiplier = 1;

	int lastRowNormalized = -1; // Contains the last row that has been normalized
	for (int col = 0; col < (includeLastCol ? matrix.getNumOfColumns() : matrix.getNumOfColumns() - 1); ++col)
	{
		int NextRow = findNextRowToNormalize(matrix, lastRowNormalized, col); // Find the next first row to contain a non zero value in column 'col'

		if (NextRow == -1) // No further row eith non zero value in column 'col'
		{
			continue;
		}

		if (lastRowNormalized + 1 != NextRow) 
		{
			switchRows(matrix, lastRowNormalized + 1, NextRow);
			multiplier *= -1;
		}

		multiplier *= normalizeRow(matrix, lastRowNormalized + 1, col);

		++lastRowNormalized;

		for (int r = 0; r < matrix.getNumOfRows(); ++r) 
		{
			if (r == lastRowNormalized)
			{
				continue;
			}

			addToRow(matrix, r, lastRowNormalized, -1 * matrix.getValue(r, col));

		}

	}
	return multiplier;
}