#include "Matrix3.h"
#include <iostream>
using namespace std;

//Constructors
Matrix3::Matrix3() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = 0.0f;
		}
	}
}

Matrix3::Matrix3(float m[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = m[i][j];
		}
	}
}

Matrix3::Matrix3(const Matrix3& m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = m.matrix[i][j];
		}
	}
}

Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
	matrix[0][0] = a;
	matrix[0][1] = b;
	matrix[0][2] = c;
	matrix[1][0] = d;
	matrix[1][1] = e;
	matrix[1][2] = f;
	matrix[2][0] = g;
	matrix[2][1] = h;
	matrix[2][2] = i;
}

//Destructor
Matrix3::~Matrix3() {

}


//Getter & Setter
float Matrix3::getElement(int i, int j) {
	if (i >= 3 || j >= 3) {
		throw std::runtime_error("Invalid Arguments");
	}
	return matrix[i][j];
}

void Matrix3::setElement(int i, int j, float val) {
	if (i >= 3 || j >= 3) {
		throw std::runtime_error("Invalid Arguments");
	}
	matrix[i][j] = val;
}

//Methods
Matrix3& Matrix3::operator+=(const Matrix3& m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] += m.matrix[i][j];
		}
	}
	return *this;
}

Matrix3& Matrix3::operator+=(float& d) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] += d;
		}
	}
	return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] -= m.matrix[i][j];
		}
	}
	return *this;
}

Matrix3& Matrix3::operator-=(float& d) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] -= d;
		}
	}
	return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += matrix[i][k] * matrix[k][j];
			}
			matrix[i][j] = sum;
		}
	}
	return *this;
}

Matrix3& Matrix3::operator*=(float& d) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] *= d;
		}
	}
	return *this;
}

Matrix3& Matrix3::operator/=(float& d) {
	if (d == 0) {
		throw std::runtime_error("Division by 0.");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[i][j] /= d;
		}
	}
	return *this;
}

void Matrix3::operator=(const Matrix3& other) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

bool Matrix3::operator==(const Matrix3& m) const {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] != m.matrix[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix3::operator!=(const Matrix3& m) const {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] != m.matrix[i][j]) {
				return true;
			}
		}
	}
	return false;
}

float Matrix3::determinant() const {
	float aei = matrix[0][0] * matrix[1][1] * matrix[2][2];
	float afh = matrix[0][0] * matrix[1][2] * matrix[2][1];
	float bfg = matrix[0][1] * matrix[1][2] * matrix[2][0];
	float bdi = matrix[0][1] * matrix[1][0] * matrix[2][2];
	float cdh = matrix[0][2] * matrix[1][0] * matrix[2][1];
	float ceg = matrix[0][2] * matrix[1][1] * matrix[2][0];

	return aei - afh + bfg - bdi + cdh - ceg;
}

Matrix3 Matrix3::transposition() const {
	Matrix3 res = Matrix3();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res.matrix[i][j] = matrix[j][i];
		}
	}
	return res;
}

Matrix3 Matrix3::comatrix() const {
	Matrix3 cofactorMatrix;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			// Calculate determinant 2x2
			float minor[2][2];
			for (int k = 0, row = 0; k < 3; ++k) {
				if (k == i) continue; // Ignore row i
				for (int l = 0, col = 0; l < 3; ++l) {
					if (l == j) continue; // Ignore column j
					minor[row][col++] = matrix[k][l];
				}
				row++;
			}
			// Determinant 2x2
			float detMinor = minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];
			// Cofactor
			cofactorMatrix.matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * detMinor;
		}
	}

	return cofactorMatrix; // Return Matrix of cofactors
}

Matrix3 Matrix3::inverse() const {
	float det = determinant();
	if (det == 0) {
		throw std::runtime_error("Non reversible matrix (determinant nul).");
	}

	Matrix3 cofactorMatrix = comatrix();
	Matrix3 inverseMatrix;

	// Apply formula
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			inverseMatrix.matrix[i][j] = cofactorMatrix.matrix[j][i] / det;
		}
	}

	return inverseMatrix;
}

// ============================================================================
// Operateurs externes ========================================================
// ============================================================================

Matrix3 operator+(const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 mat3 = Matrix3(m1);
	
	return mat3 += m2;
}

Matrix3 operator-(const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 mat3 = Matrix3(m1);

	return mat3 -= m2;
}

Matrix3 operator*(const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 mat3 = Matrix3(m1);

	return mat3 *= m2;
}

Matrix3 operator*(const Matrix3& m, float d)
{
	Matrix3 mat3 = Matrix3(m);

	return mat3 *= d;
}

Matrix3 operator*(float d, const Matrix3& m)
{
	Matrix3 mat3 = Matrix3(m);

	return mat3 *= d;
}

Matrix3 operator/(const Matrix3& m, float& d)
{
	Matrix3 mat3 = Matrix3(m);

	return mat3 /= d;
}
