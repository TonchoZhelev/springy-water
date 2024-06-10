#pragma once

#include <vector>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Spring.h"
#include "MeshGenerator.h"

#include "ErrorChecking.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class Water {
private:
	std::vector<std::vector<spring>> springs; // think about making this a two dimentional vector
	std::vector<std::vector<float>> Deltas;
	float Spread, k, d;
	unsigned int SurfaceStiffness;

	MeshGenerator::Mesh Plane;
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	VertexBufferLayout layout;
	Shader& shader;

	glm::mat4 ModelTransform;//, Translate, Rotate, Scale;
public:

	float nheight;

	Water(unsigned int ColumnXwidth, float Spread, float k, float d, unsigned int SurfaceStiffness, Shader& shader);

	void PullSprings();
	void update(float nnHeight);
	void render();

	void ReFactor(glm::mat4 Translate, glm::mat4 Rotate, glm::mat4 Scale);

	//void Splash();
	//void PlobSplashParticles();
};