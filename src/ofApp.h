#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ParticleFriction.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"
#include "RigidBodyBox.h"
#include "CollisionManager.h"
#include "CollisionBoxPlane.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void SpawnParticle(float speed, float mass, ofColor col);
	void DrawSpring(Particle p); //

public:

	const Vector3* startPoint;
	const float impulseStrength = 5000.f;
	vector<Particle*> myParticles;
	CollisionManager collisionManager = CollisionManager();
	ofBoxPrimitive box;
	int numberParticles;
	Vector3 centerStart;
	Particle* centerBox;
	RigidBodyBox rigidBox;
	bool isMoving;

	bool showOctree = false;

};
