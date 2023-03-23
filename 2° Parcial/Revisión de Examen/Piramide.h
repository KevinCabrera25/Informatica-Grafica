#pragma once
class Piramide
{
public:
	Piramide();
	~Piramide();
	void moverPiramide(float _dt);

private:
	void dibujarPiramide();
	float _x, _y, _z;
	float _r, _g, _b;
	float size;
	float _rotX, _rotY, _rotZ;
	float _direcX, _direcY, _direcZ;
	float _speed, _angle;

};

