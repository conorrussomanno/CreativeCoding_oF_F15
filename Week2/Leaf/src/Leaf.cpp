//
//  Leaf.cpp
//  Leaf
//
//  Created by Conor Russomanno on 9/10/15.
//
//

#include "Leaf.h"

//--------------------------------------------------------------
void Leaf::setup(){
//    float xPos, yPos; //position
//    float leafLength, leafWidth;//leaf length/width
//    float stemLength, stemWidth; //stem
//    float rotation; //rotation
//    ofColor color; //color
//    float scaleFactor; //scale
    xPos = ofGetWidth()/2;
    yPos = ofGetHeight()/2;
    leafLength = ofRandom(100, 150);
    leafWidth = ofRandom(100,200);
    stemLength = ofRandom(30,60);
    stemWidth = ofRandom(3,6);
    rotation = ofRandom(0,360);
    leafColor = ofColor(ofRandom(0,20), ofRandom(150,255), ofRandom(0,20), ofRandom(225,255));
    stemColor = ofColor(130, 50, 20); //hopefully brown
    scaleFactor = ofRandom(.5, 1);
    
}

//--------------------------------------------------------------
void Leaf::update(){
    
}

//--------------------------------------------------------------
void Leaf::draw(){
    //DRAW STUFF
//    ofRect(xPos, yPos, 20, 40);
    
    //Draw leave
    
    //draw leaf left
    
    ofPushMatrix();
        ofTranslate(xPos, yPos);
        ofRotateZ(rotation);
        ofScale(scaleFactor, scaleFactor);
    
        ofSetColor(leafColor);
        ofBeginShape();
        
            float x0 = 0;
            float x1 = x0 - leafWidth/2;
            float x2 = x0 - leafWidth/4;
            float x3 = 0;
        
            float y0 = 0 + stemLength;
            float y1 = y0 + leafLength/3;
            float y2 = y1 + leafLength/3;
            float y3 = y0 + leafLength;
        
            ofVertex(x0,y0);
            ofBezierVertex(x1,y1,x2,y2,x3,y3);
        
        ofEndShape();

        //draw leaf right
        ofBeginShape();
        
            x0 = 0;
            x1 = x0 + leafWidth/2;
            x2 = x0 + leafWidth/4;
            x3 = 0;
            
            y0 = 0 + stemLength;
            y1 = y0 + leafLength/3;
            y2 = y1 + leafLength/3;
            y3 = y0 + leafLength;
            
            ofVertex(x0,y0);
            ofBezierVertex(x1,y1,x2,y2,x3,y3);
        
        ofEndShape();
        
        //draw stem
        ofSetColor(stemColor);
        ofRect(0, 0 + stemLength/2, stemWidth, stemLength);
        
        //triangular stem through leaf
        ofTriangle(0 - stemWidth/2, 0 + stemLength, 0 + stemWidth/2, 0 + stemLength, 0, 0 + stemLength + 2*(leafLength/3));
    
    
    ofPopMatrix();
    
    
    
    
}








