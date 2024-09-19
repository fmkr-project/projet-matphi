#include "ofApp.h"
#include "Particle.h"
#include "Vector3.h"

#include <of3dGraphics.h>

//--------------------------------------------------------------
void ofApp::setup() {
	box.set(500);
	Particle p(Vector3(500, 500), Vector3(20, 20), 1.);
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
