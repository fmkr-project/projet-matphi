#include "ofApp.h"
#include "particule.h"
#include "vector3d.h"

float timeSinceLastSecond = float(0.0);
//--------------------------------------------------------------
void ofApp::setup() {
	box.set(500);
	ofSetBackgroundAuto(false);
	ofBackground(0);
	Particule p(Vector3d(500, 500), Vector3d(1, 1), 20, ofColor());
}

//--------------------------------------------------------------
void ofApp::update() {
	timeSinceLastSecond += ofGetLastFrameTime();

	for (auto& particle : myParticles) {

		particle.move();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	bool isSecond = false;
	if (timeSinceLastSecond >= float(1.0)) {
		timeSinceLastSecond -= float(1.0);
		isSecond = true;
	}
	for (auto& particle : myParticles) {
		ofSetColor(particle.getColor());
		if (isSecond) {
			ofDrawIcoSphere(particle.getPosition().v3(), 10);
		}
		particle.draw();
	}
	float frameTime = ofGetLastFrameTime();
	ofSetColor(255);
	ofDrawBitmapString("Press c to shoot cannonballs", 10, 10);
	ofDrawBitmapString("Press p to shoot pistols bullets", 10, 25);
	ofDrawBitmapString("Press a to shoot arrows", 10, 40);
	ofDrawBitmapString("Press l to shoot lasers", 10, 55);
	ofDrawBitmapString("Press b to shoot basket balls", 10, 70);
	ofSetColor(0);
	ofDrawRectangle(800, 0, 200, 20);
	ofSetColor(255);
	ofDrawBitmapString("Frame Time : " + ofToString(frameTime), 800, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	ofBackground(0);
	myParticles.clear();
	switch (key) {
	case 'c':

		SpawnParticle(1000, 50, ofColor(125));
		break;
	case 'p':

		SpawnParticle(1000, 5, ofColor(255));
		break;
	case 'a':

		SpawnParticle(500, 20, ofColor(125, 42, 42));
		break;
	case 'l':

		SpawnParticle(10000, 1, ofColor(255, 0, 0));
		break;
	case 'b':

		SpawnParticle(200, 10, ofColor(255, 155, 0));
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

void ofApp::SpawnParticle(float speed, float mass, ofColor col) {
	float r = ofRandom(0.1, 0.8);
	Particule newParticle(
		Vector3d(20, 600),
		speed * Vector3d(r, r - 1),
		mass,
		col
	);
	myParticles.push_back(newParticle);
}
