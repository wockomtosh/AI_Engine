#include "ofApp.h"
#include "AIClasses/KinematicSeek.h"
#include "Renderer/Renderer.h"
#include "Components/Rigidbody.h"

ofImage boid;
ofImage breadcrumb;

uint64_t prevTime = 0;
float dt = 0;

KinematicSeek* kSeek;

std::vector<Rigidbody*> boids;

std::vector<Rigidbody*> breadcrumbs;
const int MAX_BREADCRUMBS = 30;
float breadcrumbTimer = 0;
float breadcrumbInterval = 1;

int displayMode = 1;

//--------------------------------------------------------------
void getTick()
{
	uint64_t countsPerSecond = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);

	uint64_t curTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	
	//Divide the number of counts that have passed by counts per second to get seconds
	dt = (curTime - prevTime) / (float)countsPerSecond;

	prevTime = curTime;
}

//--------------------------------------------------------------
void ofApp::setup(){
	boid.load("images/boid.png");
	breadcrumb.load("images/breadcrumb.png");
	std::cout << "Press keys 1-7 to select that part of the assignment\n";

	//Start tick
	QueryPerformanceCounter((LARGE_INTEGER*) &prevTime);

	//Setup breadcrumbs
	breadcrumbs = vector<Rigidbody*>();

	//Single boid setup
	boids = vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	//kinematic seek setup
	boids[0]->position = Vector2(80, 700);
	kSeek = new KinematicSeek(boids[0]);


	//Testing how to change the color of a boid for later. 
	//Right now this iterates over every pixel so that it can ignore the transparent pixels.
	/*for (int i = 0; i < boid.getWidth(); i++)
	{
		for (int j = 0; j < boid.getHeight(); j++) 
		{
			if (boid.getPixels().getColor(i, j) == ofColor(0, 0, 0)) 
			{
				boid.setColor(i, j, ofColor(255, 255, 255));
			}
		}
	}
	boid.update();*/
}

//--------------------------------------------------------------
void ofApp::update(){
	//I want an AI::update() to get called. Should that be a static class with an update? Should the AI system be a class on its own that I set up?
	//Should I have multiple AI classes that inherit from a base class to change behaviors? How do I set up these AI systems?
	//I also need a renderer. I need to have a list of gameObjects somewhere so that I can render them after they've been modified by the AI system.
	//Should each gameObject have a generic AI component? Or should that be split into multiple components?
	
	getTick();

	switch (displayMode) {
	case 1:
		kSeek->updateRigidbody(dt);
		break;

	case 2:
		boids[0]->update(dt, {Vector2(10,10), 10});
		break;

	default:
		boids[0]->update(dt, { Vector2(-10,0), -10 });
		break;
	}

	breadcrumbTimer += dt;
	if (breadcrumbTimer > breadcrumbInterval) {
		breadcrumbTimer = 0;

		Rigidbody* newCrumb = new Rigidbody();
		newCrumb->position = boids[0]->position;
		newCrumb->orientation = boids[0]->orientation;
		breadcrumbs.push_back(newCrumb);

		//overwrite old breadcrumbs?
		if (breadcrumbs.size() >= MAX_BREADCRUMBS) {
			breadcrumbs.erase(breadcrumbs.begin());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor(180, 180, 180));

	for (int i = 0; i < breadcrumbs.size(); i++) {
		Renderer::draw(breadcrumb, breadcrumbs[i]);
	}

	for (int i = 0; i < boids.size(); i++) {
		Renderer::draw(boid, boids[i]);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//TODO Implement 1-7 key presses for the different behaviors that I'll want to run.
	//TODO Implement setup calls here to reset the boid(s)
	switch (key) {
	case '1':
		displayMode = 1;
		break;
	case '2':
		displayMode = 2;
		break;
	case '3':
		displayMode = 3;
		break;
	}
		

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
