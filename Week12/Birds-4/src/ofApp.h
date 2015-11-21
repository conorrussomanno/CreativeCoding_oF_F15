#pragma once

#include "ofMain.h"
#include "Bird.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        ofPoint accTowardsCenterOfMass(int birdNumber);
        ofPoint accAwayFromNearbyBirds(int birdNumber);
        ofPoint accInDirectionOfNearbyBirdMovement(int birdNumber);
        ofPoint accTowardsCursor(int birdNumber);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector <Bird> myBirds;
        int numBirds;
        int framesBetweenRecordedPosition;
        int frameCounter;
        bool isMousePressed;
    
    
    float aFactor; // aF - a multiplier for scaling the "temp acceleration" (A)
    ofPoint A;  // A
    ofPoint A1; // A1 - the bird wanting to move towards the middle of all other birds
    ofPoint A2; // A2 - the bird wanting to move away from fellow birds that are too close
    ofPoint A3; // A3 - the bird wanting to move the same speed as nearby friends
    ofPoint A4;
    
    float herdDependency; // lW - find this bird's desire to explore alone
    float proximityDiscomfort; // pD - find this bird's apathy to being in close quarters with other birds
    float flowConsideration; // fC - find this bird's consideration for other birds' desire to get home from work
    float cursorCuriosity;
    
    ofPoint myValue;
    ofPoint megaPosition;
    
    ofPoint runAway; //value that will be turned to
    int numBirdsInfluencing;
    
    ofPoint avgVelOfNearbyBirds;;
    ofPoint myMousePosition;
    
    float amplifier;
		
};
