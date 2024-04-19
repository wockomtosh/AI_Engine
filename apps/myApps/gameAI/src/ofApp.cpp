#include "ofApp.h"
#include <vector>
#include "Renderer/Renderer.h"
#include "Components/Rigidbody.h"
#include "Components/AxisAlignedBoundingBox.h"
#include "AIClasses/AISystem.h"
#include "AIClasses/DynamicArrive.h"
#include "AIClasses/DynamicEmpty.h"
#include "AIClasses/DynamicPathfollow.h"
#include "AIClasses/Pathfinding/Pathfinder.h"
#include "AIClasses/Pathfinding/Graph/DirectedGraph.h"
#include "AIClasses/Pathfinding/Graph/TileGraph.h"
#include "AIClasses/Pathfinding/SmallerGraphHeuristic.h"
#include "AIClasses/Pathfinding/HandmadeHeuristic.h"
#include "AIClasses/Pathfinding/ManhattanHeuristic.h"
#include "AIClasses/Pathfinding/ChebyshevHeuristic.h"
#include "AIClasses/Action.h"
#include "AIClasses/ActionManager.h"
#include "AIClasses/DecisionTree.h"
#include "AIClasses/DecisionNode.h"
#include "AIClasses/ActionNode.h"
#include "AIClasses/Blackboard.h"
#include "AIClasses/IsMovingDecision.h"
#include "AIClasses/TooCloseDecision.h"
#include "AIClasses/WanderTimeDecision.h"
#include "AIClasses/WanderAction.h"
#include "AIClasses/SpinAction.h"
#include "AIClasses/EatAction.h"
#include "AIClasses/StayStillAction.h"
#include "AIClasses/PathfindHomeAction.h"
#include "AIClasses/EvadeNearestAction.h"
#include "AIClasses/ChaseTargetAction.h"
#include "AIClasses/VelocityMatchAction.h"
#include "AIClasses/BehaviorTree.h"
#include "AIClasses/SelectorTask.h"
#include "AIClasses/NDSelectorTask.h"
#include "AIClasses/SequenceTask.h"
#include "AIClasses/ConditionTask.h"
#include "AIClasses/ActionTask.h"
#include "AIClasses/UntilFailDecorator.h"
#include "AIClasses/RepeatNDecorator.h"
#include "AIClasses/CloseToTargetCondition.h"
#include "AIClasses/CloseToWallsCondition.h"
#include "AIClasses/PlayerIsAliveCondition.h"

ofImage boid;
ofImage breadcrumb;
ofImage obstacle;

uint64_t performanceStartTime = 0;
uint64_t prevTime = 0;
float dt = 0.016;

AISystem* AI;

TileGraph* tileGraph;
std::vector<AABB*> obstacles;

std::vector<Rigidbody*> boids;

#define MAX_BREADCRUMBS 50
std::vector<Rigidbody*> breadcrumbs;
float breadcrumbTimer = 0;
float breadcrumbInterval = 1;

Vector2 clickTarget = Vector2::NULL_VECTOR;

Blackboard* blackboard;
DecisionTree* decisionTree;
ActionManager* dtManager;
BehaviorTree* behaviorTree;
ActionManager* btManager;
float maxWanderTime = 7;

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
	tileGraph = new TileGraph(16, WINDOW_WIDTH, WINDOW_HEIGHT, obstacles);
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

	//startPerformanceCheck();
	std::vector<DirectedWeightedEdge> path = Pathfinder::findPath(startNode, endNode, tileGraph, new ManhattanHeuristic(endNode, tileGraph));
	//std::vector<DirectedWeightedEdge> path = Pathfinder::findPath(startNode, endNode, tileGraph, new ChebyshevHeuristic(endNode, tileGraph));
	//std::cout << "Manhattan: " << getPerformanceCheckResult() << std::endl;

	delete ai->behavior;
	ai->behavior = new DynamicPathfollow(ai, tileGraph, path, 64, 32);
}

void setupBlackboard()
{
	if (!blackboard)
	{
		blackboard = new Blackboard();
	}	
}

void setupDecisionTree()
{
	displayMode = 1;

	//Single boid setup
	boids = std::vector<Rigidbody*>();
	boids.push_back(new Rigidbody());
	boids[0]->position = Vector2(80, 700);
	AIComponent* ai = new AIComponent(boids[0]);
	ai->behavior = new DynamicEmpty();

	if (AI)
	{
		AI->addAIObject(ai);
	}
	else
	{
		std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();
		aiObjects.push_back(ai);
		AI = new AISystem(aiObjects);
	}

	//Add our blackboard variables
	blackboard->setGeneric("obstacles", &obstacles);
	blackboard->setFloat("wanderTime", 0);

	//Create DecisionTree
	ActionNode* pathfindHome = new ActionNode(std::make_shared<PathfindHomeAction>(ai, tileGraph));
	ActionNode* emptyAction = new ActionNode(std::make_shared<Action>());
	ActionNode* evadeNearest = new ActionNode(std::make_shared<EvadeNearestAction>(blackboard, ai));
	ActionNode* wander = new ActionNode(std::make_shared<WanderAction>(ai));

	DecisionNode* wanderTime = new DecisionNode(pathfindHome, emptyAction, new WanderTimeDecision(blackboard, maxWanderTime));
	DecisionNode* tooClose = new DecisionNode(evadeNearest, wanderTime, new TooCloseDecision(blackboard, boids[0]));
	DecisionNode* isStationary = new DecisionNode(tooClose, wander, new IsMovingDecision(boids[0]));
	decisionTree = new DecisionTree(isStationary);

	dtManager = new ActionManager();
}

