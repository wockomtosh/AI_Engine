#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1200, 768);
	// PBR Materials only work with programmable renderer
	settings.setGLVersion(3,2);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	
	auto window = ofCreateWindow(settings);
<<<<<<< HEAD
<<<<<<< HEAD:examples/gl/materialPBR/src/main.cpp
	
=======

<<<<<<<< HEAD:examples/gl/materialPBR/src/main.cpp
>>>>>>> 8d5c89e (Adding scripts file):scripts/templates/emscripten/src/main.cpp
========
>>>>>>>> 0a548c4f (Updating gitignore for the problem files, starting on decision trees and things, initial setup):scripts/qtcreator/templates/wizards/openFrameworks/src/main.cpp
=======
	
>>>>>>> 0a548c4f (Updating gitignore for the problem files, starting on decision trees and things, initial setup)
	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
