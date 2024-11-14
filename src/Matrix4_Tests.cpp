#include <iostream>
#include <cmath>
#include "Matrix4.h"
#include "Vector3.h"  

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void assertEqual(float a, float b, const std::string& testName) {
    if (std::abs(a - b) > 1e-5) {
        std::cout << "Test " << testName << " failed: " << a << " != " << b << std::endl;
    }
    else {
        std::cout << "Test " << testName << " passed." << std::endl;
    }
}

void assertTrue(bool condition, const std::string& testName) {
    if (!condition) {
        std::cout << "Test " << testName << " failed: condition is false." << std::endl;
    }
    else {
        std::cout << "Test " << testName << " passed." << std::endl;
    }
}

void testDefaultConstructor() {
    Matrix4 m;
    bool passed = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m.getElement(i, j) != 0.0f) passed = false;
        }
    }
    assertTrue(passed, "DefaultConstructor");
}

void testParameterizedConstructor() {
    float values[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    Matrix4 m(values);
    bool passed = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m.getElement(i, j) != values[i][j]) passed = false;
        }
    }
    assertTrue(passed, "ParameterizedConstructor");
}

void testIdentity() {
    Matrix4 identity = Matrix4::identity();
    bool passed = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (identity.getElement(i, j) != (i == j ? 1.0f : 0.0f)) passed = false;
        }
    }
    assertTrue(passed, "Identity");
}

void testDeterminant() {
    Matrix4 m;
    float values[4][4] = { {1, 2, 3, 4}, {0, 1, 2, 3}, {4, 0, 1, 2}, {3, 4, 0, 1} };
    m = Matrix4(values);
    assertEqual(m.determinant(), -24.0f, "Determinant");
}

void testInverse() {
    float values[4][4] = { {4, 7, 2, 1}, {0, 5, 1, 0}, {3, 0, 1, 2}, {1, 6, 2, 3} };
    Matrix4 m(values);
    Matrix4 inv = m.inverse();
    Matrix4 identity = Matrix4::identity();
    assertTrue((m * inv) == identity, "Inverse");
}

void testTrace() {
    float values[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    Matrix4 m(values);
    assertEqual(m.trace(), 34.0f, "Trace");
}

void testTranslation() {
    Vector3 translation(3, 4, 5);
    Matrix4 m = Matrix4::translation(translation);
    assertEqual(m.getElement(0, 3), 3.0f, "TranslationX");
    assertEqual(m.getElement(1, 3), 4.0f, "TranslationY");
    assertEqual(m.getElement(2, 3), 5.0f, "TranslationZ");
    assertEqual(m.getElement(3, 3), 1.0f, "TranslationW");
}

void testScaling() {
    Vector3 scale(2, 3, 4);
    Matrix4 m = Matrix4::scalling(scale);
    assertEqual(m.getElement(0, 0), 2.0f, "ScalingX");
    assertEqual(m.getElement(1, 1), 3.0f, "ScalingY");
    assertEqual(m.getElement(2, 2), 4.0f, "ScalingZ");
}

void testRotationX() {
    float angle = M_PI / 4;  // 45 degrees
    Matrix4 m = Matrix4::rotationAxis(angle, "x");
    assertEqual(m.getElement(1, 1), std::cos(angle), "RotationX_Cos");
    assertEqual(m.getElement(1, 2), std::sin(angle), "RotationX_Sin");
    assertEqual(m.getElement(2, 1), -std::sin(angle), "RotationX_-Sin");
    assertEqual(m.getElement(2, 2), std::cos(angle), "RotationX_Cos2");
}

void testOperatorAdd() {
    float values1[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    float values2[4][4] = { {16, 15, 14, 13}, {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1} };
    Matrix4 m1(values1), m2(values2);
    Matrix4 result = m1 + m2;
    Matrix4 expected = Matrix4::identity();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            expected.setElement(i, j, values1[i][j] + values2[i][j]);
        }
    }
    assertTrue(result == expected, "OperatorAdd");
}

void testMatrix3ToMatrix4() {
    // Création d'une matrice 3x3 de test
    float values3x3[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Matrix3 m3(values3x3);

    // Conversion de Matrix3 à Matrix4
    Matrix4 result = Matrix4::Matrix3ToMatrix4(m3);

    // Vérification des éléments de la matrice 3x3 dans la matrice 4x4
    bool passed = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (result.getElement(i, j) != m3.getElement(i, j)) passed = false;
        }
    }

    // Vérification de la dernière colonne
    for (int i = 0; i < 3; ++i) {
        if (result.getElement(i, 3) != 0.0f) passed = false;
    }

    // Vérification de la dernière ligne
    if (result.getElement(3, 0) != 0.0f || result.getElement(3, 1) != 0.0f ||
        result.getElement(3, 2) != 0.0f || result.getElement(3, 3) != 1.0f) {
        passed = false;
        }
    
    assertTrue(passed, "Matrix3ToMatrix4");
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testIdentity();
    testDeterminant();
    testInverse();
    testTrace();
    testTranslation();
    testScaling();
    testRotationX();
    testOperatorAdd();
    testMatrix3ToMatrix4();
    return 0;
}
