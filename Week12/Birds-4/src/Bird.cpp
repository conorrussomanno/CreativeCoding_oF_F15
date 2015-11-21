#include "ofApp.h"

//--------------------------------------------------------------
void Bird::setup(){
    
    //position & movement
    pos.x = ofRandom(ofGetWidth());
    pos.y = ofRandom(ofGetHeight());
    vel.x = ofRandom(-2,2);
    vel.y = ofRandom(-2,2);
    acc.x = 0;
    acc.y = 0;
    
    //physical attributes
    tailLength = ofRandom(4,8);
    radius = ofRandom(2,4);
    topSpeed = ofRandom(5,30);
    
    //personality traits
    comfortDistance = ofRandom(10,50);
    flowDistance = ofRandom(10,20);
    cursorCuriosityDistance = ofRandom(500,800);
    
    herdDependency = ofRandom(5,10);
    proximityDiscomfort = ofRandom(5,10);
    flowConsideration = ofRandom(5,10);
    cursorCuriosity = ofRandom(10,20);
    
//    //physical attributes
//    tailLength = 5;
//    radius = 4;
//    
//    //personality traits
//    comfortDistance = 25;
//    flowDistance = 15;
//    cursorCuriosityDistance = 650;
//    
//    herdDependency = 7;
//    proximityDiscomfort = 7;
//    flowConsideration = 7;
//    cursorCuriosity = 15;
    
}

//--------------------------------------------------------------
void Bird::update(bool _recordPosition){

    vel += acc; //note: same as -> vel = vel + acc;
    
    //don't let the birds fly to fast (or else you lose them off the screen)
    if(vel.length() >= topSpeed){ //speed limit = 10
        vel = topSpeed * vel.normalize();
    }
    
    pos += vel;
    /*note: same as ->
     pos.x += vel.x;
     pos.y += vel.y;
     */
    
    if(_recordPosition == true){ //if ofApp has told us it's time to record our position
        if(posPrevious.size() >= tailLength){ //if we have more than 5 positions stored (we're going to delete the oldest one)
            //        cout << "delete!" << endl;
            posPrevious.erase(posPrevious.begin()); //delete the first element of position the vector ... this includes the cell itself ... so all later cells squish down!
        }
        posPrevious.push_back(pos); //add the latest position to the last last cell of the vector
    }
}

//--------------------------------------------------------------
void Bird::draw(){
    ofPushStyle();
    
        if(posPrevious.size() >= 2){
            //draw tail
            for (int i = 0; i < posPrevious.size() - 1; i++) {
                ofSetColor(100, 155, 215, (int)((float)255*((float)i/(float)posPrevious.size())));
                //cout << "drawingTail: " << i << endl;
                //cout << posPrevious[i].x << " | " << posPrevious[i].y << posPrevious[i].x << " | " << posPrevious[i+1].x << " | " << posPrevious[i+1].y << endl;
                
                ofSetLineWidth((radius/tailLength)*(i));
                ofLine(posPrevious[i].x, posPrevious[i].y, posPrevious[i+1].x, posPrevious[i+1].y);
            }
        }
    
        //draw body
        ofSetColor(100, 155, 215);
        ofEllipse(pos.x, pos.y, radius, radius);
    ofPopStyle();
}
