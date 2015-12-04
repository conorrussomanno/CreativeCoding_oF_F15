#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofSetFrameRate(30);  //set the rate at which the image updates .... 24 frames per second
    ofEnableAlphaBlending(); //use transparency
    
    position =  0;
    speed = 10;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    position += speed;  // each frame, add the speed to the current position  ... speed =
//    position = position + speed;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofBackground(125,125,125,20);
    
//    ofPushStyle();
//    ofFill();
//    ofSetColor(0,0,255);   //
//    ofRect(0, 0, ofGetWidth(), ofGetHeight());
//    ofPopStyle();
////
////    ofPushStyle();
////    ofSetColor(0, 0, 0);
////    ofEllipse(position, 200, 20, 20);
//    
//    ofSetColor(255, 0 ,0); //set color red
//    
//    ofPushStyle();
//        ofSetLineWidth(20);
//        ofSetColor(255); // set color white
//        ofLine(20, 20, 20, 40);
//    ofPopStyle();
    

    ofRect(100, 100, 40, 40); // this rect will draw red
    
    ofPushStyle();
        ofNoFill();
        ofRect(200, 200, 40, 40); // this rect will draw red
    ofPopStyle();
    
//    ofPopStyle();
    

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
