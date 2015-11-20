#include "ofApp.h"

//--------------------------------------------------------------
void Bird::setup(){
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    vel.x = ofRandom(-2,2);
    vel.y = ofRandom(-2,2);
    acc.x = 0;
    acc.y = 0;
}

//--------------------------------------------------------------
void Bird::update(){
    vel += acc;
    /*same as
     vel.x += acc.x;
     vel.y += acc.y;
     */
    
    pos += vel;
}

//--------------------------------------------------------------
void Bird::draw(){
    ofPushStyle();
        ofSetColor(0);
        ofEllipse(pos.x, pos.y, 5, 5);
    ofPopStyle();
}
