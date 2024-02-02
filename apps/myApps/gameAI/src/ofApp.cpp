#include "ofApp.h"

ofImage boid;

//--------------------------------------------------------------
void ofApp::setup(){
	boid.load("images/boid.png");
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
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//The renderer is basically the draw function here.
	ofBackground(ofColor(180, 180, 180));
	boid.draw(100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//TODO Implement 1-7 key presses for the different behaviors that I'll want to run.
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
