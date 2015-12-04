#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	window.setGlutDisplayString("rgba double samples>=4"); // smooth circle edges
	ofSetupOpenGL(&window, 900, 900, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new testApp());

}
