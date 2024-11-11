#pragma once
#include "Vector3.h"

class Matrix3
{
private:
	float matrix[3][3];

public:

	//Constructors & destructor
	Matrix3();
	Matrix3(float m[3][3]);
	Matrix3(const Matrix3& m);
	Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	~Matrix3();

	//Constants
	static Matrix3 identity();

	//Getter & setter
	float getElement(int i, int j) const;
	void setElement(int i, int j, float val);

	//Methods
	Matrix3& operator+=(const Matrix3& m);
	Matrix3& operator+=(float& d);
	Matrix3& operator-=(const Matrix3& m);
	Matrix3& operator-=(float& d);
	Matrix3& operator*=(const Matrix3& m);
	Matrix3& operator*=(const float& d);
	Matrix3& operator/=(float& d);
	void operator=(const Matrix3& m);
	bool operator==(const Matrix3& m) const;
	bool operator!=(const Matrix3& m) const;

	float determinant() const;
	Matrix3 transposition() const;
	Matrix3 comatrix() const;
	Matrix3 inverse() const;
	float trace() const;
};

Matrix3 operator+(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator-(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator*(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator*(const Matrix3& m, float d);
Matrix3 operator*(float d, const Matrix3& m);
Vector3 operator*(Vector3 v, Matrix3& m); // Les "consts" ont dû être enlevés
Vector3 operator*(Matrix3& m, Vector3 v); // Pour les multiplications avec des vecteurs
Matrix3 operator/(const Matrix3& m, float& d);

