#pragma once
#include "ofMain.h"
#include "testApp.h"
#include "Planet.h"


class Sun {
public:

	void setup(){


	}

	void update(){
		
		
	}
	
	void draw(){


	}

	//color values
	int hue;
	int saturation;
	int opacity;
	
	float radius;
	float density;
	ofPoint position;
	ofPoint velocity;
	ofPoint acceleration;
	ofPoint totalForce;
	
	//force for interaction between planets... these variables are changed in update of testApp
	float w;
	float h;	
	
	float rFactor;
	float mFactor;
	float vFactor;
	float gConstant;
	
};