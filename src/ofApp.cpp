#include "ofApp.h"
#include "Particle.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "World.h"
#include "ParticleFriction.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"

#include <of3dGraphics.h>


float timeSinceLastSpawn = float(3.);

float mouseXPos = 0;
float mouseYPos = 0;


//--------------------------------------------------------------
void ofApp::setup()
{
    std::cout << "Running tests of Matrix3..." << std::endl;
    runTestsMatrix3();
    std::cout << "Running tests of Matrix4..." << std::endl;
    runTestsMatrix4();
    std::cout << "Running tests of Quaternion..." << std::endl;
    runTestsQuaternion();
    std::cout << "Tests completed." << std::endl;
	box.set(500);
    ofBackground(0);
    centerStart = Vector3(500, 500, 0);
    centerBox = new Particle(centerStart, Vector3(), 100, 10);
    rigidBox = RigidBodyBox(*centerBox,Quaternion(),Vector3(),150,150,150);
    isMoving = false;
    startPoint = new Vector3(500, 700, 0);
}

//--------------------------------------------------------------
void ofApp::update()
{
    //Update the forces in the registry
    timeSinceLastSpawn += ofGetLastFrameTime();
    if (timeSinceLastSpawn < 3.0f) { 
        rigidBox.move();
    }
    else {
        timeSinceLastSpawn = 3.0f;
        isMoving = false;
        rigidBox.setCenterMass(*centerBox);
        rigidBox.setAngularVelocity(Vector3());
        rigidBox.setOrientation(Quaternion());
    }
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255, 255, 0);
    ofDrawIcoSphere(500,700, 10);
    rigidBox.draw(ofColor(100, 100, 255));
    rigidBox.getCenterMass().draw();
    rigidBox.drawEnclosingSphere(ofColor(100,255,100)); // a enlever si genant
    ofSetColor(255);
    ofDrawBitmapString("Click on the box to apply an impulsion on it", 10, 20);
    ofDrawBitmapString("The box automatically returns to the starting position after 3 seconds", 10, 35);
    ofDrawBitmapString("Press 't' to bring back the box to the starting position earlier", 10, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 't') timeSinceLastSpawn = 3.0f;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    mouseXPos = x;
    mouseYPos = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
    Vector3* mousePos = new Vector3(x, y, ofRandom(25,50) * pow(-1, static_cast<int>(ofRandom(1, 6))));
    if (x <= centerBox->getPosition().getX() + rigidBox.getWidth() 
        && x >= centerBox->getPosition().getX() - rigidBox.getWidth() 
        && y <= centerBox->getPosition().getY() + rigidBox.getHeight() 
        && y >= centerBox->getPosition().getY() - rigidBox.getHeight()
        && !isMoving) 
    {
        Vector3 impulse = *mousePos - *startPoint;
        Vector3 temp =
            {
            -impulse.getX(),
            impulse.getY(),
            impulse.getZ()
            };
        //std::cout << impulse.getX() << std::endl;
        //std::cout << impulse.getY() << std::endl;
        rigidBox.applyForceAt(impulseStrength * temp, *mousePos, ofGetLastFrameTime());
        timeSinceLastSpawn = 0.f;
        isMoving = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::SpawnParticle(float speed, float mass, ofColor col)
{
    auto newParticle = new Particle(
        Vector3(mouseXPos, mouseYPos - 100),
        *Vector3::zero,
        mass,
        10.,
        col
    );
    myParticles.push_back(newParticle);
    numberParticles++;
    //myBoundParticles.push_back(newParticle);
    //nbBoundParticles++;

    //Add forces to the new particule
    //force_registry->add(newParticle, force_friction);
    //force_registry->add(newParticle, force_gravity);
    //force_registry->add(newParticle, force_spring);

    //collision_manager.add_particle(newParticle);
    //World::addParticle(newParticle);

    std::cout << "New particle created @" << mouseXPos << ' ' << mouseYPos << '\n';
    //collision_manager._debug_print_all_particles();
}

void ofApp::DrawSpring(Particle p)
{
    auto x = p.getPosition().getX();
    auto y = p.getPosition().getY();
    ofDrawLine(x, y, mouseXPos, mouseYPos);
}

bool floatEquals(float a, float b, float tolerance = 0.0001f)
{
    return std::fabs(a - b) < tolerance;
}


//--------------------------------------------Tests--------------------------

std::ostream& operator<<(std::ostream& os, const Matrix3& matrix) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            os << std::setw(10) << matrix.matrix[i][j] << " ";
        }
        os << "\n"; // Nouvelle ligne apr�s chaque ligne de la matrice
    }
    return os;
}

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

