#pragma once

class spring
{
private:
	// k - the spring stiffness constant
	// d - dampening factor can ajust as you wish
	float k, d;
public:
	float Height, TargetHeight, Speed;

	spring(float Height, float k, float d);
	void ReFactor(float Height, float k, float d);

	void update();
};