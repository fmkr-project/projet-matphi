#include <iostream>
#include "Vector3.h"

void testAddition() {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 result = v1 + v2;
    std::cout << "Addition (1,2,3) + (4,5,6): ";
    result.print();
}

void testSubtraction() {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 result = v1 - v2;
    std::cout << "Subtraction (1,2,3) - (4,5,6): ";
    result.print();
}

void testScalarMultiplication() {
    Vector3 v(1.0f, 2.0f, 3.0f);
    float scalar = 2.0f;
    Vector3 result1 = v * scalar;
    Vector3 result2 = scalar * v;
    std::cout << "Scalar multiplication (1,2,3) * 2: ";
    result1.print();
    std::cout << "Scalar multiplication 2 * (1,2,3): ";
    result2.print();
}

void testComponentWiseMultiplication() {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 result = Vector3::scale(v1, v2);
    std::cout << "Component-wise multiplication (1,2,3) * (4,5,6): ";
    result.print();
}

void testDotProduct() {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    float result = Vector3::dot(v1, v2);
    std::cout << "Dot product (1,2,3) . (4,5,6): " << result << std::endl;
}

void testCrossProduct() {
    Vector3 v1(1.0f, 0.0f, 0.0f);
    Vector3 v2(0.0f, 1.0f, 0.0f);
    Vector3 result = Vector3::cross(v1, v2);
    std::cout << "Cross product (1,0,0) x (0,1,0): ";
    result.print();
}

void testMagnitude() {
    Vector3 v(1.0f, 2.0f, 2.0f);
    float result = v.magnitude();
    std::cout << "Magnitude of (1,2,2): " << result << std::endl;
}

void testSqrMagnitude() {
    Vector3 v(1.0f, 2.0f, 2.0f);
    float result = v.sqrMagnitude();
    std::cout << "Square magnitude of (1,2,2): " << result << std::endl;
}

void testNormalization() {
    Vector3 v(3.0f, 0.0f, 4.0f);
    Vector3 result = v.normalized();
    std::cout << "Normalized vector of (3,0,4): ";
    result.print();
}

int main() {
    std::cout << "Testing Vector3 class methods:" << std::endl;

    testAddition();
    testSubtraction();
    testScalarMultiplication();
    testComponentWiseMultiplication();
    testDotProduct();
    testCrossProduct();
    testMagnitude();
    testSqrMagnitude();
    testNormalization();

    return 0;
}
