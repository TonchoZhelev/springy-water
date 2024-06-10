#pragma once

#include <vector>

//quite simple class where i'll define the 
//Vertex Buffers and Indeces I'll need for my objects
//no need for anything more complex for this project anyway

struct TShape2D {
	const float Vertices[8*8] = {
		-1.00f,  1.00f,  0.00f, 1.0f,	 1.00f, 0.85f, 0.00f, 1.00f,
		 1.00f,  1.00f,  0.00f, 1.0f,	 1.00f, 0.85f, 0.00f, 1.00f,
		-1.00f,  0.33f,  0.00f, 1.0f,	 1.00f, 0.00f, 0.85f, 1.00f,
		 1.00f,  0.33f,  0.00f, 1.0f,	 1.00f, 0.00f, 0.85f, 1.00f,
		-0.33f,  0.33f,  0.00f, 1.0f,	 1.00f, 0.00f, 0.85f, 1.00f,
		 0.33f,  0.33f,  0.00f, 1.0f,	 1.00f, 0.00f, 0.85f, 1.00f,
		-0.33f, -1.00f,  0.00f, 1.0f,	 1.00f, 0.85f, 0.00f, 1.00f,
		 0.33f, -1.00f,  0.00f, 1.0f,	 1.00f, 0.85f, 0.00f, 1.00f,
	};

	const unsigned int Indeces[4*3] = {
		0, 2, 1,
		2, 3, 1,

		4, 6, 7,
		7, 5, 4,
	};

	const unsigned int VerticesCount = 8 * 8;
	const unsigned int IndecesCount = 3 * 4;
};

struct Plane2D {

	float Vertices[8*5] = {
		-1.0f, 0.0f, -1.0f, 1.0f,	 0.0f, 0.0f, 0.0f, 0.3f,
		 1.0f, 0.0f, -1.0f, 1.0f,	 0.0f, 0.0f, 0.0f, 0.3f,
		 0.0f, 0.0f,  0.0f, 1.0f,	 1.0f, 1.0f, 1.0f, 0.3f,
		-1.0f, 0.0f,  1.0f, 1.0f,	 0.0f, 0.0f, 0.0f, 0.3f,
		 1.0f, 0.0f,  1.0f, 1.0f,	 0.0f, 0.0f, 0.0f, 0.3f,
	};

	unsigned int Indeces[3*4] = {
		2, 1, 0,
		2, 4, 1,

		2, 3, 4,
		2, 0, 3,
	};

	const unsigned int VerticesCount = 8 * 5;
	const unsigned int IndecesCount = 3 * 4;
};

struct Cube {

	float Vertices[(4 + 4 + 2) * 8] = {
		-1.0f,  1.0f, -1.0f, 1.0f,	 0.00f, 0.00f, 0.00f, 0.6f,	 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,	 0.00f, 0.00f, 1.00f, 0.6f,	 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,	 0.00f, 1.00f, 0.00f, 0.6f,	 1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f,	 0.00f, 1.00f, 1.00f, 0.6f,	 1.0f, 0.0f,

		-1.0f,  1.0f,  1.0f, 1.0f,	 1.00f, 0.00f, 0.00f, 0.6f,	 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,	 1.00f, 0.00f, 1.00f, 0.6f,	 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,	 1.00f, 1.00f, 0.00f, 0.6f,	 1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,	 1.00f, 1.00f, 1.00f, 0.6f,	 1.0f, 0.0f,
	};

	unsigned int VerticesCount = 4 + 4 + 2;

	unsigned int Indeces[3 * 2 * 6] = {
		0, 1, 2,
		1, 3, 2,

		1, 5, 3,
		5, 7, 3,

		4, 6, 5,
		5, 6, 7,

		0, 2, 4,
		2, 6, 4,

		0, 4, 1,
		1, 4, 5,

		2, 3, 6,
		3, 7, 6
	};

	int IndecesCount = 3 * 2 * 6;
};

namespace MeshGenerator {

	struct Mesh {
		std::vector<float> verteces;
		std::vector<unsigned int> indeces;
	};

	// can make a generatePlane( widthCells, heightCells, width, height)
	// - one that can generate rectangular planes,
	// if you should - just call that one from this one 
	Mesh GenerateSquarePlane(unsigned int RowCellsCount);
}