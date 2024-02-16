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
#include "AIClasses/DynamicWander2.h"
#include "AIClasses/DynamicWander3.h"
#include "AIClasses/DynamicFlocking.h"

ofImage boid;
ofImage breadcrumb;
ofImage leaderBoid;

uint64_t prevTime = 0;
float dt = 0;

KinematicSeek* kSeek;

AISystem* AI;

std::vector<Rigidbody*> boids;
Rigidbody* flockLeader;

#define MAX_BREADCRUMBS 50
std::vector<Rigidbody*> breadcrumbs;
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

	//dynamic arriveWeight setup
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

	//dynamic arriveWeight setup
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

void setupWander2()
{
	displayMode = 6;

	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	boids[0]->position = Vector2(500, 400);
	AIComponent* ai = new AIComponent(boids[0], 20, 100);
	ai->behavior = new DynamicWander2(ai);

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

void setupWander3()
{
	displayMode = 7;

	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	boids[0]->position = Vector2(500, 400);
	AIComponent* ai = new AIComponent(boids[0], 20, 100);
	ai->behavior = new DynamicWander3(ai);

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

void setupFlocking()
{
	displayMode = 8;

	boids = std::vector<Rigidbody*>();
	std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();

	//Setup leader
	flockLeader = new Rigidbody();
	flockLeader->position = Vector2(500, 400);
	AIComponent* leaderAI = new AIComponent(flockLeader, 20, 100);
	leaderAI->behavior = new DynamicWander(leaderAI);
	leaderAI->tag = FLOCK_LEADER;
	aiObjects.push_back(leaderAI);

	//Setup flock (flockSize doesn't include leader)
	int flockSize = 15;
	for (int i = 0; i < flockSize; i++)
	{
		Rigidbody* newBoid = new Rigidbody();
		boids.push_back(newBoid);
		newBoid->position = Vector2(100 * i, 100 * i);

		//Don't setup behavior yet since they'll all need to be given the flocking behavior, but that flocking behavior needs a reference to all of them.
		AIComponent* ai = new AIComponent(newBoid, 20, 300);
		aiObjects.push_back(ai);
	}

	//In a separate loop so we can pass in the whole aiObjects vector. We may be able to do this in the first loop but I'm not gonna risk it for now
	for (int i = 0; i < aiObjects.size(); i++)
	{
		//Give everything except the leader the flocking behavior
		if (aiObjects[i]->behavior == nullptr)
		{
			/*aiObjects[i]->behavior = new DynamicWander(aiObjects[i]);*/
			aiObjects[i]->behavior = new DynamicFlocking(aiObjects[i], aiObjects);
			//aiObjects[i]->behavior = new DynamicEvade(aiObjects[i], aiObjects[0]->body, 400);
		}
	}

	//leaderAI->behavior = new DynamicFlocking(leaderAI, aiObjects);

	if (AI)
	{
		AI->replaceAIObjects(aiObjects);
	}
	else
	{
		AI = new AISystem(aiObjects);
	}

	//Distinguish the leaderBoid
	//Right now this iterates over every pixel so that it can ignore the transparent pixels.
	for (int i = 0; i < leaderBoid.getWidth(); i++)
	{
		for (int j = 0; j < leaderBoid.getHeight(); j++)
		{
			if (leaderBoid.getPixels().getColor(i, j) == ofColor(0, 0, 0))
			{
				leaderBoid.setColor(i, j, ofColor(0, 255, 0));
			}
		}
	}
	leaderBoid.update();
}

void ofApp::setup(){
	boid.load("images/boid.png");
	breadcrumb.load("images/breadcrumb.png");
	leaderBoid.load("images/boid.png");
	std::cout << "Press keys 1-8 to select that part of the assignment\n";

	//Start tick
	QueryPerformanceCounter((LARGE_INTEGER*) &prevTime);

	//Get random seed
	srand(time(NULL));

	//Setup breadcrumbs
	breadcrumbs = std::vector<Rigidbody*>();

	setupFlocking();

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

		//Track the leader when flocking
		if (displayMode == 8)
		{
			newCrumb->position = flockLeader->position;
			newCrumb->orientation = flockLeader->orientation;
		}
		else
		{
			newCrumb->position = boids[0]->position;
			newCrumb->orientation = boids[0]->orientation;
		}
		
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

	//Render leader separately when flocking. Later if I do a renderComponent that holds a sprite this will be nicer
	if (displayMode == 8) {
		Renderer::draw(leaderBoid, flockLeader);
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
		break;
	case '6':
		setupWander2();
		break;
	case '7':
		setupWander3();
		break;
	case '8':
		setupFlocking();
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
		case 4:
			delete AI->getAIObjects()[0]->behavior;
			AI->getAIObjects()[0]->behavior = new DynamicArrive2(AI->getAIObjects()[0], clickTarget);
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