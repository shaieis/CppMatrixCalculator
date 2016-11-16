#pragma once

#include "Matrix.h"
class Matrices
{
public:
	static void switchRows(Matrix& matrix, int row1, int row2);
	static void switchColumns(Matrix& matrix, int column1, int column2);

	static void multiplyRow(Matrix & matrix, int row, double scalar);
	static void multiplyColumn(Matrix & matrix, int column, double scalar);

	static Matrix transpose(const Matrix& matrix);

	static double normalizeRow(Matrix& matrix, int row, int byColumn);
	static void addToRow(Matrix& matrix, int rowToAddTo, int rowToAdd, double scalar);
	static void gaussianElimination(Matrix& matrix, bool includeLastCol);

	static double determinant(const Matrix& matrix);

private:
	static int findNextRowToNormalize(const Matrix& matrix, int currRow, int column);
	static double elimination(Matrix& matrix, bool includeLastCol);
};