void testDefaultConstructorMatrix3() {
    Matrix3 m;
    bool passed = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m.getElement(i, j) != 0.0f) passed = false;
        }
    }
    assertTrue(passed, "DefaultConstructor");
}

void testParameterizedConstructorMatrix3() {
    float values[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
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
    assertEqual(m2.determinant(), 21.0f, "Determinant (Non-Singular Matrix)");
}

bool matricesAreEqual(const Matrix3& m1, const Matrix3& m2, float tolerance = 1e-5) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (std::abs(m1.matrix[i][j] - m2.matrix[i][j]) > tolerance) {
                std::cout << "Mismatch at (" << i << ", " << j << "): "
                    << m1.matrix[i][j] << " != " << m2.matrix[i][j] << std::endl;
                return false;
            }
        }
    }
    return true;
}


void testInverse() {
    Matrix3 m(1, 2, 3, 0, 1, 4, 5, 6, 0);

    try {
        // Calculer l'inverse
        Matrix3 inv = m.inverse();

        // Afficher l'inverse
        std::cout << "Calculated inverse:\n" << inv << std::endl;

        // Crer la matrice identit
        Matrix3 identity = Matrix3::identity();

        // Calculer le produit m * inv
        Matrix3 result = m * inv;
        std::cout << "Result of m * inv (should be identity):\n" << result << std::endl;

        // Afficher la matrice identit attendue
        std::cout << "Expected identity matrix:\n" << identity << std::endl;

        // Vrifier la matrice rsultante
        bool passed = matricesAreEqual(result, identity, 1e-5);
        if (!passed) {
            std::cout << "Test failed! Result is not the identity matrix.\n";
        }
        assertTrue(passed, "Inverse");

    }
    catch (const std::exception& e) {
        std::cout << "Test Inverse failed with exception: " << e.what() << std::endl;
        assertTrue(false, "Inverse");
    }
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
    }
    catch (const std::runtime_error&) {
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

void ofApp::runTestsMatrix3() {

    testDefaultConstructorMatrix3();
    testParameterizedConstructorMatrix3();
    testIdentity();
    testDeterminant();
    testInverse();
    testTrace();
    testOperatorAdd();
    testOperatorMultiplyMatrix();
    testSetAndGetElement();
    testOperatorEqual();
    testOperatorNotEqual();
}


//----------------------------------------------------------------------------------

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


bool matricesAreEqual4(const Matrix4& m1, const Matrix4& m2, float tolerance = 1e-5) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (std::abs(m1.matrix[i][j] - m2.matrix[i][j]) > tolerance) {
                std::cout << "Mismatch at (" << i << ", " << j << "): "
                    << m1.matrix[i][j] << " != " << m2.matrix[i][j] << std::endl;
                return false;
            }
        }
    }
    return true;
}


void testDefaultConstructorMatrix4() {
    Matrix4 m;
    bool passed = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m.getElement(i, j) != 0.0f) passed = false;
        }
    }
    assertTrue(passed, "DefaultConstructor");
}

void testParameterizedConstructorMatrix4() {
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



void testIdentityMatrix4() {
    Matrix4 identity = Matrix4::identity();
    bool passed = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (identity.getElement(i, j) != (i == j ? 1.0f : 0.0f)) passed = false;
        }
    }
    assertTrue(passed, "Identity");
}

void testDeterminantMatrix4() {
    Matrix4 m;
    float values[4][4] = { {1, 2, 3, 4}, {0, 1, 2, 3}, {4, 0, 1, 2}, {3, 4, 0, 1} };
    m = Matrix4(values);
    assertEqual(m.determinant(), 25.0f, "Determinant");
}