void setupBehaviorTree()
{
	boids.push_back(new Rigidbody());
	boids[1]->position = Vector2(700, 80);
	AIComponent* ai = new AIComponent(boids[1]);
	ai->behavior = new DynamicEmpty();

	if (AI)
	{
		AI->addAIObject(ai);
	}
	else
	{
		std::vector<AIComponent*> aiObjects = std::vector<AIComponent*>();
		aiObjects.push_back(ai);
		AI = new AISystem(aiObjects);
	}

	//Add our blackboard variables
	blackboard->setGeneric("character", boids[0]);
	blackboard->setGeneric("monster", boids[1]);
	blackboard->setGeneric("obstacles", &obstacles); //Double setting this because I won't always be using the decision tree
	blackboard->setBool("playerIsAlive", true);
	blackboard->setBool("victoryComplete", false);

	//Create BehaviorTree
	
	//WALL EVASION
	ConditionTask* tooCloseToWalls = new ConditionTask(5, new CloseToWallsCondition());
	ActionTask* evadeWalls = new ActionTask(6, std::make_shared<EvadeNearestAction>(blackboard, ai));
	SequenceTask* handleWalls = new SequenceTask(1, { tooCloseToWalls, evadeWalls });

	//CHASING/EATING
	ConditionTask* playerIsAlive = new ConditionTask(7, new PlayerIsAliveCondition());
	ConditionTask* canChasePlayer = new ConditionTask(8, new CloseToTargetCondition());

	ConditionTask* canEatPlayer = new ConditionTask(16, new CloseToTargetCondition(30));
	ActionTask* eatPlayer = new ActionTask(17, std::make_shared<EatAction>(blackboard, boids[0]));
	SequenceTask* tryEatPlayer = new SequenceTask(12, { canEatPlayer, eatPlayer });

	ActionTask* chasePlayer = new ActionTask(13, std::make_shared<ChaseTargetAction>(blackboard, ai, boids[0]));
	SelectorTask* eatOrChase = new SelectorTask(9, { tryEatPlayer, chasePlayer });

	SequenceTask* handleChase = new SequenceTask(2, { playerIsAlive, canChasePlayer, eatOrChase });

	//IDLE/SEARCHING
	ActionTask* velocityMatch = new ActionTask(14, std::make_shared<VelocityMatchAction>(ai, boids[0]));
	ActionTask* stayStill = new ActionTask(15, std::make_shared<StayStillAction>(ai));
	NDSelectorTask* randomIdle = new NDSelectorTask(10, { velocityMatch, stayStill });
	SequenceTask* handleIdle = new SequenceTask(3, { playerIsAlive, randomIdle });

	//VICTORY
	ActionTask* victorySpin = new ActionTask(11, std::make_shared<SpinAction>(ai));
	RepeatNDecorator* handleVictory = new RepeatNDecorator(4, victorySpin);

	SelectorTask* root = new SelectorTask(0, { handleWalls, handleChase, handleIdle, handleVictory });

	behaviorTree = new BehaviorTree(root, blackboard);

	btManager = new ActionManager();
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

	//Setup world
	setupObstacles();
	createTileGraph();

	//Setup AI
	setupBlackboard();
	setupDecisionTree();
	setupBehaviorTree();
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

void updateDecisionTreeAIController(float dt)
{
	//Update our wander time here
	float wanderTime = blackboard->getFloat("wanderTime");
	if (wanderTime > maxWanderTime * 2)
	{
		wanderTime = 0;
	}
	else
	{
		wanderTime += dt;
	}
	blackboard->setFloat("wanderTime", wanderTime);

	//The decision tree is intended to run once per tick. I also designed the actions in it to run quickly, to try to keep things consistent
	//I also decided to let my AI system handle the movement still, so movement actions just set the behavior on that object
	std::shared_ptr<Action> newAction = decisionTree->makeDecision();
	dtManager->scheduleAction(newAction);
	dtManager->update(dt);
}

void updateBTAIController(float dt)
{
	std::shared_ptr<Action> newAction = behaviorTree->makeDecision();
	if (newAction)
	{
		btManager->scheduleAction(newAction);
	}
	btManager->update(dt);

	if (blackboard->getBool("victoryComplete"))
	{
		AI->replaceAIObjects(std::vector<AIComponent*>());
		setupDecisionTree();
		setupBehaviorTree();
	}
}

void ofApp::update(){
	getTick();

	updateDecisionTreeAIController(dt);
	updateBTAIController(dt);
	AI->update(dt);
	updateBreadcrumbs();
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
		setupDecisionTree();
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