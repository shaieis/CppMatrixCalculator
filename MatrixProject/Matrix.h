#pragma once

#include <string>

class Matrix
{
public:
	// Ctor =======
	Matrix(int numOfRows, int numOfColumns);
	Matrix(const Matrix &matrixToCopy);
	
	// Dtor =======
	~Matrix();

	int getNumOfRows() const;
	int getNumOfColumns() const;
	double getValue(int row, int column) const;
	
	Matrix operator+(const Matrix& m) const;
	Matrix operator-(const Matrix& m) const;
	Matrix operator*(const Matrix & m) const;
	Matrix operator*(double scalar) const;
	Matrix& operator=(const Matrix& m);
	bool operator==(const Matrix& m) const;


	void setValue(int row, int column, double value);
	std::string to_string() const;

private:
	int m_numOfRows, m_numOfColumns;
	double* m_matrix;

	int getPosInArray(int row, int column) const;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
Matrix operator*(double scalar, const Matrix& m);