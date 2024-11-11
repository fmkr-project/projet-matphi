#include <iostream>
#include "Matrix3.h"
#include "Vector3.h"  

void assertEqual(float a, float b, const std::string& testName) {
    if (std::abs(a - b) > 1e-5) {
        std::cout << "Test " << testName << " failed: " << a << " != " << b << std::endl;
    } else {
        std::cout << "Test " << testName << " passed." << std::endl;
    }
}

void assertTrue(bool condition, const std::string& testName) {
    if (!condition) {
        std::cout << "Test " << testName << " failed: condition is false." << std::endl;
    } else {
        std::cout << "Test " << testName << " passed." << std::endl;
    }
}

void testDefaultConstructor() {
    Matrix3 m;
    bool passed = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m.getElement(i, j) != 0.0f) passed = false;
        }
    }
    assertTrue(passed, "DefaultConstructor");
}

void testParameterizedConstructor() {
    float values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3 m(values);
    bool passed = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m.getElement(i, j) != values[i][j]) passed = false;
        }
    }
    assertTrue(passed, "ParameterizedConstructor");
}

void testIdentity() {
    Matrix3 identity = Matrix3::identity();
    bool passed = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (identity.getElement(i, j) != ((i == j) ? 1.0f : 0.0f)) passed = false;
        }
    }
    assertTrue(passed, "Identity");
}

void testDeterminant() {
    Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
    assertEqual(m.determinant(), 0.0f, "Determinant (Singular Matrix)");

    Matrix3 m2(2, 1, 3, 4, -1, 6, 1, 5, -2);
    assertEqual(m2.determinant(), -63.0f, "Determinant (Non-Singular Matrix)");
}

void testInverse() {
    Matrix3 m(1, 2, 3, 0, 1, 4, 5, 6, 0);
    Matrix3 inv = m.inverse();
    Matrix3 identity = Matrix3::identity();
    Matrix3 result = m * inv;
    bool passed = result == identity;
    assertTrue(passed, "Inverse");
}

void testTrace() {
    Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
    assertEqual(m.trace(), 15.0f, "Trace");
}

void testOperatorAdd() {
    Matrix3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 m2(9, 8, 7, 6, 5, 4, 3, 2, 1);
    Matrix3 result = m1 + m2;
    Matrix3 expected(10, 10, 10, 10, 10, 10, 10, 10, 10);
    assertTrue(result == expected, "OperatorAdd");
}


void testOperatorMultiplyMatrix() {
    Matrix3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 m2(9, 8, 7, 6, 5, 4, 3, 2, 1);
    Matrix3 result = m1 * m2;
    Matrix3 expected(30, 24, 18, 84, 69, 54, 138, 114, 90);
    assertTrue(result == expected, "OperatorMultiplyMatrix");
}

void testSetAndGetElement() {
    Matrix3 m;
    m.setElement(0, 0, 5.0f);
    assertEqual(m.getElement(0, 0), 5.0f, "SetAndGetElement");
    try {
        m.setElement(3, 3, 1.0f);
        std::cout << "Test SetAndGetElement (Invalid Argument) failed: No exception thrown" << std::endl;
    } catch (const std::runtime_error&) {
        std::cout << "Test SetAndGetElement (Invalid Argument) passed." << std::endl;
    }
}

void testOperatorEqual() {
    Matrix3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 m2(1, 2, 3, 4, 5, 6, 7, 8, 9);
    assertTrue(m1 == m2, "OperatorEqual");
}

void testOperatorNotEqual() {
    Matrix3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 m2(9, 8, 7, 6, 5, 4, 3, 2, 1);
    assertTrue(m1 != m2, "OperatorNotEqual");
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testIdentity();
    testDeterminant();
    testInverse();
    testTrace();
    testOperatorAdd();
    testOperatorMultiplyMatrix();
    testSetAndGetElement();
    testOperatorEqual();
    testOperatorNotEqual();
    
    return 0;
}
