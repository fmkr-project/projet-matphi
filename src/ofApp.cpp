#include "ofApp.h"
#include "Particle.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"
//#include "World.h"
#include "ParticleFriction.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"
#include "RigidBodyBox.h"
#include "BoundingBox.h"
#include "Octree.h"

#include <of3dGraphics.h>


float timeSinceLastSpawn = float(3.);

float mouseXPos = 0;
float mouseYPos = 0;


//--------------------------------------------------------------
void ofApp::setup()
{
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

    BoundingBox box(Vector3(1024, 0, 0), Vector3(0, 1024, -1024));
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