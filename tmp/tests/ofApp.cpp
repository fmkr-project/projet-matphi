#include "ofApp.h"
#include "particule.h"
#include "vector3d.h"

//--------------------------------------------------------------
void ofApp::setup() {
	box.set(500);
	Particule p(Vector3d(500, 500), Vector3d(1, 1), 20);
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
	Particule newParticle(
		Vector3d(500, 500),
		Vector3d(ofRandom(-2, 2), ofRandom(-2, 2)),
		10
	);

	myParticles.push_back(newParticle);
}




bool floatEquals(float a, float b, float tolerance = 0.0001f)
{
	return std::fabs(a - b) < tolerance;
}

void ofApp::testvector3d()
{
    // Test des constructeurs
    Vector3d v1(1.0f, 2.0f, 3.0f);
    assert(floatEquals(v1.getX(), 1.0f));
    assert(floatEquals(v1.getY(), 2.0f));
    assert(floatEquals(v1.getZ(), 3.0f));
    assert(floatEquals(v1.getW(), 1.0f)); // par défaut, w = 1.0

    Vector3d v2(v1); // Test du constructeur de copie
    assert(v2 == v1); // Test de l'égalité entre deux vecteurs

    // Test des setters
    v1.setX(5.0f);
    v1.setY(6.0f);
    v1.setZ(7.0f);
    assert(floatEquals(v1.getX(), 5.0f));
    assert(floatEquals(v1.getY(), 6.0f));
    assert(floatEquals(v1.getZ(), 7.0f));

    // Test des opérateurs += et -=
    Vector3d v3(1.0f, 1.0f, 1.0f);
    v1 += v3;
    assert(floatEquals(v1.getX(), 6.0f));
    assert(floatEquals(v1.getY(), 7.0f));
    assert(floatEquals(v1.getZ(), 8.0f));

    v1 -= v3;
    assert(floatEquals(v1.getX(), 5.0f));
    assert(floatEquals(v1.getY(), 6.0f));
    assert(floatEquals(v1.getZ(), 7.0f));

    // Test des opérateurs *= et /=
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
    Vector3d v4(1.0f, 1.0f, 1.0f);
    float dotProduct = v1.dotProduct(v4);
    assert(floatEquals(dotProduct, 5.0f + 6.0f + 7.0f)); // 5 + 6 + 7 = 18

    // Test du produit vectoriel
    Vector3d crossProduct = v1.crossProduct(v4);
    assert(floatEquals(crossProduct.getX(), -1.0f));
    assert(floatEquals(crossProduct.getY(), 2.0f));
    assert(floatEquals(crossProduct.getZ(), -1.0f));

    // Test de normalisation
    Vector3d v5(3.0f, 4.0f, 0.0f);
    v5.normalise();
    assert(floatEquals(v5.getX(), 0.6f));
    assert(floatEquals(v5.getY(), 0.8f));
    assert(floatEquals(v5.getZ(), 0.0f));

    // Test des comparaisons == et !=
    Vector3d v6(0.6f, 0.8f, 0.0f);
    assert(v5 == v6); // Ils doivent être égaux après normalisation

    v6.setX(0.61f);
    assert(v5 != v6); // v6 a été légèrement modifié, donc ils ne doivent plus être égaux

    // Afficher le résultat final
    std::cout << "Tous les tests ont réussi.\n";
}