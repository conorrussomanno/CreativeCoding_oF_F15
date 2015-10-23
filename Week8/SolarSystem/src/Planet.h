#pragma once
#include "ofMain.h"
#include "testApp.h"
#include "Sun.h"

class Planet {
public:

	void setup(int x, int y)
	{
		radius = 50;
		position.x = x;
		position.y = y;
		velocity.x = 100;
		velocity.y = 100;
		acceleration.x = 0;
		acceleration.y = 0;
		totalForce.x = 0;
		totalForce.y = 0;
		hue = 0;
		saturation = 100;
		density = 100;
		
	//  Fg = (G x m1 x m2)/( r^2 )
		rFactor = 1.0;
		vFactor = 20.0;
		mFactor = 1000.0;
		gConstant = .001;
		

		
	}
	
	void update()
	{
		//PHYSICS INTERACTIONS
		
		//interact with walls
		if(position.x<=radius*rFactor){
			position.x = radius*rFactor + 1;
			velocity.x *= -1;
		}
		if (position.x>=ofGetWidth()-(radius*rFactor)) {
			position.x = ofGetWidth()-(radius*rFactor)-1;
			velocity.x *= -1;
		}
		if (position.y<=radius*rFactor) {
			position.y = radius*rFactor + 1;
			velocity.y *= -1;
		}
		if (position.y>=ofGetHeight()-(radius*rFactor)) {
			position.y = ofGetHeight()-(radius*rFactor)-1;
			velocity.y *= -1;
		}
		
		//convert totalX and totalY to accX and accY
		acceleration.x = totalForce.x/((density*(4/3)*PI*pow(radius, 3))/mFactor);
		acceleration.y = totalForce.y/((density*(4/3)*PI*pow(radius, 3))/mFactor);
		
		velocity.x += acceleration.x;
		velocity.y += acceleration.y;
		
		//speed regulators
		if (velocity.x > 200) {
			velocity.x = 200;
		}
		if (velocity.y > 200) {
			velocity.y = 200;
		}
		if (velocity.x < -200) {
			velocity.x = -200;
		}
		if (velocity.y < -200) {
			velocity.y = -200;
		}
		
		position.x += velocity.x/vFactor;
		position.y += velocity.y/vFactor;
		
		totalForce.x = 0;
		totalForce.y = 0;

	}
	
	void draw()
	{
		ofPushStyle();
		ofSetColor(255, 255, 255, 255);
		ofCircle(position.x, position.y, radius);
		ofxSetColorHSB(hue,saturation,200,opacity);
		ofCircle(position.x, position.y, radius);
		ofPopStyle();
		
	}
	
//	void mousePressed(int x, int y, int mode)
//	{
//		//for interface displays
//	}
//	
//	void mouseReleased(int x, int y, int mode)
//	{
//		//sets values of mode/attribute
//		if(mode==1){
//			position.x = x;
//			position.y = y;
//		}
//		
//	}
	
	void ofxSetColorHSB(float h, float s, float b, float a) {
		if (b==0) return ofSetColor(0,0,0,a); //black
		if (s==0) return ofSetColor(b,b,b,a); //gray
		
		h *= 6.0 / 360.0;
		s *= 1.0 / 100;
		
		float x = b * (1-s);
		float y = b * (1-s*(h-int(h)));
		float z = b * (1-s*(1-(h-int(h))));
		
		switch (int(h)) {
			case 0: return ofSetColor(b,z,x,a); //red
			case 1: return ofSetColor(y,b,x,a); //green
			case 2: return ofSetColor(x,b,z,a); 
			case 3: return ofSetColor(x,y,b,a); //blue
			case 4: return ofSetColor(z,x,b,a); 
			case 5: return ofSetColor(b,x,y,a); //back to red
		}
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
    //	float w;
    //	float h;	
	
	float rFactor;
	float mFactor;
	float vFactor;
	float gConstant;
	
};
