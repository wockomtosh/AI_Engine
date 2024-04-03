#include "ofApp.h"
#include <vector>
#include "Renderer/Renderer.h"
#include "Components/Rigidbody.h"
#include "Components/AxisAlignedBoundingBox.h"
#include "AIClasses/AISystem.h"
#include "AIClasses/DynamicArrive.h"
#include "AIClasses/DynamicPathfollow.h"
#include "AIClasses/Pathfinding/Pathfinder.h"
#include "AIClasses/Pathfinding/Graph/DirectedGraph.h"
#include "AIClasses/Pathfinding/Graph/TileGraph.h"
#include "AIClasses/Pathfinding/SmallerGraphHeuristic.h"
#include "AIClasses/Pathfinding/HandmadeHeuristic.h"
#include "AIClasses/Pathfinding/ManhattanHeuristic.h"
#include "AIClasses/Pathfinding/ChebyshevHeuristic.h"



ofImage boid;
ofImage breadcrumb;
ofImage obstacle;

uint64_t performanceStartTime = 0;
uint64_t prevTime = 0;
float dt = 0;

AISystem* AI;

TileGraph* tileGraph;
std::vector<AABB*> obstacles;

std::vector<Rigidbody*> boids;

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

void startPerformanceCheck()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&performanceStartTime);
}

//Similar to getTick() but it can be used alongside getTick and dt if you want to measure performance
float getPerformanceCheckResult()
{
	uint64_t countsPerSecond = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);

	uint64_t curTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

	return (curTime - performanceStartTime) / (float)countsPerSecond;
}

//--------------------------------------------------------------

void setupObstacles()
{
	obstacles = std::vector<AABB*>();

	//For now it'll be easier to just have all obstacles be the same size
	//My obstacle sprite is 128x128 so the extents should be (64,64), but my boid only takes into account its center, so I extend this a bit further to account for that.
	//Boid is 55 wide so we add ~55 to the extents
	Vector2 obstExtents = Vector2(112, 112);

	//Row up top
	obstacles.push_back(new AABB(Vector2(150, 150), obstExtents));
	obstacles.push_back(new AABB(Vector2(250, 150), obstExtents));
	obstacles.push_back(new AABB(Vector2(350, 150), obstExtents));
	obstacles.push_back(new AABB(Vector2(450, 150), obstExtents));

	//Column in the center area
	obstacles.push_back(new AABB(Vector2(500, 600), obstExtents));
	obstacles.push_back(new AABB(Vector2(500, 500), obstExtents));
	obstacles.push_back(new AABB(Vector2(500, 400), obstExtents));
	obstacles.push_back(new AABB(Vector2(500, 300), obstExtents));
	obstacles.push_back(new AABB(Vector2(500, 200), obstExtents));

	//Column 2
	//obstacles.push_back(new AABB(Vector2(800, 600), obstExtents));
	//obstacles.push_back(new AABB(Vector2(800, 500), obstExtents));
	//obstacles.push_back(new AABB(Vector2(800, 400), obstExtents));
	//obstacles.push_back(new AABB(Vector2(800, 300), obstExtents));
	//obstacles.push_back(new AABB(Vector2(800, 200), obstExtents));
}

void createTileGraph()
{
	tileGraph = new TileGraph(4, WINDOW_WIDTH, WINDOW_HEIGHT, obstacles);
}

void getNewClickTargetPath()
{
	AIComponent* ai = AI->getAIObjects()[0];

	int startNode = tileGraph->getNodeFromWorldCoordinate(ai->body->position.x, ai->body->position.y);
	int endNode = tileGraph->getNodeFromWorldCoordinate(clickTarget.x, clickTarget.y);

	//Don't accept invalid clicks!
	if (!tileGraph->checkIsNodeValid(endNode))
	{
		return;
	}

	std::vector<DirectedWeightedEdge> path = Pathfinder::findPath(startNode, endNode, tileGraph, new ManhattanHeuristic(endNode, tileGraph));
	//std::vector<DirectedWeightedEdge> path = Pathfinder::findPath(startNode, endNode, tileGraph, new ChebyshevHeuristic(endNode, tileGraph));

	ai->behavior = new DynamicPathfollow(ai, tileGraph, path, 64, 32);
}

void setupPathfollow()
{
	displayMode = 1;

	//Single boid setup
	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());

	boids[0]->position = Vector2(80, 700);
	AIComponent* ai = new AIComponent(boids[0]);

	//TODO: Create an empty steering behavior or handle the null check in AIComponent
	ai->behavior = new DynamicArrive(ai, ai->body->position);
	
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

	if (clickTarget != Vector2::NULL_VECTOR)
	{
		getNewClickTargetPath();
	}
}

void ofApp::setup(){
	boid.load("images/boid.png");
	breadcrumb.load("images/breadcrumb.png");
	obstacle.load("images/obstacle.png");
	//std::cout << "Press keys 1-8 to select that part of the assignment\n";

	//Start tick
	QueryPerformanceCounter((LARGE_INTEGER*) &prevTime);

	//Get random seed
	srand(time(NULL));

	//Setup breadcrumbs
	breadcrumbs = std::vector<Rigidbody*>();

	setupObstacles();
	createTileGraph();

	setupPathfollow();
}

//--------------------------------------------------------------
void updateBreadcrumbs()
{
	breadcrumbTimer += dt;
	if (breadcrumbTimer > breadcrumbInterval) {
		breadcrumbTimer = 0;

		//TODO: Make new crumbs for the monster
		Rigidbody* newCrumb = new Rigidbody();
		newCrumb->position = boids[0]->position;
		newCrumb->orientation = boids[0]->orientation;
		breadcrumbs.push_back(newCrumb);

		if (boids.size() > 1)
		{
			Rigidbody* newCrumb = new Rigidbody();
			newCrumb->position = boids[1]->position;
			newCrumb->orientation = boids[1]->orientation;
			breadcrumbs.push_back(newCrumb);
		}

		//overwrite old breadcrumbs
		if (breadcrumbs.size() >= MAX_BREADCRUMBS) {
			breadcrumbs.erase(breadcrumbs.begin());
		}
	}
}

void ofApp::update(){
	getTick();

	switch (displayMode) {
	default:
		AI->update(dt);
		updateBreadcrumbs();
		break;
	}	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor(180, 180, 180));

	//TODO: Set up render components and have the renderer just iterate through those on its own.
	for (int i = 0; i < breadcrumbs.size(); i++) {
		Renderer::draw(breadcrumb, breadcrumbs[i]);
	}

	for (int i = 0; i < boids.size(); i++) {
		Renderer::draw(boid, boids[i]);
	}

	for (int i = 0; i < obstacles.size(); i++) {
		Renderer::drawAABB(obstacle, obstacles[i]);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		setupPathfollow();
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
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
			getNewClickTargetPath();
			break;
		case 2:
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