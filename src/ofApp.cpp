#include "ofApp.h"
#include "Particle.h"
#include "Vector3.h"
#include "World.h"
#include "ParticleFriction.h"
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
    init = Particle(Vector3(),Vector3(), 1, 10.);
    numberParticles = 0;

    ground = Particle(Vector3(500,1600,0), Vector3(), 10000000, 1000., ofColor(160,160,160));

    force_registry = new ParticleForceRegistry();
    //ParticleGravity* tmp = new ParticleGravity(Vector3());
    //force_registry->add(&ground, tmp);
    collision_manager = *new CollisionManager();
    collision_manager.add_particle(&init);
    collision_manager.add_particle(&ground);
    force_friction = new ParticleFriction(0.1f, 0.1f);
    force_gravity = new ParticleGravity();
    force_spring = new ParticleSpring(500., 10., &init);
}

//--------------------------------------------------------------
void ofApp::update()
{
    //Update the forces in the registry
    force_registry->updateForces(ofGetLastFrameTime());
	for (auto particle : myParticles)
    {
		particle->move();
        particle->clearAccum();
	}

    // Manage resulting collisions
    collision_manager.detect_collisions();
    myParticles = collision_manager.get_particles();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Update init position in collision manager
    ground.draw();
    init.setPosition(Vector3(mouseXPos, mouseYPos, 0.));
    init.draw();
    for (auto& particle : myParticles) {
        if (particle->getMass() < 1000) { //Allow to exclude the ground
            particle->draw();
            DrawSpring(*particle);
        }
    }
    for (auto& particle : myFreeParticles) {
        particle->draw();
    }
    ofSetColor(init.getColor());
    ofDrawBitmapString("Numbers of particles :" + ofToString(numberParticles), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    ofColor randomColor = ofColor(ofRandom(127, 256), ofRandom(127, 256), ofRandom(127, 256));
    if (key == 'e' && numberParticles <20) {
        SpawnParticle(1, 100, randomColor);
    }
    if (key == 'b' && numberParticles > 0) {
        Particle* p = myParticles.back();
        myFreeParticles.push_back(p);
        myParticles.pop_back();
        collision_manager.remove_particle(p);

    }
    if (key == 'a' && numberParticles > 0 && myFreeParticles.size() > 0) {
        Particle* p = myFreeParticles.back();
        myParticles.push_back(p);
        myFreeParticles.pop_back();
        collision_manager.add_particle(p);
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
    auto newParticle = new Particle(
        Vector3(mouseXPos, mouseYPos - 100),
        *Vector3::zero,
        mass,
        10.,
        col
    );
    myParticles.push_back(newParticle);

    //Add forces to the new particule
    force_registry->add(newParticle, force_friction);
    force_registry->add(newParticle, force_gravity);
    force_registry->add(newParticle, force_spring);

    collision_manager.add_particle(newParticle);
    //World::addParticle(newParticle);

    std::cout << "New particle created @" << mouseXPos << ' ' << mouseYPos << '\n';
    collision_manager._debug_print_all_particles();
    numberParticles++;
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