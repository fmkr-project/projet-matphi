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

	//Getter & setter
	float getElement(int i, int j);
	void setElement(int i, int j, float val);

	//Methods
	Matrix3& operator+=(const Matrix3& m);
	Matrix3& operator+=(float& d);
	Matrix3& operator-=(const Matrix3& m);
	Matrix3& operator-=(float& d);
	Matrix3& operator*=(const Matrix3& m);
	Matrix3& operator*=(float& d);
	Matrix3& operator/=(float& d);
	void operator=(const Matrix3& m);
	bool operator==(const Matrix3& m) const;
	bool operator!=(const Matrix3& m) const;

	float determinant() const;
	Matrix3 transposition() const;
	Matrix3 comatrix() const;
	Matrix3 inverse() const;
	float trace() const;
	Matrix3 crossProduct(const Matrix3& m) const;
	Matrix3 translation(float x, float y);
	Matrix3 rotation(float angle);
	Matrix3 scalling(float sx, float sy);
};

Matrix3 operator+(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator-(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator*(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator*(const Matrix3& m, float d);
Matrix3 operator*(float d, const Matrix3& m);
Matrix3 operator*(Vector3 v, const Matrix3& m);
Matrix3 operator*(const Matrix3& m, Vector3 v);
Matrix3 operator/(const Matrix3& m, float& d);