void testInverseMatrix4() {
    float values[4][4] = {
        {4, 7, 2, 1},
        {0, 5, 1, 0},
        {3, 0, 1, 2},
        {1, 6, 2, 3}
    };

    Matrix4 m(values);

    try {
        // Calculer l'inverse
        Matrix4 inv = m.inverse();

        // Afficher la matrice d'origine
        //std::cout << "Original matrix (m):\n" << m << std::endl;

        // Afficher l'inverse calcule
        //std::cout << "Calculated inverse (inv):\n" << inv << std::endl;

        // Crer la matrice identit attendue
        Matrix4 identity = Matrix4::identity();
        //std::cout << "Expected identity matrix:\n" << identity << std::endl;

        // Calculer le produit m * inv
        Matrix4 result = m * inv;
        //std::cout << "Result of m * inv (should be identity):\n" << result << std::endl;

        // Vrifier si le rsultat est proche de la matrice identit
        bool passed = matricesAreEqual4(result, identity, 1e-5);
        if (!passed) {
            std::cout << "Test failed! Result is not the identity matrix.\n";
        }
        assertTrue(passed, "Inverse");

    }
    catch (const std::exception& e) {
        std::cout << "Test Inverse failed with exception: " << e.what() << std::endl;
        assertTrue(false, "Inverse");
    }
}

void testTraceMatrix4() {
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

void testOperatorAddMatrix4() {
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
    // Cration d'une matrice 3x3 de test
    float values3x3[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Matrix3 m3(values3x3);

    // Conversion de Matrix3 Matrix4
    Matrix4 result = Matrix4::Matrix3ToMatrix4(m3);

    // Vrification des lments de la matrice 3x3 dans la matrice 4x4
    bool passed = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (result.getElement(i, j) != m3.getElement(i, j)) passed = false;
        }
    }

    // Vrification de la dernire colonne
    for (int i = 0; i < 3; ++i) {
        if (result.getElement(i, 3) != 0.0f) passed = false;
    }

    // Vrification de la dernire ligne
    if (result.getElement(3, 0) != 0.0f || result.getElement(3, 1) != 0.0f ||
        result.getElement(3, 2) != 0.0f || result.getElement(3, 3) != 1.0f) {
        passed = false;
    }

    assertTrue(passed, "Matrix3ToMatrix4");
}

void ofApp::runTestsMatrix4() {
    testDefaultConstructorMatrix4();
    testParameterizedConstructorMatrix4();
    testIdentityMatrix4();
    testDeterminantMatrix4();
    testInverseMatrix4();
    testTraceMatrix4();
    testTranslation();
    testScaling();
    testRotationX();
    testOperatorAddMatrix4();
    testMatrix3ToMatrix4();
}


//--------------------------------------------------------------------------------------------

void testDefaultConstructorQuaternion() {
    Quaternion q;
    assertEqual(q.w, 1.0f, "DefaultConstructor w");
    assertEqual(q.x, 0.0f, "DefaultConstructor x");
    assertEqual(q.y, 0.0f, "DefaultConstructor y");
    assertEqual(q.z, 0.0f, "DefaultConstructor z");
}

void testParameterizedConstructorQuaternion() {
    Quaternion q(4.0f, 1.0f, 2.0f, 3.0f); // w en premier
    assertEqual(q.w, 4.0f, "ParameterizedConstructor w");
    assertEqual(q.x, 1.0f, "ParameterizedConstructor x");
    assertEqual(q.y, 2.0f, "ParameterizedConstructor y");
    assertEqual(q.z, 3.0f, "ParameterizedConstructor z");
}

void testNeg() {
    Quaternion q(-4.0f, 1.0f, -2.0f, 3.0f); // w en premier
    Quaternion negQ = Quaternion::Neg(q);
    assertEqual(negQ.w, 4.0f, "Neg w");
    assertEqual(negQ.x, -1.0f, "Neg x");
    assertEqual(negQ.y, 2.0f, "Neg y");
    assertEqual(negQ.z, -3.0f, "Neg z");
}

