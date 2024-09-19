#include "ofApp.h"
#include "Particle.h"
#include "Vector3.h"

#include <of3dGraphics.h>

//--------------------------------------------------------------
void ofApp::setup() {
	box.set(500);
	Particle p(Vector3(500, 500), Vector3(20, 20), 1.);
    testVector3();
}

//--------------------------------------------------------------
void ofApp::update() {
	for (auto& particle : myParticles) {
		particle.move();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto& particle : myParticles) {
		particle.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key) {
	case 'p':
		SpawnParticle();
		break;

	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

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

void ofApp::SpawnParticle() {
	Particle newParticle(
		Vector3(500, 500),
		ofRandom(10., 100.) * Vector3(ofRandom(-1., 1.), ofRandom(-1., 0.), ofRandom(-1., 1.)),
		ofRandom(1., 10.)
	);

	myParticles.push_back(newParticle);
}

bool floatEquals(float a, float b, float tolerance = 0.0001f)
{
    return std::fabs(a - b) < tolerance;
}

void ofApp::testVector3()
{
    // Test des constructeurs
    Vector3 v1(1.0f, 2.0f, 3.0f);
    assert(floatEquals(v1.getX(), 1.0f));
    assert(floatEquals(v1.getY(), 2.0f));
    assert(floatEquals(v1.getZ(), 3.0f));
    assert(floatEquals(v1.getW(), 1.0f)); // par d faut, w = 1.0

    Vector3 v2(v1); // Test du constructeur de copie
    assert(v2 == v1); // Test de l' galit  entre deux vecteurs

    // Test des setters
    v1.setX(5.0f);
    v1.setY(6.0f);
    v1.setZ(7.0f);
    assert(floatEquals(v1.getX(), 5.0f));
    assert(floatEquals(v1.getY(), 6.0f));
    assert(floatEquals(v1.getZ(), 7.0f));

    // Test des op rateurs += et -=
    Vector3 v3(1.0f, 1.0f, 1.0f);
    v1 += v3;
    assert(floatEquals(v1.getX(), 6.0f));
    assert(floatEquals(v1.getY(), 7.0f));
    assert(floatEquals(v1.getZ(), 8.0f));

    v1 -= v3;
    assert(floatEquals(v1.getX(), 5.0f));
    assert(floatEquals(v1.getY(), 6.0f));
    assert(floatEquals(v1.getZ(), 7.0f));

    // Test des op rateurs *= et /=
    float scalar = 2.0f;
    v1 *= scalar;
    assert(floatEquals(v1.getX(), 10.0f));
    assert(floatEquals(v1.getY(), 12.0f));
    assert(floatEquals(v1.getZ(), 14.0f));

    v1 /= scalar;
    assert(floatEquals(v1.getX(), 5.0f));
    assert(floatEquals(v1.getY(), 6.0f));
    assert(floatEquals(v1.getZ(), 7.0f));

    // Test du produit scalaire
    Vector3 v4(1.0f, 1.0f, 1.0f);
    float dotProduct = v1.dotProduct(v4);
    assert(floatEquals(dotProduct, 5.0f + 6.0f + 7.0f)); // 5 + 6 + 7 = 18

    // Test du produit vectoriel
    Vector3 crossProduct = v1.crossProduct(v4);
    assert(floatEquals(crossProduct.getX(), -1.0f));
    assert(floatEquals(crossProduct.getY(), 2.0f));
    assert(floatEquals(crossProduct.getZ(), -1.0f));

    // Test de normalisation
    Vector3 v5(3.0f, 4.0f, 0.0f);
    v5.normalise();
    assert(floatEquals(v5.getX(), 0.6f));
    assert(floatEquals(v5.getY(), 0.8f));
    assert(floatEquals(v5.getZ(), 0.0f));

    // Test des comparaisons == et !=
    Vector3 v6(0.6f, 0.8f, 0.0f);
    assert(v5 == v6); // Ils doivent  tre  gaux apr s normalisation

    v6.setX(0.61f);
    assert(v5 != v6); // v6 a  t  l g rement modifi , donc ils ne doivent plus  tre  gaux

    // Afficher le r sultat final
    std::cout << "Tous les tests ont r ussi.\n";
}