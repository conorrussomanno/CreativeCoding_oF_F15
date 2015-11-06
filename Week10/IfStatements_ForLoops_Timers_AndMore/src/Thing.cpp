
#include "Thing.h"

//--------------------------------------------------------------
void Thing::setup(float xLocation, float yLocation){
    pos.x = xLocation;
    pos.y = yLocation;
    diameter = ofRandom(20,50);
    myColor = ofColor(15, 120, 220);
}

//--------------------------------------------------------------
void Thing::update(){
    
}

//--------------------------------------------------------------
void Thing::draw(){
    ofPushStyle();
        ofSetColor(myColor);
        ofEllipse(pos.x, pos.y, diameter, diameter);
    ofPopStyle();
}

ofColor Thing::returnNewColor(int thingNumber, int numThings){ //note that there is a return type (ofColor), so we have to return this to ofApp
    float ratio = (float)thingNumber/(float)numThings;
    cout << "Ratio = ";
    cout << ratio << endl;
    ofColor colorToSendBack = ofColor(255*(ratio), 255*(ratio), 0); //change my color to a new random color!
//    cout << "I'm thing [";
//    cout << thingNumber;
//    cout << "], and my new color is: ";
//    cout << colorToSendBack << endl;
    cout << colorToSendBack << endl;
    
    return colorToSendBack; //sends the new color back to update() of ofApp.cpp
}