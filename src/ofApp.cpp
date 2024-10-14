#include "ofApp.h"
#include "Particle.h"
#include "Vector3.h"
#include "World.h"
#include "ForceFriction.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"

#include <of3dGraphics.h>


float timeSinceLastSecond = float(0.);

float mouseXPos = 0;
float mouseYPos = 0;

//--------------------------------------------------------------
void ofApp::setup()
{
	box.set(500);
    ofBackground(0);
    init = Particle(Vector3(),Vector3(), 1, 200.);

    collision_manager = *new CollisionManager();
    collision_manager.add_particle(init);
    force_friction = new ForceFriction(0.1f, 0.1f);
    force_gravity = new ParticleGravity();
    force_spring = new ParticleSpring(1.);
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (auto& particle : myParticles)
    {
		particle.move();
	}

    // Manage resulting collisions
    collision_manager.detect_collisions();
    myParticles = collision_manager.get_particles();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    init.setPosition(Vector3(mouseXPos, mouseYPos, 0.));
    ofSetColor(init.getColor());
    init.draw();
    for (auto& particle : myParticles) {
        ofSetColor(particle.getColor());
        particle.draw();
        DrawSpring(particle);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    ofColor randomColor = ofColor(ofRandom(127, 256), ofRandom(127, 256), ofRandom(127, 256));
    if (key == 'e') {
        SpawnParticle(1, 10, randomColor);
    }
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
    Vector3 speedVector = Vector3(ofRandom(0.1, 0.8), ofRandom(-1., 0.), ofRandom(-0.25, 0.25));
    speedVector.normalise();
    Particle newParticle(
        Vector3(mouseXPos, mouseYPos - 100),
        speed * speedVector,
        mass,
        10.,
        col
    );
    myParticles.push_back(newParticle);
    collision_manager.add_particle(newParticle);
    World::addParticle(newParticle);

    std::cout << "New particle created" << std::endl;
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