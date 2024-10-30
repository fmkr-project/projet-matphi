#pragma once

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
	Matrix4 crossProduct(const Matrix4& m) const;
	Matrix4 translation(float x, float y);
	Matrix4 rotation(float angle);
	Matrix4 scalling(float sx, float sy);
};

Matrix4 operator+(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator-(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m, float d);
Matrix4 operator*(float d, const Matrix4& m);
Matrix4 operator/(const Matrix4& m, float& d);

