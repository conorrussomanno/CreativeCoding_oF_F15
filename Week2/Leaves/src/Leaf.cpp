//
//  Leaf.cpp
//  Leaves
//
//  Created by Conor Russomanno on 9/10/15.
//
//

#include "Leaf.h"

void Leaf::setup(){
    xPos = ofGetWidth()/2; //set to middle of screen in the horizontal
    yPos = ofGetHeight()/2; //set to 3/4 of the way from the top of the screen in the vertical
    stemColor = ofColor(ofRandom(100,150),69,19); //brown
    leafColor = ofColor(ofRandom(0,20),ofRandom(100,200),ofRandom(0,20), ofRandom(150,255)); //set to random green color
    scaleFactor = ofRandom(.5,1.0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    stemLength = ofRandom(50,100);
    stemWidth = ofRandom(2,4);
    leafLength = ofRandom(150,300);
    leafWidth = ofRandom(80,200);
    leafCurvature = ofRandom(1, 5);
    rotation = ofRandom(0, 360);
}

void Leaf::update(){
    
}

void Leaf::draw(){
    
    ofPushMatrix();
        ofTranslate(xPos, yPos);
        ofScale(scaleFactor, scaleFactor);
        ofRotateZ(rotation);
    
        //draw leaf
        
        ofSetColor(leafColor);
        
        //draw left half of leaf
        
        ofBeginShape();
        
            float x0 = 0;
            float x1 = x0 - leafWidth;
            float x2 = x0 - leafWidth/leafCurvature;
            float x3 = x0;
            
            float y0 = 0 - stemLength;
            float y1 = y0 - leafLength/3;
            float y2 = y1 - leafLength/3;
            float y3 = y0 - leafLength;
            
            ofVertex(x0,y0);
            ofBezierVertex(x1,y1,x2,y2,x3,y3);
        
        ofEndShape();
        
        //draw right half of leaf
        
        ofBeginShape();
        
            x0 = 0; //don't need to redefine as float, because we are just reusing the variables created above
            x1 = x0 + leafWidth;
            x2 = x0 + leafWidth/leafCurvature;
            x3 = x0;
            
            y0 = 0 - stemLength;
            y1 = y0 - leafLength/3;
            y2 = y1 - leafLength/3;
            y3 = y0 - leafLength;
            
            ofVertex(x0,y0);
            ofBezierVertex(x1,y1,x2,y2,x3,y3);
        
        ofEndShape();
        
        //draw stem and veins of leaf
        
        ofSetColor(stemColor);
        ofRect(0,0 - (stemLength/2), stemWidth, stemLength); //MATH!
        ofTriangle(0 - stemWidth/2, 0 - stemLength, 0 + stemWidth/2, 0 - stemLength, 0, 0 - stemLength - 3*(leafLength/4));
    
    ofPopMatrix();

    
}