void testMagnitude() {
    Quaternion q(1.0f, 2.0f, 2.0f, 2.0f); // w en premier
    assertEqual(Quaternion::Magnitude(q), 3.60555f, "Magnitude"); // sqrt(13)
}

void testConjugate() {
    Quaternion q(4.0f, 1.0f, 2.0f, 3.0f); // w en premier
    Quaternion conjugateQ = Quaternion::Conjugate(q);
    assertEqual(conjugateQ.w, 4.0f, "Conjugate w");
    assertEqual(conjugateQ.x, -1.0f, "Conjugate x");
    assertEqual(conjugateQ.y, -2.0f, "Conjugate y");
    assertEqual(conjugateQ.z, -3.0f, "Conjugate z");
}

void testInverseQuaternion() {
    Quaternion q(1.0f, 0.0f, 0.0f, 0.0f); // w en premier
    Quaternion inverseQ = Quaternion::Inverse(q);

    std::cout << "Original Quaternion: w=" << q.w << ", x=" << q.x << ", y=" << q.y << ", z=" << q.z << std::endl;
    std::cout << "Inverse Quaternion: w=" << inverseQ.w << ", x=" << inverseQ.x << ", y=" << inverseQ.y << ", z=" << inverseQ.z << std::endl;

    assertEqual(inverseQ.w, 1.0f, "Inverse w");
    assertEqual(inverseQ.x, 0.0f, "Inverse x");
    assertEqual(inverseQ.y, 0.0f, "Inverse y");
    assertEqual(inverseQ.z, 0.0f, "Inverse z");
}

void testDot() {
    Quaternion q1(4.0f, 1.0f, 2.0f, 3.0f); // w en premier
    Quaternion q2(5.0f, 2.0f, 3.0f, 4.0f); // w en premier
    assertEqual(Quaternion::Dot(q1, q2), 40.0f, "DotProduct");
}

void testPower() {
    Quaternion q(0.0f, 0.0f, 1.0f, 0.0f); // w en premier
    Quaternion result = Quaternion::Power(q, 2.0f);
    assertEqual(result.w, -1.0f, "Power w");
    assertEqual(result.x, 0.0f, "Power x");
    assertEqual(result.y, 0.0f, "Power y");
    assertEqual(result.z, 0.0f, "Power z");
}

void testSlerp() {
    Quaternion q1(1.0f, 0.0f, 0.0f, 0.0f); // w en premier
    Quaternion q2(0.0f, 1.0f, 0.0f, 0.0f); // w en premier
    Quaternion slerpQ = Quaternion::Slerp(q1, q2, 0.5f);
    assertEqual(slerpQ.w, 0.707107f, "Slerp w");
    assertEqual(slerpQ.x, 0.707107f, "Slerp x");
    assertEqual(slerpQ.y, 0.0f, "Slerp y");
    assertEqual(slerpQ.z, 0.0f, "Slerp z");
}

void testAddition() {
    Quaternion q1(4.0f, 1.0f, 2.0f, 3.0f); // w en premier
    Quaternion q2(5.0f, 2.0f, 3.0f, 4.0f); // w en premier
    Quaternion result = q1 + q2;
    assertEqual(result.w, 9.0f, "Addition w");
    assertEqual(result.x, 3.0f, "Addition x");
    assertEqual(result.y, 5.0f, "Addition y");
    assertEqual(result.z, 7.0f, "Addition z");
}

void testMultiplication() {
    Quaternion q1(0.0f, 1.0f, 0.0f, 1.0f); // w en premier
    Quaternion q2(0.75f, 1.0f, 0.5f, 0.5f); // w en premier
    Quaternion result = q1 * q2;
    assertEqual(result.w, -1.5f, "Multiplication w");
    assertEqual(result.x, 0.25f, "Multiplication x");
    assertEqual(result.y, 0.5f, "Multiplication y");
    assertEqual(result.z, 1.25f, "Multiplication z");
}

void ofApp::runTestsQuaternion() {
    testDefaultConstructorQuaternion();
    testParameterizedConstructorQuaternion();
    testNeg();
    testMagnitude();
    testConjugate();
    testInverseQuaternion();
    testDot();
    testPower();
    testSlerp();
    testAddition();
    testMultiplication();
}
