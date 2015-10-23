#pragma once

#include "ofMain.h"
#include "Planet.h"
#include <vector>

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		//for audio in
		void audioIn(float * input, int bufferSize, int nChannels);
	
		vector<Planet> planets;
		int mode;
		int clickMode;
		ofImage imageOrbit; //
		ofImage imageAdd; //
		ofImage imageEdit; //
		ofImage imageEditClicked;
		ofImage imageDelete; //
		ofImage openHand; //
		ofImage closedHand; //
		ofImage goButton;
		ofImage cancelButton;
		ofImage densitySlider;
		ofImage colorSlider;
		ofImage sliderBars;
		ofImage imageSelectPlanet;
		ofImage imageDeleteClicked;
		ofImage positionCursor;
	
		#define	gConstant .0000001
		#define	maxPlanets 50
		#define vFactor 20.0
		#define rFactor 1.0
		
		float forceMain[maxPlanets][maxPlanets];
		float forceX[maxPlanets][maxPlanets];
		float forceY[maxPlanets][maxPlanets];
	
		//AUDIO Variables
	
		int audioIndicator;
	
		vector <float> left;
		vector <float> right;
		vector <float> volHistory;
		
		int 	bufferCounter;
		int 	drawCounter;
		
		float smoothedVol;
		float scaledVol;
		
		ofSoundStream soundStream;
	
	
		
};
