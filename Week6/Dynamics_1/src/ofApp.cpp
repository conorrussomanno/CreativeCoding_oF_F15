#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //System Setup Stuff
    
    ofBackground(255); //white background
    ofSetFrameRate(60); //default is 60, but you can adjust this
    ofEnableAlphaBlending(); //allow for transparency, bc why not?
    ofSetBackgroundAuto(true); //maybe we don't want to autodraw the background... if we don't set this to false
//    ofEnableSmoothing(); //this makes shapes much smoother... similar to anti-aliasing in Photoshop, Maya, etc.
    
}

void ofApp::systemStart(){
    
    balls.clear(); //clear vector of balls if there is anything in there... 
    
    //setup one ball
//    myBall.setup();
    
    //setup many balls
    numBalls = 1000;
    for(int i = 0; i < numBalls; i++){
        Ball temp;
        temp.setup(ofRandom(0, ofGetWidth()),                          //xPos
//                       ((ofGetHeight()-100)/(numBalls-1))*i + 50,                //yPos
                      ofRandom(ofGetHeight()),                //yPos
                       ofRandom(-5,5),                                                        //xVel
                       ofRandom (-5, 5),                                                        //yVel
                       0,                                                        //xAcc
                       .5,                                                        //yAcc
                       10,                                                       //diameter
                       .85,                                                       //bounciness
                       ofColor(ofRandom(255), ofRandom(255), ofRandom(255))); //ballColor
        balls.push_back(temp);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //update one ball
    myBall.update();
    
    
    //update many balls
    for(int i = 0; i < numBalls; i++){
        balls[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushStyle();
        ofSetColor(255, 255, 255, 25);
        ofRect(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    //draw one ball
    myBall.draw();
    
    //draw many balls
    for(int i = 0; i < numBalls; i++){
        balls[i].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    systemStart();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
