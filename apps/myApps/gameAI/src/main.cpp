#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(ofApp::WINDOW_WIDTH, ofApp::WINDOW_HEIGHT);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	settings.title = "Jake's AI";

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
