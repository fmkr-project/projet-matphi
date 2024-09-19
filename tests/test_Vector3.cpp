#include <iostream>
#include "vector3d.h"

void testAddition() {
    Vector3d v1(1.0f, 2.0f, 3.0f);
    Vector3d v2(4.0f, 5.0f, 6.0f);
    Vector3d result = v1 + v2;
    std::cout << "Addition (1,2,3) + (4,5,6): ";
    result.print();
}

void testSubtraction() {
    Vector3d v1(1.0f, 2.0f, 3.0f);
    Vector3d v2(4.0f, 5.0f, 6.0f);
    Vector3d result = v1 - v2;
    std::cout << "Subtraction (1,2,3) - (4,5,6): ";
    result.print();
}

void testScalarMultiplication() {
    Vector3d v(1.0f, 2.0f, 3.0f);
    float scalar = 2.0f;
    Vector3d result1 = v * scalar;
    Vector3d result2 = scalar * v;
    std::cout << "Scalar multiplication (1,2,3) * 2: ";
    result1.print();
    std::cout << "Scalar multiplication 2 * (1,2,3): ";
    result2.print();
}

void testComponentWiseMultiplication() {
    Vector3d v1(1.0f, 2.0f, 3.0f);
    Vector3d v2(4.0f, 5.0f, 6.0f);
    Vector3d result = v1 * v2; // Utilisation de l'opérateur de multiplication composante par composante
    std::cout << "Component-wise multiplication (1,2,3) * (4,5,6): ";
    result.print();
}

void testDotProduct() {
    Vector3d v1(1.0f, 2.0f, 3.0f);
    Vector3d v2(4.0f, 5.0f, 6.0f);
    float result = v1.dotProduct(v2);
    std::cout << "Dot product (1,2,3) . (4,5,6): " << result << std::endl;
}

void testCrossProduct() {
    Vector3d v1(1.0f, 0.0f, 0.0f);
    Vector3d v2(0.0f, 1.0f, 0.0f);
    Vector3d result = v1.crossProduct(v2);
    std::cout << "Cross product (1,0,0) x (0,1,0): ";
    result.print();
}

// Suppression des tests de magnitude et de normalisation car ces méthodes ne sont pas présentes dans Vector3d

int main() {
    std::cout << "Testing Vector3d class methods:" << std::endl;

    testAddition();
    testSubtraction();
    testScalarMultiplication();
    testComponentWiseMultiplication();
    testDotProduct();
    testCrossProduct();

    return 0;
}
