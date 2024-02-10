#include "ofApp.h"
#include <vector>
#include "Renderer/Renderer.h"
#include "Components/Rigidbody.h"
#include "AIClasses/AISystem.h"
#include "AIClasses/KinematicSeek.h"
#include "AIClasses/DynamicSeek.h"
#include "AIClasses/DynamicArrive.h"
#include "AIClasses/DynamicArrive2.h"
#include "AIClasses/DynamicWander.h"

ofImage boid;
ofImage breadcrumb;

uint64_t prevTime = 0;
float dt = 0;

KinematicSeek* kSeek;

AISystem* AI;

std::vector<Rigidbody*> boids;

std::vector<Rigidbody*> breadcrumbs;
const int MAX_BREADCRUMBS = 30;
float breadcrumbTimer = 0;
float breadcrumbInterval = 1;

Vector2 clickTarget = Vector2::NULL_VECTOR;

int displayMode;

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
void setupKinematic()
{
	displayMode = 1;

	//Single boid setup
	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	//kinematic seek setup
	boids[0]->position = Vector2(80, 700);
	kSeek = new KinematicSeek(boids[0]);
}

void setupSeek()
{
	displayMode = 2;

	//Single boid setup
	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	//dynamic seek setup
	boids[0]->position = Vector2(80, 700);
	AIComponent* ai = new AIComponent(boids[0]);
	Vector2 target = clickTarget;
	if (target == Vector2::NULL_VECTOR)
	{
		target = Vector2(300, 300);
	}
	ai->behavior = new DynamicSeek(target, ai);

	std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();
	aiObjects.push_back(ai);

	if (AI)
	{
		AI->replaceAIObjects(aiObjects);
	}
	else 
	{
		AI = new AISystem(aiObjects);
	}
}

void setupArrive1()
{
	displayMode = 3;

	//Single boid setup
	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	//dynamic arrive setup
	boids[0]->position = Vector2(80, 700);
	AIComponent* ai = new AIComponent(boids[0]);
	Vector2 target = clickTarget;
	if (target == Vector2::NULL_VECTOR)
	{
		target = Vector2(300, 300);
	}
	ai->behavior = new DynamicArrive(ai, target);

	std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();
	aiObjects.push_back(ai);

	if (AI)
	{
		AI->replaceAIObjects(aiObjects);
	}
	else
	{
		AI = new AISystem(aiObjects);
	}
}

void setupArrive2()
{
	displayMode = 4;

	//Single boid setup
	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	//dynamic arrive setup
	boids[0]->position = Vector2(80, 700);
	AIComponent* ai = new AIComponent(boids[0]);
	Vector2 target = clickTarget;
	if (target == Vector2::NULL_VECTOR)
	{
		target = Vector2(300, 300);
	}
	ai->behavior = new DynamicArrive2(ai, target);

	std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();
	aiObjects.push_back(ai);

	if (AI)
	{
		AI->replaceAIObjects(aiObjects);
	}
	else
	{
		AI = new AISystem(aiObjects);
	}
}

void setupWander1()
{
	displayMode = 5;

	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	boids[0]->position = Vector2(500, 400);
	AIComponent* ai = new AIComponent(boids[0], 20, 100);
	ai->behavior = new DynamicWander(ai);

	std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();
	aiObjects.push_back(ai);

	if (AI)
	{
		AI->replaceAIObjects(aiObjects);
	}
	else
	{
		AI = new AISystem(aiObjects);
	}
}

void ofApp::setup(){
	boid.load("images/boid.png");
	breadcrumb.load("images/breadcrumb.png");
	std::cout << "Press keys 1-8 to select that part of the assignment\n";

	//Start tick
	QueryPerformanceCounter((LARGE_INTEGER*) &prevTime);

	//Get random seed
	srand(time(NULL));

	//Setup breadcrumbs
	breadcrumbs = std::vector<Rigidbody*>();

	setupWander1();

	//TODO find memory leaks?
}

//--------------------------------------------------------------
void ofApp::update(){
	getTick();

	switch (displayMode) {
	case 1:
		kSeek->updateRigidbody(dt);
		break;

	default:
		AI->update(dt);
		break;
	}

	breadcrumbTimer += dt;
	if (breadcrumbTimer > breadcrumbInterval) {
		breadcrumbTimer = 0;

		Rigidbody* newCrumb = new Rigidbody();
		newCrumb->position = boids[0]->position;
		newCrumb->orientation = boids[0]->orientation;
		breadcrumbs.push_back(newCrumb);

		//overwrite old breadcrumbs
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
	switch (key) {
	case '1':
		setupKinematic();
		break;
	case '2':
		setupSeek();
		break;
	case '3':
		setupArrive1();
		break;
	case '4':
		setupArrive2();
		break;
	case '5':
		setupWander1();
		//Wander1
		break;
	case '6':
		displayMode = 6;
		//Wander2
		break;
	case '7':
		displayMode = 7;
		//Wander3
		break;
	case '8':
		displayMode = 8;
		//Flocking
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
	//Setup clickTarget
	clickTarget = Vector2(x, y);
	if (AI) {
		switch (displayMode)
		{
		case 1:
			break;
		case 2:
			delete AI->getAIObjects()[0]->behavior; //Are these actually necessary? Some testing without them didn't seem to bring up any issues
			AI->getAIObjects()[0]->behavior = new DynamicSeek(clickTarget, AI->getAIObjects()[0]);
			break;
		case 3:
			delete AI->getAIObjects()[0]->behavior;
			AI->getAIObjects()[0]->behavior = new DynamicArrive(AI->getAIObjects()[0], clickTarget);
			break;
		}
	}
	
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