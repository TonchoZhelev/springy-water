#include "MeshGenerator.h"

MeshGenerator::Mesh MeshGenerator::GenerateSquarePlane(unsigned int RowCellsCount) // cells count IN A SINGLE ROW !!!!!
{
	Mesh temp;
	float step = 1.f / RowCellsCount;

	// the number of vertecies in a single line
	// is equal to the number of rows + 1 or columns + 1
	temp.verteces.reserve((RowCellsCount + 1)*(RowCellsCount + 1)*(4 + 4));

	for (unsigned int y = 0; y < RowCellsCount + 1; y++)
	{
		for (unsigned int x = 0; x < RowCellsCount + 1; x++)
		{
			temp.verteces.emplace_back(x*step);
			temp.verteces.emplace_back(0.f);
			temp.verteces.emplace_back(y*step);
			temp.verteces.emplace_back(1.f);

			float color = (y + x) % 3 * 0.25;

			temp.verteces.emplace_back(0.1f);// std::rand() % 1000 / 1000.f);
			temp.verteces.emplace_back(0.1f);// std::rand() % 1000 / 1000.f);
			temp.verteces.emplace_back(1.0f - color);
			temp.verteces.emplace_back(.8f);
		}
	}

	temp.indeces.reserve(RowCellsCount*RowCellsCount * 6);

	for (unsigned int y = 0; y < RowCellsCount; y++)
	{
		for (unsigned int x = 0; x < RowCellsCount; x++)
		{
			unsigned int rowWidth = RowCellsCount + 1;
			unsigned int row = y * rowWidth;
			temp.indeces.emplace_back(row + x);
			temp.indeces.emplace_back(row + x + rowWidth);
			temp.indeces.emplace_back(row + x + rowWidth + 1);

			temp.indeces.emplace_back(row + x + rowWidth + 1);
			temp.indeces.emplace_back(row + x + 1);
			temp.indeces.emplace_back(row + x);
		}
	}

	return temp;
}