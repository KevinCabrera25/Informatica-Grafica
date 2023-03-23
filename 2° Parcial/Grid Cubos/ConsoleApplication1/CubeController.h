#pragma once
class CubeController
{
public:
	CubeController();
	~CubeController();

	void cubeGenerator(float, float, float);
	
private:
	float variationColor(float);
};

