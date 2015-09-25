//
//  Leaf.cpp
//  Leaves
//
//  Created by Conor Russomanno on 9/10/15.
//
//

#include "Leaf.h"

void Leaf::setup(float _branchAngle, int _season){
    xPos = ofGetWidth()/2; //set to middle of screen in the horizontal
    yPos = ofGetHeight()/2; //set to 3/4 of the way from the top of the screen in the vertical
    stemColor = ofColor(ofRandom(100,150),69,19); //brown
    
    season = _season;
    
    if(season == 0 || season == 3){
        leafColor = ofColor(ofRandom(0,20),ofRandom(100,200),ofRandom(0,20), ofRandom(150,255)); //set to random green color

    } else if(season == 1){
        randomNumber = ofRandom(0, 3);
        
        if(randomNumber >= 0 && randomNumber <1){
            leafColor = ofColor(ofRandom(100,150),69,19); //brown
        }
        if(randomNumber >= 1 && randomNumber < 2) {
            leafColor = ofColor(ofRandom(200,250),20,19); //red
        }
        if(randomNumber >= 2 && randomNumber < 3) {
            leafColor = ofColor(ofRandom(100,150),ofRandom(200,250),19); //yellow
        }
    }
    
//    leafColor = ofColor(ofRandom(0,20),ofRandom(100,200),ofRandom(0,20), ofRandom(150,255)); //set to random green color
    scaleFactor = ofRandom(.08,.2);
    ofSetRectMode(OF_RECTMODE_CENTER);
    stemLength = ofRandom(50,100);
    stemWidth = ofRandom(2,4);
    leafLength = ofRandom(150,300);
    leafWidth = ofRandom(80,200);
    leafCurvature = ofRandom(1, 5);
//    rotation = _branchAngle + PI/2; //bring in angle of branch
    rotation = _branchAngle + PI/2 + ofRandom(-(PI/2), PI/2); //bring in angle of branch

    rotation = rotation * (180/PI); //convert to degrees (from radians) to use for ofRotateZ() below, which expects degrees...
}

void Leaf::update(){
    
}

void Leaf::draw(float _xPos, float _yPos){
    
    ofPushMatrix();
    ofSetLineWidth(1);
    ofTranslate(_xPos, _yPos);
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
    
    float x11 = 0 - stemWidth/2;
    float x22 = 0 + stemWidth/2;
    
    ofTriangle(x11, 0 - stemLength, x22, 0 - stemLength, 0, 0 - stemLength - 3*(leafLength/4));
    
    cout << "x1 = ";
    cout << x1 << endl;
    cout << "x2 = ";
    cout << x2 << endl;
    
    ofPopMatrix();
    
    
}










