#include "Water.h"
#include <iostream>

#include <thread>

Water::Water(unsigned int ColumnXwidth, float Spread, float k, float d, unsigned int SurfaceStiffness, Shader& shader)
	:Spread(Spread), k(k), d(d),
	SurfaceStiffness(SurfaceStiffness), 
	Plane(MeshGenerator::GenerateSquarePlane(ColumnXwidth-1)),
	vb(Plane.verteces.data(), Plane.verteces.size() * sizeof(float)),
	ib(Plane.indeces.data(), Plane.indeces.size()), shader(shader),
	ModelTransform(1.f)//, Translate(1.f), Rotate(1.f), Scale(1.f)
{
	layout.Push(GL_FLOAT, 4, GL_FALSE);
	layout.Push(GL_FLOAT, 4, GL_FALSE);
	va.AddBuffer(vb, layout);

	springs.resize(ColumnXwidth);

	for (unsigned int z = 0; z < springs.size(); z++) 
	{
		springs[z].reserve(ColumnXwidth);
		for (unsigned int x = 0; x < springs[z].capacity(); x++)
		{
			springs[z].emplace_back(0.f, k, d);
		}
	}

	Deltas.resize(springs.size());

	for (unsigned int z = 0; z < Deltas.size(); z++)
	{
		Deltas[z].resize(ColumnXwidth);
	}

}

void Water::PullSprings()
{
	for (unsigned int s = 0; s < SurfaceStiffness; s++)
	{

		for (unsigned int z = 0; z < springs.size(); z++)
		{
			for (unsigned int x = 0; x < springs[0].size(); x++)
			{
				if (z > 0){
					Deltas[z][x] = Spread * (springs[z][x].Height - springs[z - 1][x].Height);
					springs[z - 1][x].Speed += Deltas[z][x];
				}

				if (z < springs.size() - 1) {
					Deltas[z][x] = Spread * (springs[z][x].Height - springs[z + 1][x].Height);
					springs[z + 1][x].Speed += Deltas[z][x];
				}

				if (x > 0) {
					Deltas[z][x] = Spread * (springs[z][x].Height - springs[z][x - 1].Height);
					springs[z][x - 1].Speed += Deltas[z][x];
				}
				
				if (x < springs[z].size() - 1) {
					Deltas[z][x] = Spread * (springs[z][x].Height - springs[z][x + 1].Height);
					springs[z][x + 1].Speed += Deltas[z][x];
				}
			}
		}

		for (unsigned int z = 0; z < springs.size(); z++)
		{
			for (unsigned int x = 0; x < springs[0].size(); x++)
			{
				if (z > 0) {
					springs[z - 1][x].Height += Deltas[z][x];
				}

				if (z < springs.size() - 1) {
					springs[z + 1][x].Height += Deltas[z][x];
				}

				if (x > 0) {
					springs[z][x - 1].Height += Deltas[z][x];
				}

				if (x < springs[z].size() - 1) {
					springs[z][x + 1].Height += Deltas[z][x];
				}
			}
		}

	}
}

void Water::update(float nnSpeed)
{
	springs[(springs.size() - 1) / 2][(springs[0].size() - 1) / 2].Speed = nnSpeed;

	PullSprings();

	for (unsigned int z = 0; z < springs.size(); z++)
	{
		for (unsigned int x = 0; x < springs[0].size(); x++)
		{
			springs[z][x].update();
		}
	}

}

void Water::render()
{
	GLCALL(glEnable(GL_CULL_FACE));
	shader.SetUniform4f("u_color", 1.f, 1.f, 1.f, 1.f);
	shader.SetUniformMatrix4fv("ModelTrans", 1, GL_FALSE, &ModelTransform[0][0]);

	va.Bind();
	ib.Bind();

	for (unsigned int z = 0; z < springs.size(); z++)
	{
		for (unsigned int x = 0; x < springs[0].size(); x++)
		{
			Plane.verteces[(1 + (z*springs.size() + x)*8)] = springs[z][x].Height;
		}
	}

	vb.setData(Plane.verteces.data(), Plane.verteces.size() * sizeof(float));

	GLCALL(glDrawElements(GL_TRIANGLES, Plane.indeces.size(), GL_UNSIGNED_INT, 0));
}

void Water::ReFactor(glm::mat4 Translate, glm::mat4 Rotate, glm::mat4 Scale)
{
	ModelTransform = Translate * Rotate * Scale;
}
