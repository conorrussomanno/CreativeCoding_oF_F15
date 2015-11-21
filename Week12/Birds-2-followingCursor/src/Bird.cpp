#include "ofApp.h"

//--------------------------------------------------------------
void Bird::setup(){
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    vel.x = ofRandom(-2,2);
    vel.y = ofRandom(-2,2);
    acc.x = 0;
    acc.y = 0;
    
    tailLength = 10;
    radius = 5;
}

//--------------------------------------------------------------
void Bird::update(){
    vel += acc; //note: same as -> vel = vel + acc;
    
    pos += vel;
    /*note: same as ->
     pos.x += vel.x;
     pos.y += vel.y;
     */
    
    if(posPrevious.size() >= tailLength){ //if we have more than 5 positions stored (we're going to delete the oldest one)
//        cout << "delete!" << endl;
        posPrevious.erase(posPrevious.begin()); //delete the first element of position the vector ... this includes the cell itself ... so all later cells squish down!
    }
    posPrevious.push_back(pos); //add the latest position to the last last cell of the vector

}

//--------------------------------------------------------------
void Bird::draw(){
    ofPushStyle();
    
        //draw tail
        ofSetColor(119, 53, 75);
        for (int i = 0; i < posPrevious.size() - 1; i++) {
            
            //cout << "drawingTail: " << i << endl;
            //cout << posPrevious[i].x << " | " << posPrevious[i].y << posPrevious[i].x << " | " << posPrevious[i+1].x << " | " << posPrevious[i+1].y << endl;
            
            ofSetLineWidth((radius/tailLength)*(i));
            ofLine(posPrevious[i].x, posPrevious[i].y, posPrevious[i+1].x, posPrevious[i+1].y);
        }
    
        //draw body
        ofSetColor(100, 155, 215);
        ofEllipse(pos.x, pos.y, radius, radius);
    ofPopStyle();
}
