#include <iostream>
#include <stdlib.h>

#include "Matrix.h"
#include "Matrices.h"

using namespace Matrix_ns;

int main()
{
	try
	{
		Matrix matrix(3, 3);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				matrix.setValue(i, j, rand() % 10);
			}
		}

		std::cout << "Matrix before gaussian elimination" << std::endl << matrix << std::endl;
		
		std::cout << "Det: " << Matrices::determinant(matrix) << std::endl;

		Matrices::gaussianElimination(matrix, true);
		std::cout << "Matrix after gaussian elimination" << std::endl << matrix << std::endl;
		int i;
		std::cin >> i;

	}
	catch (char* c)
	{
		int i;
		std::cout << c;
		std::cin >> i;
	}


}