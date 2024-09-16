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
	ofDrawBitmapString("Press p to shoot particules", 10, 10);
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
	case 'p':

		SpawnParticle(ofColor(ofRandom(256), ofRandom(256), ofRandom(256)));
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

void ofApp::SpawnParticle(ofColor col) {
	Particule newParticle(
		Vector3d(500, 500),
		Vector3d(ofRandom(-2, 2), ofRandom(-2, 2)),
		20,
		col
	);
	myParticles.push_back(newParticle);
}
