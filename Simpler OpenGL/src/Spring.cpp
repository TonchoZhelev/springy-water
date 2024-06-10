#include "Spring.h"

spring::spring(float Height, float k, float d)
	:Height(Height), TargetHeight(Height), Speed(0), k(k), d(d)
{
}

void spring::ReFactor(float Height, float k, float d)
{
	this->Height = Height;
	this->k = k;
	this->d = d;
}

void spring::update()
{
	Speed += k * (TargetHeight - Height) - Speed * d;
	Height += Speed;
}
