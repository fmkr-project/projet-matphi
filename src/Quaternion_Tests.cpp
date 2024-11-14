#include <iostream>
#include <cmath>
#include "Quaternion.h"
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
    Quaternion q;
    assertEqual(q.x, 1.0f, "DefaultConstructor x");
    assertEqual(q.y, 0.0f, "DefaultConstructor y");
    assertEqual(q.z, 0.0f, "DefaultConstructor z");
    assertEqual(q.w, 0.0f, "DefaultConstructor w");
}

void testParameterizedConstructor() {
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    assertEqual(q.x, 1.0f, "ParameterizedConstructor x");
    assertEqual(q.y, 2.0f, "ParameterizedConstructor y");
    assertEqual(q.z, 3.0f, "ParameterizedConstructor z");
    assertEqual(q.w, 4.0f, "ParameterizedConstructor w");
}

void testNeg() {
    Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
    Quaternion negQ = Quaternion::Neg(q);
    assertEqual(negQ.x, -1.0f, "Neg x");
    assertEqual(negQ.y, 2.0f, "Neg y");
    assertEqual(negQ.z, -3.0f, "Neg z");
    assertEqual(negQ.w, 4.0f, "Neg w");
}

void testMagnitude() {
    Quaternion q(1.0f, 2.0f, 2.0f, 2.0f);
    assertEqual(Quaternion::Magnitude(q), 3.0f, "Magnitude");
}

void testConjugate() {
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion conjugateQ = Quaternion::Conjugate(q);
    assertEqual(conjugateQ.x, -2.0f, "Conjugate x");
    assertEqual(conjugateQ.y, -3.0f, "Conjugate y");
    assertEqual(conjugateQ.z, -4.0f, "Conjugate z");
    assertEqual(conjugateQ.w, 1.0f, "Conjugate w");
}

void testInverse() {
    Quaternion q(1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion inverseQ = Quaternion::Inverse(q);
    assertEqual(inverseQ.x, -1.0f, "Inverse x");
    assertEqual(inverseQ.y, 0.0f, "Inverse y");
    assertEqual(inverseQ.z, 0.0f, "Inverse z");
    assertEqual(inverseQ.w, 1.0f, "Inverse w");
}

void testDot() {
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(2.0f, 3.0f, 4.0f, 5.0f);
    assertEqual(Quaternion::Dot(q1, q2), 40.0f, "DotProduct");
}

void testPower() {
    Quaternion q(0.0f, 1.0f, 0.0f, 0.0f);
    Quaternion result = Quaternion::Power(q, 2.0f);
    assertEqual(result.x, 0.0f, "Power x");
    assertEqual(result.y, 1.0f, "Power y");
    assertEqual(result.z, 0.0f, "Power z");
    assertEqual(result.w, -1.0f, "Power w");
}

void testSlerp() {
    Quaternion q1(0.0f, 0.0f, 0.0f, 1.0f);
    Quaternion q2(1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion slerpQ = Quaternion::Slerp(q1, q2, 0.5f);
    assertEqual(slerpQ.x, 0.707107f, "Slerp x");
    assertEqual(slerpQ.y, 0.0f, "Slerp y");
    assertEqual(slerpQ.z, 0.0f, "Slerp z");
    assertEqual(slerpQ.w, 0.707107f, "Slerp w");
}

void testAddition() {
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(2.0f, 3.0f, 4.0f, 5.0f);
    Quaternion result = q1 + q2;
    assertEqual(result.x, 3.0f, "Addition x");
    assertEqual(result.y, 5.0f, "Addition y");
    assertEqual(result.z, 7.0f, "Addition z");
    assertEqual(result.w, 9.0f, "Addition w");
}

void testMultiplication() {
    Quaternion q1(1.0f, 0.0f, 1.0f, 0.0f);
    Quaternion q2(1.0f, 0.5f, 0.5f, 0.75f);
    Quaternion result = q1 * q2;
    assertEqual(result.x, 0.75f, "Multiplication x");
    assertEqual(result.y, 1.25f, "Multiplication y");
    assertEqual(result.z, 0.25f, "Multiplication z");
    assertEqual(result.w, -0.5f, "Multiplication w");
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testNeg();
    testMagnitude();
    testConjugate();
    testInverse();
    testDot();
    testPower();
    testSlerp();
    testAddition();
    testMultiplication();

    return 0;
}
