#include "Matrix4.h"
#include <iostream>
#include "Matrix3.h"
using namespace std;

//Constructors
Matrix4::Matrix4() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = 0.0f;
		}
	}
}

Matrix4::Matrix4(float m[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = m[i][j];
		}
	}
}

Matrix4::Matrix4(const Matrix4& m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = m.matrix[i][j];
		}
	}
}

//Destructor
Matrix4::~Matrix4() {

}


//Getter & Setter
float Matrix4::getElement(int i, int j) {
	if (i >= 4 || j >= 4) {
		throw std::runtime_error("Invalid Arguments");
	}
	return matrix[i][j];
}

void Matrix4::setElement(int i, int j, float val) {
	if (i >= 4 || j >= 4) {
		throw std::runtime_error("Invalid Arguments");
	}
	matrix[i][j] = val;
}

//Methods
Matrix4& Matrix4::operator+=(const Matrix4& m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] += m.matrix[i][j];
		}
	}
	return *this;
}

Matrix4& Matrix4::operator+=(float& d) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] += d;
		}
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] -= m.matrix[i][j];
		}
	}
	return *this;
}

Matrix4& Matrix4::operator-=(float& d) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] -= d;
		}
	}
	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += matrix[i][k] * matrix[k][j];
			}
			matrix[i][j] = sum;
		}
	}
	return *this;
}

Matrix4& Matrix4::operator*=(float& d) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] *= d;
		}
	}
	return *this;
}

Matrix4& Matrix4::operator/=(float& d) {
	if (d == 0) {
		throw std::runtime_error("Division by 0.");
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] /= d;
		}
	}
	return *this;
}

void Matrix4::operator=(const Matrix4& other) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

bool Matrix4::operator==(const Matrix4& m) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] != m.matrix[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix4::operator!=(const Matrix4& m) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] != m.matrix[i][j]) {
				return true;
			}
		}
	}
	return false;
}

float Matrix4::determinant() const {
	Matrix3 submatrix1 = Matrix3(matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][1], matrix[2][2], matrix[2][3], matrix[3][1], matrix[3][2], matrix[3][3]);
	Matrix3 submatrix2 = Matrix3(matrix[1][0], matrix[1][2], matrix[1][3], matrix[2][0], matrix[2][2], matrix[2][3], matrix[3][0], matrix[3][2], matrix[3][3]);
	Matrix3 submatrix3 = Matrix3(matrix[1][0], matrix[1][1], matrix[1][3], matrix[2][0], matrix[2][1], matrix[2][3], matrix[3][0], matrix[3][1], matrix[3][3]);
	Matrix3 submatrix4 = Matrix3(matrix[1][0], matrix[1][1], matrix[1][2], matrix[2][0], matrix[2][1], matrix[2][2], matrix[3][0], matrix[3][1], matrix[3][2]);

	float det1 = submatrix1.determinant();
	float det2 = submatrix2.determinant();
	float det3 = submatrix3.determinant();
	float det4 = submatrix4.determinant();

	return matrix[0][0] * det1 - matrix[0][1] * det2 + matrix[0][2] * det3 - matrix[0][3] * det4 ;
}

Matrix4 Matrix4::transposition() const {
	Matrix4 res = Matrix4();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.matrix[i][j] = matrix[j][i];
		}
	}
	return res;
}

Matrix4 Matrix4::comatrix() const {
	Matrix4 cofactorMatrix;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			// Construire le mineur 3x3 pour l'élément (i, j) en utilisant la classe Matrix3
			Matrix3 minorMatrix;
			for (int k = 0, row = 0; k < 4; ++k) {
				if (k == i) continue; // Ignore la ligne i
				for (int l = 0, col = 0; l < 4; ++l) {
					if (l == j) continue; // Ignore la colonne j
					minorMatrix.setElement(row, col++, matrix[k][l]);
				}
				row++;
			}
			// Calculer le déterminant du mineur 3x3
			float detMinor = minorMatrix.determinant();

			// Calculer le cofacteur avec alternance de signe
			cofactorMatrix.matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * detMinor;
		}
	}

	return cofactorMatrix; // Retourne la matrice des cofacteurs
}


Matrix4 Matrix4::inverse() const {
	float det = determinant();
	if (det == 0) {
		throw std::runtime_error("Matrice non réversible (déterminant nul).");
	}

	// Calculer la comatrice
	Matrix4 cofactorMatrix = comatrix();

	// Calculer l'inverse en transposant la comatrice et en divisant par le déterminant
	Matrix4 inverseMatrix;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			// Transposer la comatrice (échanger i et j) et diviser par le déterminant
			inverseMatrix.matrix[i][j] = cofactorMatrix.matrix[j][i] / det;
		}
	}

	return inverseMatrix;
}


// ============================================================================
// Operateurs externes ========================================================
// ============================================================================

Matrix4 operator+(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 mat4 = Matrix4(m1);

	return mat4 += m2;
}

Matrix4 operator-(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 mat4 = Matrix4(m1);

	return mat4 -= m2;
}

Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 mat4 = Matrix4(m1);

	return mat4 *= m2;
}

Matrix4 operator*(const Matrix4& m, float d)
{
	Matrix4 mat4 = Matrix4(m);

	return mat4 *= d;
}

Matrix4 operator*(float d, const Matrix4& m)
{
	Matrix4 mat4 = Matrix4(m);

	return mat4 *= d;
}

Matrix4 operator/(const Matrix4& m, float& d)
{
	Matrix4 mat4 = Matrix4(m);

	return mat4 /= d;
}
