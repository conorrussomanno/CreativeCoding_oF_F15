#pragma once

#include "ofMain.h"
#include "Thing.h" //have to include the Thing class in order to use it & instantiate it

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void bump();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //our vector of Things
        vector <Thing> myThings;
        //timeSinceLastImportantMomemt
        float timeOfLastImportantMomemt; //for our timer in ofApp.update();
        int xMargin, yMargin;
        int numColumns, numRows;
        bool haveIGrabbedAThing;
        int thingGrabbed;
		
};
