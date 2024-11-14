#pragma once
#include <string>     
#include "Vector3.h" 
#include "Matrix3.h"
using namespace std;

class Matrix4
{
private:
	float matrix[4][4];

public:

	//Constructors & destructor
	Matrix4();
	Matrix4(float m[4][4]);
	Matrix4(const Matrix4& m);
	~Matrix4();

	//Constants
	static Matrix4 identity();

	//Getter & setter
	float getElement(int i, int j);
	void setElement(int i, int j, float val);

	//Methods
	Matrix4& operator+=(const Matrix4& m);
	Matrix4& operator+=(float& d);
	Matrix4& operator-=(const Matrix4& m);
	Matrix4& operator-=(float& d);
	Matrix4& operator*=(const Matrix4& m);
	Matrix4& operator*=(float& d);
	Matrix4& operator/=(float& d);
	void operator=(const Matrix4& m);
	bool operator==(const Matrix4& m) const;
	bool operator!=(const Matrix4& m) const;

	float determinant() const;
	Matrix4 transposition() const;
	Matrix4 comatrix() const;
	Matrix4 inverse() const;
	float trace() const;
	static Matrix4 translation(Vector3 translation);
	static Matrix4 rotationAxis(float angle, string axis);
	static Matrix4 rotation(Vector3 rotation);
	static Matrix4 scalling(Vector3 scale);
	static Matrix4 Matrix3ToMatrix4(const Matrix3& m);
};

Matrix4 operator+(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator-(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m, float d);
Matrix4 operator*(float d, const Matrix4& m);
Matrix4 operator/(const Matrix4& m, float& d);

